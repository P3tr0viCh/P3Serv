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

#include "P3ServTDomnaRecord.h"

#include "P3ServMainFunctionDomna.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void DomnaLoad(TSettings * Settings, TDomnaRecordList * Records,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_SELECT);
	SQLAdd(Query, "Measures.ID, Measures.DT, Measures.Weigh, Measures.PartID,");
	SQLAdd(Query, "Weights.WeighName, Weights.WeighID, Weights.Left,");
	SQLAdd(Query, "Products.Product, Products.ProductID");
	if (Settings->DomnaHumidity) {
		SQLAdd(Query, ", Measures.Humidity");
	}
	SQLAdd(Query, IDS_SQL_FROM);
	SQLAdd(Query, IDS_SQL_TABLE_DOMNA_MEASURES);
	SQLAdd(Query, ",");
	SQLAdd(Query, IDS_SQL_TABLE_DOMNA_WEIGHTS);
	SQLAdd(Query, ",");
	SQLAdd(Query, IDS_SQL_TABLE_DOMNA_PRODUCTS);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "Send=0");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "Measures.WeighID = Weights.WeighID");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "Measures.ProductID = Products.ProductID");

	// WriteToLog(Query->SQL->Text);

	Query->Open();
	try {
		TDomnaRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TDomnaRecord();

			Record->ID = Query->Fields->FieldByName("ID")->AsInteger;
			Record->DateTime = Query->Fields->FieldByName("DT")->AsDateTime;
			Record->WeighName = Query->Fields->FieldByName("WeighName")
				->AsString;
			Record->WeighNameCode = Query->Fields->FieldByName("WeighID")
				->AsInteger;
			Record->Product = Query->Fields->FieldByName("Product")->AsString;
			Record->ProductCode = Query->Fields->FieldByName("ProductID")
				->AsInteger;
			Record->LeftSide = Query->Fields->FieldByName("Left")->AsBoolean;
			Record->Netto = Query->Fields->FieldByName("Weigh")->AsFloat;
			Record->PartCode = Query->Fields->FieldByName("PartID")->AsInteger;
			if (Settings->DomnaHumidity) {
				Record->Humidity = Query->Fields->FieldByName("Humidity")
					->AsFloat;
			}
			Records->Add(Record);

			Query->Next();
		}
	}
	__finally {
		Query->Close();
	}
}

// ---------------------------------------------------------------------------
void DomnaSaveSend(TDomnaRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_UPDATE);
	SQLAdd(Query, IDS_SQL_TABLE_DOMNA_MEASURES);
	SQLAdd(Query, IDS_SQL_SET);
	SQLAdd(Query, "Send=1");
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "ID=:id");

	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void DomnaSaveToServer(TSettings * Settings, TDomnaRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	String S = "";

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_DOMNA_MYSQL);
	S += "(";
	S += "scales, bdatetime, id, weighname, weighname_code, product, product_code, leftside, netto, part_code";
	if (Settings->DomnaHumidity) {
		S += ", humidity";
	}
	S += ")";
	SQLAdd(Query, S);
	SQLAdd(Query, IDS_SQL_VALUES);

	S = "";

	S += "(";
	S += ":scales, :bdatetime, :id, :weighname, :weighname_code, :product, :product_code, :leftside, :netto, :part_code";
	if (Settings->DomnaHumidity) {
		S += ", :humidity";
	}
	S += ")";

	SQLAdd(Query, S);

	// WriteToLog(Query->SQL->Text);

	SQLSetParam(Query, "scales", Settings->DomnaScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "id", Record->ID);
	SQLSetParam(Query, "weighname", Record->WeighName);
	SQLSetParam(Query, "weighname_code", Record->WeighNameCode);
	SQLSetParam(Query, "product", Record->Product);
	SQLSetParam(Query, "product_code", Record->ProductCode);
	SQLSetParam(Query, "leftside", Record->LeftSide);
	SQLSetParam(Query, "netto", Record->Netto);
	SQLSetParam(Query, "part_code", Record->PartCode);
	if (Settings->DomnaHumidity) {
		SQLSetParam(Query, "humidity", Record->Humidity);
	}
	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void DomnaDeleteFromServer(TSettings * Settings, TDomnaRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_DELETE);
	SQLAdd(Query, IDS_SQL_FROM);

	SQLAdd(Query, IDS_SQL_TABLE_DOMNA_MYSQL);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "scales=:scales");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "bdatetime=:bdatetime");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "id=:id");

	SQLSetParam(Query, "scales", Settings->DomnaScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void MainFunctionDomna(TSettings * Settings) {
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

	TDomnaRecordList * Records = new TDomnaRecordList();

	try {
		DomnaLoad(Settings, Records, QueryLocal);

		for (int i = 0; i < Records->Count; i++) {
			try {
				DomnaSaveToServer(Settings, Records->Items[i], QueryServer);
			}
			catch (Exception &E) {
				WriteToLog(Format(IDS_LOG_EXCEPTION, E.Message));

				DomnaDeleteFromServer(Settings, Records->Items[i], QueryServer);

				DomnaSaveToServer(Settings, Records->Items[i], QueryServer);
			}

			DomnaSaveSend(Records->Items[i], QueryLocal);

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		WriteToLog(Format(IDS_LOG_DOMNA_DATA_SAVED,
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
