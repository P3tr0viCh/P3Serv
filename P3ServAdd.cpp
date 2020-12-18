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

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void CheckSettings(TSettings * Settings) {
	if (IsEmpty(Settings->MySQLHost) || IsEmpty(Settings->MySQLPort) ||
		IsEmpty(Settings->MySQLDatabase) || IsEmpty(Settings->MySQLUser)) {
		throw EIniFileException(Format(IDS_LOG_ERROR_CHECK_SETTINGS, "mysql"));
	}

	switch (Settings->ProgramMode) {
	case pmAglodoza:
		if (Settings->AglodozaScaleNum == 0 ||
			IsEmpty(Settings->AglodozaDatabase)) {
			throw EIniFileException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
				"aglodoza"));
		}

		if (!FileExists(Settings->AglodozaDatabase)) {
			throw EFileNotFoundException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
				"aglodoza (database not exists)"));
		}

		break;
	case pmKoksohim:
		if (Settings->KoksohimScaleNum == 0 ||
			IsEmpty(Settings->KoksohimDatabase)) {
			throw EIniFileException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
				"koksohim"));
		}

		if (!FileExists(Settings->KoksohimDatabase)) {
			throw EFileNotFoundException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
				"koksohim (database not exists)"));
		}

		break;
	case pmDomna:
		if (Settings->DomnaScaleNum == 0 || IsEmpty(Settings->DomnaDatabase)) {
			throw EIniFileException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
				"domna"));
		}

		if (!FileExists(Settings->DomnaDatabase)) {
			throw EFileNotFoundException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
				"domna (database not exists)"));
		}

		break;
	case pmUnknown:
	default:
		throw EIniFileException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
			"program mode"));
	}
}

// ---------------------------------------------------------------------------
String GetMySQLConnectionString(TSettings * Settings) {
	return Format(IDS_CONNECTION_MYSQL,
		ARRAYOFCONST((Settings->MySQLHost, Settings->MySQLPort,
		Settings->MySQLDatabase, Settings->MySQLUser, Settings->MySQLPass)));
}

// ---------------------------------------------------------------------------
String GetAccessConnectionString(TSettings * Settings) {
	String Database, User, Pass;

	switch (Settings->ProgramMode) {
	pmAglodoza:
		Database = Settings->AglodozaDatabase;
		User = Settings->AglodozaUser;
		Pass = Settings->AglodozaPass;
		break;
	pmDomna:
		Database = Settings->DomnaDatabase;
		User = Settings->DomnaUser;
		Pass = Settings->DomnaPass;
		break;
	default:
		throw Exception("GetAccessConnectionString");
	}

	return Format(IDS_CONNECTION_ACCESS, ARRAYOFCONST((Database, User, Pass)));
}

void OpenMySQLConnection(TSettings * Settings, TADOConnection * Connection) {
	Connection->ConnectionString = GetMySQLConnectionString(Settings);

	try {
		Connection->Open();
	}
	catch (Exception &E) {
		throw Exception(IDS_LOG_ERROR_SERVER_DB_OPEN,
		ARRAYOFCONST((E.Message)));
	}
}

// ---------------------------------------------------------------------------
void OpenAccessConnection(TSettings * Settings, TADOConnection * Connection) {
	String Database;

	switch (Settings->ProgramMode) {
	case pmAglodoza:
		Database = Settings->AglodozaDatabase;
		break;
	case pmDomna:
		Database = Settings->DomnaDatabase;
		break;
	default:
		throw Exception("OpenAccessConnection");
	}

	if (!FileExists(Database)) {
		throw EFileNotFoundException(Format(IDS_LOG_ERROR_LOCAL_DB_NOT_EXISTS,
			Database));
	}

	Connection->ConnectionString = GetAccessConnectionString(Settings);

	try {
		Connection->Open();
	}
	catch (Exception &E) {
		throw Exception(Format(IDS_LOG_ERROR_LOCAL_DB_OPEN, E.Message));
	}
}

