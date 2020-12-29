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

#include "P3ServTAglodozaDozSumRecord.h"
#include "P3ServTAglodozaGroupSumRecord.h"
#include "P3ServTAglodozaGroupsRecord.h"

#include "P3ServMainFunctionAglodoza.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void AglodozaDozSumLoad(TSettings * Settings,
	TAglodozaDozSumRecordList * Records, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_SELECT);
	SQLAdd(Query, "*");
	SQLAdd(Query, IDS_SQL_FROM);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_DOZSUM);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "Send=0");

	// WriteToLog(Query->SQL->Text);

	Query->Open();

	try {
		TAglodozaDozSumRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TAglodozaDozSumRecord();

			Record->ID = Query->Fields->FieldByName("id")->AsInteger;

			Record->Line = Query->Fields->FieldByName("Line")->AsInteger;

			Record->DateTime = Query->Fields->FieldByName("DT")->AsDateTime;

			for (int i = 1; i <= AGLODOZA_DOZATOR_COUNT; i++) {
				Record->DozatorSum[i] =
					Query->Fields->FieldByName("DozSum" + IntToStr(i))->AsFloat;
				Record->DozatorProd[i] =
					Query->Fields->FieldByName("DozProd" + IntToStr(i))
					->AsFloat;
				Record->DozatorGroup[i] =
					Query->Fields->FieldByName("DozGroup" + IntToStr(i))
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
void AglodozaGroupSumLoad(TSettings * Settings,
	TAglodozaGroupSumRecordList * Records, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_SELECT);
	SQLAdd(Query, "*");
	SQLAdd(Query, IDS_SQL_FROM);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPSUM);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "Send=0");

	// WriteToLog(Query->SQL->Text);

	Query->Open();
	try {
		TAglodozaGroupSumRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TAglodozaGroupSumRecord();

			Record->ID = Query->Fields->FieldByName("id")->AsInteger;

			Record->Line = Query->Fields->FieldByName("Line")->AsInteger;

			Record->DateTime = Query->Fields->FieldByName("DT")->AsDateTime;

			for (int i = 1; i <= AGLODOZA_DOZATOR_COUNT; i++) {
				Record->GroupId[i] =
					Query->Fields->FieldByName("GroupID" + IntToStr(i))
					->AsFloat;
				Record->GroupSum[i] =
					Query->Fields->FieldByName("GroupSum" + IntToStr(i))
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
void AglodozaGroupsLoad(TSettings * Settings,
	TAglodozaGroupsRecordList * Records, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_SELECT);
	SQLAdd(Query, "*");
	SQLAdd(Query, IDS_SQL_FROM);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPS);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "Send=0");

	// WriteToLog(Query->SQL->Text);

	Query->Open();
	try {
		TAglodozaGroupsRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TAglodozaGroupsRecord();

			Record->ID = Query->Fields->FieldByName("id")->AsInteger;
			Record->FullName = Query->Fields->FieldByName("FullName")->AsString;
			Record->ShortName = Query->Fields->FieldByName("ShortName")
				->AsString;
			Record->Order = Query->Fields->FieldByName("Order")->AsInteger;
			Record->MaxPro = Query->Fields->FieldByName("MaxPro")->AsInteger;

			Records->Add(Record);

			Query->Next();
		}
	}
	__finally {
		Query->Close();
	}
}

