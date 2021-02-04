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
#include "P3ServTKoksohimRecord.h"

#include "P3ServMainFunctionKoksohim.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

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
bool KoksohimReadRecord(int FileHandle, int RecordNum, TKoksohimRecord * Record)
{
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
		// WriteToLog(Format(IDS_LOG_ERROR_CORRUPTED_RECORD,
		// ARRAYOFCONST((RecordNum + 1, TmStamp, DozN, Virabotka, Material))));

		return false;
	}

	return true;
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

			if (KoksohimReadRecord(FileHandle, i, Record)) {
				Records->Add(Record);
			}
			else {
				delete Record;
			}

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
	S += ":scales,:bdatetime,:dozator_num,:netto,:material_code";
	S += ")";

	SQLAdd(Query, S);

	SQLSetParam(Query, "scales", Settings->KoksohimScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "dozator_num", Record->DozatorNum);
	SQLSetParam(Query, "netto", Record->Netto);
	SQLSetParam(Query, "material_code", Record->Material);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void KoksohimDeleteFromServer(TSettings * Settings, TKoksohimRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	SQLAdd(Query, IDS_SQL_DELETE);
	SQLAdd(Query, IDS_SQL_FROM);

	SQLAdd(Query, IDS_SQL_TABLE_KOKSOHIM_MYSQL);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "scales=:scales");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "bdatetime=:bdatetime");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "dozator_num=:dozator_num");

	SQLSetParam(Query, "scales", Settings->KoksohimScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "dozator_num", Record->DozatorNum);

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void MainFunctionKoksohim(TSettings * Settings) {
	ULONGLONG FirstTick = StartTimer();

	CheckSettings(Settings);

	TADOConnection * ConnectionServer = new TADOConnection(NULL);

	TADOQuery * QueryServer = new TADOQuery(NULL);

	QueryServer->Connection = ConnectionServer;

	OpenMySQLConnection(Settings, ConnectionServer);

	TKoksohimRecordList * Records = new TKoksohimRecordList();

	TStringList * SyncList = new TStringList();
	TStringList * SyncListNewValues = new TStringList();

	int NU;

	try {
		KoksohimLoad(Settings, Records);

		KoksohimLoadSyncList(SyncList);

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
		// Также, в конце файла  могут быть данные за следующий год.
		// В довесок, могут быть повторяющиеся записи.
        // На редкость убогая программа. ЪУЪ

		// Исправляем даты

		int BreakID = -1;
		TDateTime BreakDateTime = 0;

		for (int i = 0; i < Records->Count; i++) {
			if (Records->Items[i]->DateTime < BreakDateTime) {
				BreakID = i;
				break;
			}
			BreakDateTime = Records->Items[i]->DateTime;
		}

		for (int i = 0; i < BreakID; i++) {
			Records->Items[i]->DateTime =
				IncYear(Records->Items[i]->DateTime, -1);
		}

		BreakID = Records->Count;
		BreakDateTime = Now();

		for (int i = Records->Count - 1; i >= 0; i--) {
			if (Records->Items[i]->DateTime > BreakDateTime) {
				BreakID = i;
				break;
			}
			BreakDateTime = Records->Items[i]->DateTime;
		}

		for (int i = BreakID + 1; i < Records->Count; i++) {
			Records->Items[i]->DateTime =
				IncYear(Records->Items[i]->DateTime, 1);
		}

		// Сохраняем
		for (int i = 0; i < Records->Count; i++) {
			String ID = DateTimeToKoksohimSyncStr(Records->Items[i]->DateTime);
			ID += IntToStr(Records->Items[i]->DozatorNum);

			if (!SyncList->Find(ID, NU)) {
				try {
					KoksohimSaveToServer(Settings, Records->Items[i],
						QueryServer);
				}
				catch (Exception &E) {
					WriteToLog(Format(IDS_LOG_EXCEPTION, E.Message));

					KoksohimDeleteFromServer(Settings, Records->Items[i],
						QueryServer);

					KoksohimSaveToServer(Settings, Records->Items[i],
						QueryServer);
				}

				SyncListNewValues->Add(ID);
			}

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		if (SyncListNewValues->Count > 0) {
			SyncList->AddStrings(SyncListNewValues);
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

		Records->Free();

		QueryServer->Free();

		ConnectionServer->Free();
	}
}

// ---------------------------------------------------------------------------