// ---------------------------------------------------------------------------
void AglodozaDozSumLoad(TSettings * Settings, TDozSumRecordList * Records,
	TADOQuery * Query) {
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
		TDozSumRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TDozSumRecord();

			Record->ID = Query->Fields->FieldByName("id")->AsInteger;

			Record->Line = Query->Fields->FieldByName("Line")->AsInteger;

			Record->DateTime = Query->Fields->FieldByName("DT")->AsDateTime;

			for (int i = 1; i <= DOZATOR_COUNT; i++) {
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
void AglodozaGroupSumLoad(TSettings * Settings, TGroupSumRecordList * Records,
	TADOQuery * Query) {
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
		TGroupSumRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TGroupSumRecord();

			Record->ID = Query->Fields->FieldByName("id")->AsInteger;

			Record->Line = Query->Fields->FieldByName("Line")->AsInteger;

			Record->DateTime = Query->Fields->FieldByName("DT")->AsDateTime;

			for (int i = 1; i <= DOZATOR_COUNT; i++) {
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
void AglodozaGroupsLoad(TSettings * Settings, TGroupsRecordList * Records,
	TADOQuery * Query) {
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
		TGroupsRecord * Record;

		while (!Query->Eof) {
			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}

			Record = new TGroupsRecord();

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
void AglodozaDozSumSaveSend(TDozSumRecord * Record, TADOQuery * Query) {
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
void AglodozaGroupSumSaveSend(TGroupSumRecord * Record, TADOQuery * Query) {
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
void AglodozaGroupsSaveSend(TGroupsRecord * Record, TADOQuery * Query) {
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
void AglodozaDozSumSaveToServer(TSettings * Settings, TDozSumRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_DOZSUM_MYSQL);
	SQLAdd(Query, IDS_SQL_VALUES);

	String S = "";

	S += "(";
	S += ":scales,:bdatetime,:line,";

	for (int j = 1; j <= DOZATOR_COUNT; j++) {
		S += FloatToSQLStr(Record->DozatorSum[j]) + ",";
	}
	for (int j = 1; j <= DOZATOR_COUNT; j++) {
		S += FloatToSQLStr(Record->DozatorProd[j]) + ",";
	}
	for (int j = 1; j <= DOZATOR_COUNT; j++) {
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
	TGroupSumRecord * Record, TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_AGLODOZA_GROUPSUM_MYSQL);
	SQLAdd(Query, IDS_SQL_VALUES);

	String S = "";

	S += "(";
	S += ":scales,:bdatetime,:line,";

	for (int j = 1; j <= GROUPS_COUNT; j++) {
		S += FloatToSQLStr(Record->GroupId[j]) + ",";
	}
	for (int j = 1; j <= GROUPS_COUNT; j++) {
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
void AglodozaGroupsSaveToServer(TSettings * Settings, TGroupsRecord * Record,
	TADOQuery * Query) {
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
	TDozSumRecord * Record, TADOQuery * Query) {
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
	TGroupSumRecord * Record, TADOQuery * Query) {
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
	SQLSetParam(Query, "bdatetime", ((TGroupSumRecord*)Record)->DateTime);
	SQLSetParam(Query, "line", ((TGroupSumRecord*)Record)->Line);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void AglodozaGroupsDeleteFromServer(TSettings * Settings,
	TGroupsRecord * Record, TADOQuery * Query) {
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

	TDozSumRecordList * DozSumRecords = new TDozSumRecordList();
	TGroupSumRecordList * GroupSumRecords = new TGroupSumRecordList();
	TGroupsRecordList * GroupsRecords = new TGroupsRecordList();

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
void KoksohimLoadSyncList(TStringList * SyncList) {
	String FileName = GetSyncFileFullName(SYNC_KOKSOHIM);

	if (FileExists(FileName)) {
		SyncList->LoadFromFile(FileName);
	}
	else {
		String SyncFolder = GetSyncFolder();
		if (!DirectoryExists(SyncFolder)) {
			if (!CreateDir(SyncFolder)) {
				throw Exception(IDS_LOG_ERROR_CREATE_SYNCFOLDER);
			}
		}

		HANDLE SyncFile = CreateFile(FileName.w_str(), GENERIC_WRITE,
			FILE_SHARE_READ, NULL, OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_COMPRESSED, 0);

		if (SyncFile != INVALID_HANDLE_VALUE) {
			CloseHandle(SyncFile);
		}
		else {
			throw Exception(IDS_LOG_ERROR_CREATE_SYNCFILE);
		}
	}
}

// ---------------------------------------------------------------------------
String KoksohimReadField(int FileHandle, int FieldSize) {
	AnsiChar pszField[FIELD_MAX_SIZE + 1];

	pszField[FieldSize] = 0;

	int BytesRead = FileRead(FileHandle, pszField, FieldSize);

	if (BytesRead != FieldSize) {
		throw Exception(IDS_LOG_ERROR_KOKSOHIM_DB_CORRUPT);
	}

	return Trim(String(pszField));
}

// ---------------------------------------------------------------------------
TKoksohimRecord * KoksohimReadRecord(int FileHandle, int RecordNum) {
	String TmStamp = KoksohimReadField(FileHandle, FIELD_TMSTAMP_SIZE);
	String DozN = KoksohimReadField(FileHandle, FIELD_DOZN_SIZE);

	FileSeek(FileHandle, FIELD_SMENA_SIZE, 1);

	String Virabotka = KoksohimReadField(FileHandle, FIELD_VIRABOTKA_SIZE);
	String Material = KoksohimReadField(FileHandle, FIELD_MATERIAL_SIZE);

	FileSeek(FileHandle, FIELD_GROUP_SIZE + 1, 1);

	Virabotka = StringReplace(Virabotka, '.', FormatSettings.DecimalSeparator,
		TReplaceFlags());
	Virabotka = StringReplace(Virabotka, ',', FormatSettings.DecimalSeparator,
		TReplaceFlags());

	TKoksohimRecord * Record = new TKoksohimRecord();

	try {
		// 18123002 => 2018-12-30 02:00:00
		// Magic Number: "20"
		Record->DateTime = TDateTime(StrToInt("20" + TmStamp.SubString(1, 2)),
			StrToInt(TmStamp.SubString(3, 2)),
			StrToInt(TmStamp.SubString(5, 2)),
			StrToInt(TmStamp.SubString(7, 2)), 0, 0, 0);

		Record->DozatorNum = StrToInt(DozN);

		Record->Netto = StrToFloat(Virabotka);

		Record->Material = StrToInt(Material);
	}
	catch (...) {
		WriteToLog(Format(IDS_LOG_ERROR_CORRUPTED_RECORD,
			ARRAYOFCONST((RecordNum + 1, TmStamp, DozN, Virabotka, Material))));
	}

	return Record;
}

// ---------------------------------------------------------------------------
void KoksohimLoad(TSettings * Settings, TKoksohimRecordList * Records) {
	TKoksohimRecord * Record;

	int FileHandle = FileOpen(Settings->KoksohimDatabase, fmOpenRead);

	if (FileHandle < 0) {
		throw Exception(Format(IDS_LOG_ERROR_LOCAL_DB_OPEN,
			IntToStr((int)GetLastError())));
	}

	try {
		FileSeek(FileHandle, 4, 0);

		int TotalRecordCount;

		FileRead(FileHandle, &TotalRecordCount, 4);

		FileSeek(FileHandle, HEADER_SIZE + FIELD_SIZE * FIELD_COUNT + 3, 0);

		for (int i = 0; i < TotalRecordCount; i++) {
			Record = new TKoksohimRecord();

			Record = KoksohimReadRecord(FileHandle, i);

			Records->Add(Record);
		}
	}
	__finally {
		FileClose(FileHandle);
	}
}

// ---------------------------------------------------------------------------
void KoksohimSaveToServer(TSettings * Settings, TKoksohimRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_INSERT);
	SQLAdd(Query, IDS_SQL_TABLE_KOKSOHIM_MYSQL);
	SQLAdd(Query, IDS_SQL_VALUES);

	String S = "";

	S += "(";
	S += ":scales,:datetime,:dozator_num,:netto,:material_code";
	S += ")";

	SQLAdd(Query, S);

	SQLSetParam(Query, "scales", Settings->KoksohimScaleNum);
	SQLSetParam(Query, "datetime", Record->DateTime);
	SQLSetParam(Query, "dozator_num", Record->DozatorNum);
	SQLSetParam(Query, "netto", Record->Netto);
	SQLSetParam(Query, "material_code", Record->Material);

	Query->Prepared = true;

	// SQLExec(Query);
}

// ---------------------------------------------------------------------------
void MainFunctionKoksohim(TSettings * Settings) {
	ULONGLONG FirstTick = StartTimer();

	CheckSettings(Settings);

	TADOConnection * ConnectionServer = new TADOConnection(NULL);

	TADOQuery * QueryServer = new TADOQuery(NULL);

	QueryServer->Connection = ConnectionServer;

	OpenMySQLConnection(Settings, ConnectionServer);

	TKoksohimRecordList * KoksohimRecordRecords = new TKoksohimRecordList();

	TStringList * SyncList = new TStringList();
	TStringList * SyncListNewValues = new TStringList();

	int NU;

	try {
		KoksohimLoadSyncList(SyncList);

		KoksohimLoad(Settings, KoksohimRecordRecords);

		// В начале файла могут содержаться данные за прошлый год,
		// при этом в дате у них стоит текущий.
		// 18123002	01	2	24,7	18
		// 18123002	02	2	13,9	20
		// 18123002	03	2	15,9	04
		// ...
		// 18123123	07	2	0,0		02
		// 18123123	08	2	0,0		16
		// 18123123	09	2	0,0		09
		// Эти ^^^ записи на самом деле должны быть 17123123 и т.п.
		// 18010100	01	2	0,0		16
		// 18010100	02	2	0,0		20
		// 18010100	03	2	0,0		04
		// ...

		TDateTime BreakDateTime = Now(); // << Это и условие ниже попытка исправить

		for (int i = KoksohimRecordRecords->Count - 1; i >= 0; i--) {
			if (KoksohimRecordRecords->Items[i]->DateTime > BreakDateTime) {
				break;
			}

			BreakDateTime = KoksohimRecordRecords->Items[i]->DateTime;

			String ID = DateTimeToKoksohimSyncStr
				(KoksohimRecordRecords->Items[i]->DateTime);
			ID += IntToStr(KoksohimRecordRecords->Items[i]->DozatorNum);

			if (!SyncList->Find(ID, NU)) {
				KoksohimSaveToServer(Settings, KoksohimRecordRecords->Items[i],
					QueryServer);

				SyncListNewValues->Add(ID);
			}

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		if (SyncListNewValues->Count > 0) {
			SyncList->AddStrings(SyncListNewValues);
			SyncList->Sorted = true;
			try {
				SyncList->SaveToFile(GetSyncFileFullName(SYNC_KOKSOHIM));
			}
			catch (...) {
				throw Exception(IDS_LOG_ERROR_SAVE_SYNCFILE);
			}
		}

		WriteToLog(Format(IDS_LOG_KOKSOHIM_DATA_SAVED,
			ARRAYOFCONST((SyncListNewValues->Count, StopTimer(FirstTick)))));
	}
	__finally {
		SyncListNewValues->Free();
		SyncList->Free();

		KoksohimRecordRecords->Free();

		QueryServer->Free();

		ConnectionServer->Free();
	}
}

// ---------------------------------------------------------------------------
void SQLAdd(TADOQuery * Query, String Text) {
	Query->SQL->Add(Text);
}

// ---------------------------------------------------------------------------
void SQLAdd(TADOQuery * Query, NativeUInt Ident) {
	Query->SQL->Add(LoadStr(Ident));
}

// ---------------------------------------------------------------------------
void SQLSetParam(TADOQuery * Query, String ParamName, int Value) {
	Query->Parameters->ParamByName(ParamName)->DataType = ftInteger;
	Query->Parameters->ParamByName(ParamName)->Value = Value;
}

// ---------------------------------------------------------------------------
void SQLSetParam(TADOQuery * Query, String ParamName, String Value) {
	Query->Parameters->ParamByName(ParamName)->DataType = ftString;
	Query->Parameters->ParamByName(ParamName)->Value = Value;
}

// ---------------------------------------------------------------------------
void SQLSetParam(TADOQuery * Query, String ParamName, TDateTime Value) {
	SQLSetParam(Query, ParamName, DateTimeToSQLStr(Value));
}

// ---------------------------------------------------------------------------
void SQLExec(TADOQuery * Query) {
	// WriteToLog(Query->SQL->Text);
	Query->ExecSQL();
}

// ---------------------------------------------------------------------------
String DateTimeToSQLStr(TDateTime ADateTime) {
	return FormatDateTime("yyyy-MM-dd hh:nn:ss", ADateTime);
}

// ---------------------------------------------------------------------------
String DateTimeToKoksohimSyncStr(TDateTime ADateTime) {
	return FormatDateTime("yyyyMMddhhnnss", ADateTime);
}

// ---------------------------------------------------------------------------
String FloatToSQLStr(float Value) {
	return StringReplace(FloatToStr(Value), COMMA, DOT, TReplaceFlags());
}

// ---------------------------------------------------------------------------
String GetSyncFolder() {
	return IncludeTrailingPathDelimiter(ExtractFilePath(Application->ExeName)) +
		SYNC_FOLDER;
}

// ---------------------------------------------------------------------------
String GetSyncFileFullName(String FileName) {
	return GetSyncFolder() + PathDelim + FileName + SYNC_EXT;
}

// ---------------------------------------------------------------------------
