// ---------------------------------------------------------------------------

#pragma hdrstop

#include <ComObj.hpp>
#include <System.SysUtils.hpp>
#include <System.DateUtils.hpp>

#include <UtilsStr.h>
#include <UtilsLog.h>
#include <UtilsMisc.h>

#include "P3ServStrings.h"

#include "P3ServAdd.h"

#include "P3ServTKanatRecord.h"

#include "P3ServMainFunctionKanat.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void KanatLoad(TSettings * Settings, TKanatRecordList * Records,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_SELECT);
	SQLAdd(Query, "ID, DTWeigh, Brutto, Tara, Netto");
	SQLAdd(Query, IDS_SQL_FROM);
	SQLAdd(Query, IDS_SQL_TABLE_KANAT_MEASURES);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "Send=0");

	// WriteToLog(Query->SQL->Text);

	Query->Open();
	try {
		TKanatRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TKanatRecord();

			Record->ID = Query->Fields->FieldByName("ID")->AsInteger;
			Record->DateTime = Query->Fields->FieldByName("DTWeigh")
				->AsDateTime;
			Record->Brutto = Query->Fields->FieldByName("Brutto")->AsFloat;
			Record->Tare = Query->Fields->FieldByName("Tara")->AsFloat;
			Record->Netto = Query->Fields->FieldByName("Netto")->AsFloat;
			Records->Add(Record);

			Query->Next();
		}
	}
	__finally {
		Query->Close();
	}
}

// ---------------------------------------------------------------------------
void KanatSaveSend(TKanatRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_UPDATE);
	SQLAdd(Query, IDS_SQL_TABLE_KANAT_MEASURES);
	SQLAdd(Query, IDS_SQL_SET);
	SQLAdd(Query, "Send=1");
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "ID=:id");

	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void KanatSaveToServer(TSettings * Settings, TKanatRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	String S = "";

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_KANAT_MYSQL);
	S += "(";
	S += "scales, bdatetime, id, brutto, tare, netto";
	S += ")";
	SQLAdd(Query, S);
	SQLAdd(Query, IDS_SQL_VALUES);

	S = "";

	S += "(";
	S += ":scales, :bdatetime, :id, :brutto, :tare, :netto";
	S += ")";

	SQLAdd(Query, S);

	// WriteToLog(Query->SQL->Text);

	SQLSetParam(Query, "scales", Settings->KanatScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "id", Record->ID);
	SQLSetParam(Query, "brutto", Record->Brutto);
	SQLSetParam(Query, "tare", Record->Tare);
	SQLSetParam(Query, "netto", Record->Netto);
	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void KanatDeleteFromServer(TSettings * Settings, TKanatRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_DELETE);
	SQLAdd(Query, IDS_SQL_FROM);

	SQLAdd(Query, IDS_SQL_TABLE_KANAT_MYSQL);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "scales=:scales");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "bdatetime=:bdatetime");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "id=:id");

	SQLSetParam(Query, "scales", Settings->KanatScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void MainFunctionKanat(TSettings * Settings) {
	ULONGLONG FirstTick = StartTimer();

	CheckSettings(Settings);

	TADOConnection * ConnectionLocal = new TADOConnection(NULL);
	TADOConnection * ConnectionServer = new TADOConnection(NULL);

	TADOQuery * QueryLocal = new TADOQuery(NULL);
	TADOQuery * QueryServer = new TADOQuery(NULL);

	QueryLocal->Connection = ConnectionLocal;
	QueryServer->Connection = ConnectionServer;

	OpenMySQLConnection(Settings, ConnectionServer);
	OpenAccessConnection(Settings, ConnectionLocal);

	TKanatRecordList * Records = new TKanatRecordList();

	try {
		KanatLoad(Settings, Records, QueryLocal);

		for (int i = 0; i < Records->Count; i++) {
			try {
				KanatSaveToServer(Settings, Records->Items[i], QueryServer);
			}
			catch (Exception &E) {
				WriteToLog(Format(IDS_LOG_EXCEPTION, E.Message));

				KanatDeleteFromServer(Settings, Records->Items[i], QueryServer);

				KanatSaveToServer(Settings, Records->Items[i], QueryServer);
			}

			KanatSaveSend(Records->Items[i], QueryLocal);

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		WriteToLog(Format(IDS_LOG_KANAT_DATA_SAVED,
			ARRAYOFCONST((Records->Count, StopTimer(FirstTick)))));
	}
	__finally {
		Records->Free();

		QueryServer->Free();
		QueryLocal->Free();

		ConnectionServer->Free();
		ConnectionLocal->Free();
	}
}

// ---------------------------------------------------------------------------