// ---------------------------------------------------------------------------
void AglodozaDozSumSaveSend(TAglodozaDozSumRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_UPDATE);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_DOZSUM);
	SQLAdd(Query, IDS_SQL_SET);
	SQLAdd(Query, "Send=1");
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "id=:id");

	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaGroupSumSaveSend(TAglodozaGroupSumRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_UPDATE);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPSUM);
	SQLAdd(Query, IDS_SQL_SET);
	SQLAdd(Query, "Send=1");
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "id=:id");

	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaGroupsSaveSend(TAglodozaGroupsRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_UPDATE);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPS);
	SQLAdd(Query, IDS_SQL_SET);
	SQLAdd(Query, "Send=1");
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "id=:id");

	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaDozSumSaveToServer(TSettings * Settings,
	TAglodozaDozSumRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_DOZSUM_MYSQL);
	SQLAdd(Query, IDS_SQL_VALUES);

	String S = "";

	S += "(";
	S += ":scales,:bdatetime,:line,";

	for (int j = 1; j <= AGLODOZA_DOZATOR_COUNT; j++) {
		S += FloatToSQLStr(Record->DozatorSum[j]) + ",";
	}
	for (int j = 1; j <= AGLODOZA_DOZATOR_COUNT; j++) {
		S += FloatToSQLStr(Record->DozatorProd[j]) + ",";
	}
	for (int j = 1; j <= AGLODOZA_DOZATOR_COUNT; j++) {
		S += FloatToSQLStr(Record->DozatorGroup[j]) + ",";
	}
	S.Delete(S.Length(), 1);

	S += ")";

	SQLAdd(Query, S);

	SQLSetParam(Query, "scales", Settings->AglodozaScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "line", Record->Line);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaGroupSumSaveToServer(TSettings * Settings,
	TAglodozaGroupSumRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPSUM_MYSQL);
	SQLAdd(Query, IDS_SQL_VALUES);

	String S = "";

	S += "(";
	S += ":scales,:bdatetime,:line,";

	for (int j = 1; j <= AGLODOZA_GROUPS_COUNT; j++) {
		S += FloatToSQLStr(Record->GroupId[j]) + ",";
	}
	for (int j = 1; j <= AGLODOZA_GROUPS_COUNT; j++) {
		S += FloatToSQLStr(Record->GroupSum[j]) + ",";
	}
	S.Delete(S.Length(), 1);

	S += ")";

	SQLAdd(Query, S);

	SQLSetParam(Query, "scales", Settings->AglodozaScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "line", Record->Line);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaGroupsSaveToServer(TSettings * Settings,
	TAglodozaGroupsRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPS_MYSQL);
	SQLAdd(Query, IDS_SQL_VALUES);

	String S = "";

	S += "(";
	S += ":scales,:id,:fullname,:shortname,:g_order,:maxpro";
	S += ")";

	SQLAdd(Query, S);

	SQLSetParam(Query, "scales", Settings->AglodozaScaleNum);
	SQLSetParam(Query, "id", Record->ID);
	SQLSetParam(Query, "fullname", Record->FullName);
	SQLSetParam(Query, "shortname", Record->ShortName);
	SQLSetParam(Query, "g_order", Record->Order);
	SQLSetParam(Query, "maxpro", Record->MaxPro);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaDozSumDeleteFromServer(TSettings * Settings,
	TAglodozaDozSumRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_DELETE);
	SQLAdd(Query, IDS_SQL_FROM);

	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_DOZSUM_MYSQL);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "scales=:scales");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "bdatetime=:bdatetime");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "line=:line");

	SQLSetParam(Query, "scales", Settings->AglodozaScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "line", Record->Line);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaGroupSumDeleteFromServer(TSettings * Settings,
	TAglodozaGroupSumRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_DELETE);
	SQLAdd(Query, IDS_SQL_FROM);

	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPSUM_MYSQL);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "scales=:scales");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "bdatetime=:bdatetime");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "line=:line");

	SQLSetParam(Query, "scales", Settings->AglodozaScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "line", Record->Line);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaGroupsDeleteFromServer(TSettings * Settings,
	TAglodozaGroupsRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_DELETE);
	SQLAdd(Query, IDS_SQL_FROM);

	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPS_MYSQL);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "scales=:scales");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "id=:id");

	SQLSetParam(Query, "scales", Settings->AglodozaScaleNum);
	SQLSetParam(Query, "id", Record->ID);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void MainFunctionAglodoza(TSettings * Settings) {
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

	TAglodozaDozSumRecordList * DozSumRecords = new TAglodozaDozSumRecordList();
	TAglodozaGroupSumRecordList * GroupSumRecords =
		new TAglodozaGroupSumRecordList();
	TAglodozaGroupsRecordList * GroupsRecords = new TAglodozaGroupsRecordList();

	try {
		// ------------- DozatorSum -------------
		AglodozaDozSumLoad(Settings, DozSumRecords, QueryLocal);

		for (int i = 0; i < DozSumRecords->Count; i++) {
			try {
				AglodozaDozSumSaveToServer(Settings, DozSumRecords->Items[i],
					QueryServer);
			}
			catch (Exception &E) {
				WriteToLog(Format(IDS_LOG_EXCEPTION, E.Message));

				AglodozaDozSumDeleteFromServer(Settings,
					DozSumRecords->Items[i], QueryServer);

				AglodozaDozSumSaveToServer(Settings, DozSumRecords->Items[i],
					QueryServer);
			}

			AglodozaDozSumSaveSend(DozSumRecords->Items[i], QueryLocal);

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		// ------------- GroupSum -------------
		AglodozaGroupSumLoad(Settings, GroupSumRecords, QueryLocal);

		for (int i = 0; i < GroupSumRecords->Count; i++) {
			try {
				AglodozaGroupSumSaveToServer(Settings,
					GroupSumRecords->Items[i], QueryServer);
			}
			catch (Exception &E) {
				WriteToLog(Format(IDS_LOG_EXCEPTION, E.Message));

				AglodozaGroupSumDeleteFromServer(Settings,
					GroupSumRecords->Items[i], QueryServer);

				AglodozaGroupSumSaveToServer(Settings,
					GroupSumRecords->Items[i], QueryServer);
			}

			AglodozaGroupSumSaveSend(GroupSumRecords->Items[i], QueryLocal);

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		// ------------- Groups -------------
		AglodozaGroupsLoad(Settings, GroupsRecords, QueryLocal);

		for (int i = 0; i < GroupsRecords->Count; i++) {
			try {
				AglodozaGroupsSaveToServer(Settings, GroupsRecords->Items[i],
					QueryServer);
			}
			catch (Exception &E) {
				WriteToLog(Format(IDS_LOG_EXCEPTION, E.Message));

				AglodozaGroupsDeleteFromServer(Settings,
					GroupsRecords->Items[i], QueryServer);

				AglodozaGroupsSaveToServer(Settings, GroupsRecords->Items[i],
					QueryServer);
			}

			AglodozaGroupsSaveSend(GroupsRecords->Items[i], QueryLocal);

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		WriteToLog(Format(IDS_LOG_AGLODOZA_DATA_SAVED,
			ARRAYOFCONST((DozSumRecords->Count, GroupSumRecords->Count,
			GroupsRecords->Count, StopTimer(FirstTick)))));
	}
	__finally {
		GroupsRecords->Free();
		GroupSumRecords->Free();
		DozSumRecords->Free();

		QueryServer->Free();
		QueryLocal->Free();

		ConnectionServer->Free();
		ConnectionLocal->Free();
	}
}

// ---------------------------------------------------------------------------
