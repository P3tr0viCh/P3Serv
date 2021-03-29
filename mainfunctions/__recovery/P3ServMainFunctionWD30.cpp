// ---------------------------------------------------------------------------

#pragma hdrstop

#include <System.DateUtils.hpp>

#include <UtilsStr.h>
#include <UtilsLog.h>
#include <UtilsMisc.h>

#include "P3ServStrings.h"

#include "P3ServAdd.h"
#include "P3ServTWD30ZRecord.h"
#include "P3ServTWD30TRecord.h"
#include "P3ServTWD30SRecord.h"

#include "P3ServMainFunctionWD30.h"

// 18.03.2021 00:59:49.919
#define WD30_LOG_DATETIME 23

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void WD30LoadSyncList(TStringList * SyncList, int W) {
	String SyncFileName;

	switch (W) {
	case 0:
		SyncFileName = SYNC_WD30LOGS;
		break;
	case 1:
		SyncFileName = SYNC_WD30Z;
		break;
	case 2:
		SyncFileName = SYNC_WD30T;
		break;
	case 3:
		SyncFileName = SYNC_WD30S;
		break;
	default:
		throw EArgumentOutOfRangeException(W);
	}

	String FileName = GetSyncFileFullName(SyncFileName);

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
void WD30FindLogs(String LogFolder, TStringList * LogFiles) {
	TSearchRec SearchRec;
	LogFolder = IncludeTrailingPathDelimiter(LogFolder);

	if (FindFirst(LogFolder + "WDyn*.log", faAnyFile, SearchRec) == 0) {
		do {
			if (SearchRec.Name != "." && SearchRec.Name != ".." &&
				!IsValueInWord(SearchRec.Attr, faDirectory)) {

				LogFiles->Add(LogFolder + SearchRec.Name);
			}

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}
		while (FindNext(SearchRec) == 0);

		FindClose(SearchRec);
	}
}

// ---------------------------------------------------------------------------
bool IsCurrentLog(String LogName) {
	return SameStr(LogName, "WDyn.log");
}

// ---------------------------------------------------------------------------
bool IsDigit(char C) {
	return C >= '0' && C <= '9';
}

// ---------------------------------------------------------------------------
void WD30Load(String LogName, TWD30ZRecordList * ZRecords,
	TWD30TRecordList * TRecords, TWD30SRecordList * SRecords) {

	TWD30ZRecord * ZRecord;
	TWD30TRecord * TRecord;
	TWD30SRecord * SRecord;

	TFormatSettings FormatSettings;
	FormatSettings.DecimalSeparator = '.';

	TStringList * LogFile = new TStringList();

	try {
		LogFile->LoadFromFile(LogName);

		int P;
		int Index;
		int SensorState;

		bool UseZ;

		String S;
		String D;
		String V;

		char X;

		for (int i = 0; i < LogFile->Count; i++) {
			S = LogFile->Strings[i];

			if (S.IsEmpty()) {
				continue;
			}

			// 18.03.2021 00:56:16.261 Z  -2090   3848      0   2789
			// 18.03.2021 00:56:11.160 T -10.7 -10.7 0.0 0.0
			// 18.03.2021 00:59:49.919 18.03.2021 0:59:27 <--L  V = 3.1 WMode = CR WObject = 1 LocPos = 0 M1,M2,--,M4, T1,--,--,--,
			// |> WD30_LOG_DATETIME <|

			if (S.Length() < WD30_LOG_DATETIME + 2) {
				continue;
			}

			X = S[WD30_LOG_DATETIME + 2];

			// ----------- Нули ----------------------------------------------
			// Под каждое значение отведено 7 символов

			if (X == 'Z') {
				D = S.SubString(1, WD30_LOG_DATETIME);

				S.Delete(1, WD30_LOG_DATETIME + 2);

				ZRecord = new TWD30ZRecord();

				ZRecord->DateTime = StrToDateTime(D);

				Index = 1;

				while (!S.IsEmpty()) {
					V = S.SubString(1, 7);

					ZRecord->Z[Index] = StrToInt(V);

					Index++;

					S.Delete(1, 7);
				}

				ZRecords->Add(ZRecord);

				continue;
			}

			// ----------- Температуры ---------------------------------------
			// Температура дублируется, разница - 1 пробел и 2 пробела

			if (X == 'T') {
				if (S.Length() < WD30_LOG_DATETIME + 4) {
					continue;
				}

				if (S[WD30_LOG_DATETIME + 3] != ' ') {
					continue;
				}

				if (S[WD30_LOG_DATETIME + 4] == ' ') {
					continue;
				}

				D = S.SubString(1, WD30_LOG_DATETIME);

				S.Delete(1, WD30_LOG_DATETIME + 3);

				TRecord = new TWD30TRecord();

				TRecord->DateTime = StrToDateTime(D);

				Index = 1;

				S = S + " ";

				while (!S.IsEmpty()) {
					P = S.Pos(" ");

					V = S.SubString(1, P - 1);

					TRecord->T[Index] = StrToFloat(V, FormatSettings);

					Index++;

					S.Delete(1, P);
				}

				TRecords->Add(TRecord);

				continue;
			}

			// ----------- Датчики -------------------------------------------
			// После даты идёт ещё одна дата, начинается с цифры
			if (IsDigit(X)) {
				P = S.Pos(" LocPos ");
			}
			else {
				P = -1;
			}

			if (P > 0) {
				D = S.SubString(1, P - 1);

				// LocPos = 0
				S.Delete(1, P + 11);

				SRecord = new TWD30SRecord();

				SRecord->DateTime = StrToDateTime(D);

				Index = 1;

				UseZ = true;

				// M1,M2,--,M4, T1,--,--,--,

				while (!S.IsEmpty()) {
					P = S.Pos(",");

					V = S.SubString(1, P - 1);

					if (V[1] == ' ') {
						UseZ = false;
						Index = 1;
						V.Delete(1, 1);
					}

					if (V[1] == '-') {
						SensorState = 0;
					}
					else {
						SensorState = 1;
					}

					if (UseZ) {
						SRecord->Z->Z[Index] = SensorState;

						Index++;
					}
					else {
						SRecord->T->T[Index] = SensorState;

						Index++;
					}

					S.Delete(1, P);
				}

				SRecords->Add(SRecord);

				continue;
			}
		}
	}
	__finally {
		LogFile->Free();
	}
}

// ---------------------------------------------------------------------------
void WD30ZSaveToServer(TSettings * Settings, TWD30ZRecord * Record,
	TADOQuery * Query, bool UseInsert) {
	Query->SQL->Clear();

	String Name;

	if (UseInsert) {
		String Columns = "scales, bdatetime";
		String Params = ":scales, :bdatetime";

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			if (Record->Z[i] != WD30_Z_NULL_VALUE) {
				Name = "m" + IntToStr(i);
				Columns = Columns + ", " + Name;
				Params = Params + ", " + ":" + Name;
			}
		}

		SQLAdd(Query, IDS_SQL_INSERT);
		SQLAdd(Query, IDS_SQL_TABLE_WD30_Z_MYSQL);
		SQLAdd(Query, "(" + Columns + ")");
		SQLAdd(Query, IDS_SQL_VALUES);
		SQLAdd(Query, "(" + Params + ")");

		// WriteToLog(Query->SQL->Text);

		SQLSetParam(Query, "scales", Settings->WD30ScaleNum);
		SQLSetParam(Query, "bdatetime", Record->DateTime);

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			if (Record->Z[i] != WD30_Z_NULL_VALUE) {
				Name = "m" + IntToStr(i);
				SQLSetParam(Query, Name, Record->Z[i]);
			}
		}
	}
	else {
		String Values = "";

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			Name = "m" + IntToStr(i);
			Values = Values + ", " + Name + "=:" + Name;
		}
		Values.Delete(1, 2);

		SQLAdd(Query, IDS_SQL_UPDATE);
		SQLAdd(Query, IDS_SQL_TABLE_WD30_Z_MYSQL);
		SQLAdd(Query, IDS_SQL_SET);
		SQLAdd(Query, Values);
		SQLAdd(Query, IDS_SQL_WHERE);
		SQLAdd(Query, "scales=:scales");
		SQLAdd(Query, IDS_SQL_AND);
		SQLAdd(Query, "bdatetime=:bdatetime");

		// WriteToLog(Query->SQL->Text);

		SQLSetParam(Query, "scales", Settings->WD30ScaleNum);
		SQLSetParam(Query, "bdatetime", Record->DateTime);

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			Name = "m" + IntToStr(i);
			if (Record->Z[i] != WD30_Z_NULL_VALUE) {
				SQLSetParam(Query, Name, Record->Z[i]);
			}
			else {
				Query->Parameters->ParamByName(Name)->DataType = ftInteger;
				Query->Parameters->ParamByName(Name)->Value = Null();
			}
		}
	}

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
void WD30TSaveToServer(TSettings * Settings, TWD30TRecord * Record,
	TADOQuery * Query, bool UseInsert) {
	Query->SQL->Clear();

	String Name;

	if (UseInsert) {
		String Columns = "scales, bdatetime";
		String Params = ":scales, :bdatetime";

		for (int i = 1; i <= WD30_T_COUNT; i++) {
			if (Record->T[i] != WD30_T_NULL_VALUE) {
				Name = "t" + IntToStr(i);
				Columns = Columns + ", " + Name;
				Params = Params + ", " + ":" + Name;
			}
		}

		SQLAdd(Query, IDS_SQL_INSERT);
		SQLAdd(Query, IDS_SQL_TABLE_WD30_T_MYSQL);
		SQLAdd(Query, "(" + Columns + ")");
		SQLAdd(Query, IDS_SQL_VALUES);
		SQLAdd(Query, "(" + Params + ")");

		// WriteToLog(Query->SQL->Text);

		SQLSetParam(Query, "scales", Settings->WD30ScaleNum);
		SQLSetParam(Query, "bdatetime", Record->DateTime);

		for (int i = 1; i <= WD30_T_COUNT; i++) {
			if (Record->T[i] != WD30_T_NULL_VALUE) {
				Name = "t" + IntToStr(i);
				SQLSetParam(Query, Name, Record->T[i]);
			}
		}
	}
	else {
		String Values = "";

		for (int i = 1; i <= WD30_T_COUNT; i++) {
			Name = "t" + IntToStr(i);
			Values = Values + ", " + Name + "=:" + Name;
		}
		Values.Delete(1, 2);

		SQLAdd(Query, IDS_SQL_UPDATE);
		SQLAdd(Query, IDS_SQL_TABLE_WD30_T_MYSQL);
		SQLAdd(Query, IDS_SQL_SET);
		SQLAdd(Query, Values);
		SQLAdd(Query, IDS_SQL_WHERE);
		SQLAdd(Query, "scales=:scales");
		SQLAdd(Query, IDS_SQL_AND);
		SQLAdd(Query, "bdatetime=:bdatetime");

		// WriteToLog(Query->SQL->Text);

		SQLSetParam(Query, "scales", Settings->WD30ScaleNum);
		SQLSetParam(Query, "bdatetime", Record->DateTime);

		for (int i = 1; i <= WD30_T_COUNT; i++) {
			Name = "t" + IntToStr(i);
			if (Record->T[i] != WD30_T_NULL_VALUE) {
				SQLSetParam(Query, Name, Record->T[i]);
			}
			else {
				Query->Parameters->ParamByName(Name)->DataType = ftFloat;
				Query->Parameters->ParamByName(Name)->Value = Null();
			}
		}
	}

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
bool WD30SLoadFromServer(TSettings * Settings, TWD30SRecord * Record,
	TADOQuery * Query) {
	Query->SQL->Clear();

	String Name;

	TDateTime DateTimeEnd = IncMonth(Record->DateTime, -1);

	SQLAdd(Query, IDS_SQL_SELECT);
	SQLAdd(Query, "*");
	SQLAdd(Query, IDS_SQL_FROM);
	SQLAdd(Query, IDS_SQL_TABLE_WD30_S_MYSQL);
	SQLAdd(Query, IDS_SQL_WHERE);
	SQLAdd(Query, "scales=:scales");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "bdatetime<:bdatetime");
	SQLAdd(Query, IDS_SQL_AND);
	SQLAdd(Query, "bdatetime>:bdatetime_end");
	SQLAdd(Query, IDS_SQL_ORDER);
	SQLAdd(Query, "bdatetime");
	SQLAdd(Query, IDS_SQL_DESC);
	SQLAdd(Query, IDS_SQL_LIMIT_1);

	// WriteToLog(Query->SQL->Text);

	SQLSetParam(Query, "scales", Settings->WD30ScaleNum);
	SQLSetParam(Query, "bdatetime", Record->DateTime);
	SQLSetParam(Query, "bdatetime_end", DateTimeEnd);

	Query->Prepared = true;

	Query->Open();
	try {
		if (Query->RecordCount < 1) {
			return true;
		}

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			Name = "m" + IntToStr(i);

			if (Query->Fields->FieldByName(Name)->IsNull) {
				if (Record->Z->Z[i] != WD30_Z_NULL_VALUE) {
					return true;
				}
			}
			else {
				if (Record->Z->Z[i] != Query->Fields->FieldByName(Name)
					->AsInteger) {
					return true;
				}
			}
		}
		for (int i = 1; i <= WD30_T_COUNT; i++) {
			Name = "t" + IntToStr(i);

			if (Query->Fields->FieldByName(Name)->IsNull) {
				if (Record->T->T[i] != WD30_T_NULL_VALUE) {
					return true;
				}
			}
			else {
				if (Record->T->T[i] != Query->Fields->FieldByName(Name)
					->AsInteger) {
					return true;
				}
			}
		}
	}
	__finally {
		Query->Close();
	}

	return false;
}

// ---------------------------------------------------------------------------
void WD30SSaveToServer(TSettings * Settings, TWD30SRecord * Record,
	TADOQuery * Query, bool UseInsert) {
	Query->SQL->Clear();

	String Name;

	if (UseInsert) {
		String Columns = "scales, bdatetime";
		String Params = ":scales, :bdatetime";

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			if (Record->Z->Z[i] != WD30_Z_NULL_VALUE) {
				Name = "m" + IntToStr(i);
				Columns = Columns + ", " + Name;
				Params = Params + ", " + ":" + Name;
			}
		}
		for (int i = 1; i <= WD30_T_COUNT; i++) {
			if (Record->T->T[i] != WD30_T_NULL_VALUE) {
				Name = "t" + IntToStr(i);
				Columns = Columns + ", " + Name;
				Params = Params + ", " + ":" + Name;
			}
		}

		SQLAdd(Query, IDS_SQL_INSERT);
		SQLAdd(Query, IDS_SQL_TABLE_WD30_S_MYSQL);
		SQLAdd(Query, "(" + Columns + ")");
		SQLAdd(Query, IDS_SQL_VALUES);
		SQLAdd(Query, "(" + Params + ")");

		// WriteToLog(Query->SQL->Text);

		SQLSetParam(Query, "scales", Settings->WD30ScaleNum);
		SQLSetParam(Query, "bdatetime", Record->DateTime);

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			if (Record->Z->Z[i] != WD30_Z_NULL_VALUE) {
				Name = "m" + IntToStr(i);
				SQLSetParam(Query, Name, Record->Z->Z[i]);
			}
		}
		for (int i = 1; i <= WD30_T_COUNT; i++) {
			if (Record->T->T[i] != WD30_T_NULL_VALUE) {
				Name = "t" + IntToStr(i);
				SQLSetParam(Query, Name, Record->T->T[i]);
			}
		}
	}
	else {
		String Values = "";

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			Name = "m" + IntToStr(i);
			Values = Values + ", " + Name + "=:" + Name;
		}
		for (int i = 1; i <= WD30_T_COUNT; i++) {
			Name = "t" + IntToStr(i);
			Values = Values + ", " + Name + "=:" + Name;
		}
		Values.Delete(1, 2);

		SQLAdd(Query, IDS_SQL_UPDATE);
		SQLAdd(Query, IDS_SQL_TABLE_WD30_S_MYSQL);
		SQLAdd(Query, IDS_SQL_SET);
		SQLAdd(Query, Values);
		SQLAdd(Query, IDS_SQL_WHERE);
		SQLAdd(Query, "scales=:scales");
		SQLAdd(Query, IDS_SQL_AND);
		SQLAdd(Query, "bdatetime=:bdatetime");

		// WriteToLog(Query->SQL->Text);

		SQLSetParam(Query, "scales", Settings->WD30ScaleNum);
		SQLSetParam(Query, "bdatetime", Record->DateTime);

		for (int i = 1; i <= WD30_Z_COUNT; i++) {
			Name = "m" + IntToStr(i);
			if (Record->Z->Z[i] != WD30_Z_NULL_VALUE) {
				SQLSetParam(Query, Name, Record->Z->Z[i]);
			}
			else {
				Query->Parameters->ParamByName(Name)->DataType = ftBoolean;
				Query->Parameters->ParamByName(Name)->Value = Null();
			}
		}
		for (int i = 1; i <= WD30_T_COUNT; i++) {
			Name = "t" + IntToStr(i);
			if (Record->T->T[i] != WD30_T_NULL_VALUE) {
				SQLSetParam(Query, Name, Record->T->T[i]);
			}
			else {
				Query->Parameters->ParamByName(Name)->DataType = ftBoolean;
				Query->Parameters->ParamByName(Name)->Value = Null();
			}
		}
	}

	Query->Prepared = true;

	SQLExec(Query);
}

// ---------------------------------------------------------------------------
int __fastcall SortLogsByDateTime(TStringList * List, int Index1, int Index2) {
	String S1 = ExtractFileName(List->Strings[Index1]);
	String S2 = ExtractFileName(List->Strings[Index2]);
	// WDyn.log
	// WDyn_01012020_155358.log
	S1 = S1.SubString(5, S1.Length() - 8);
	S2 = S2.SubString(5, S2.Length() - 8);

	if (S1.IsEmpty()) {
		return 1;
	}

	if (S2.IsEmpty()) {
		return -1;
	}

	// 0000000001111111
	// 1234567890123456
	// _01012020_155358
	return CompareDateTime(EncodeDateTime(StrToInt(S1.SubString(6, 4)),
		StrToInt(S1.SubString(4, 2)), StrToInt(S1.SubString(2, 2)),
		StrToInt(S1.SubString(11, 2)), StrToInt(S1.SubString(13, 2)),
		StrToInt(S1.SubString(15, 2)), 0),
		EncodeDateTime(StrToInt(S2.SubString(6, 4)),
		StrToInt(S2.SubString(4, 2)), StrToInt(S2.SubString(2, 2)),
		StrToInt(S2.SubString(11, 2)), StrToInt(S2.SubString(13, 2)),
		StrToInt(S2.SubString(15, 2)), 0));
}

// ---------------------------------------------------------------------------
void MainFunctionWD30(TSettings * Settings) {
	ULONGLONG FirstTick = StartTimer();

	CheckSettings(Settings);

	TADOConnection * ConnectionServer = new TADOConnection(NULL);

	TADOQuery * QueryServer = new TADOQuery(NULL);

	QueryServer->Connection = ConnectionServer;

	OpenMySQLConnection(Settings, ConnectionServer);

	TWD30ZRecordList * ZRecords = new TWD30ZRecordList();
	TWD30TRecordList * TRecords = new TWD30TRecordList();
	TWD30SRecordList * SRecords = new TWD30SRecordList();

	TStringList * LogFiles = new TStringList();

	TStringList * LogFilesSyncList = new TStringList();
	TStringList * ZSyncList = new TStringList();
	TStringList * TSyncList = new TStringList();
	TStringList * SSyncList = new TStringList();

	int NU;
	int NewZCount = 0, NewTCount = 0, NewSCount = 0;

	try {
		WD30FindLogs(Settings->WD30Logs, LogFiles);
		try {
			LogFiles->CustomSort(SortLogsByDateTime);
		}
		catch (...) {
		}

		WD30LoadSyncList(LogFilesSyncList, 0);
		WD30LoadSyncList(ZSyncList, 1);
		WD30LoadSyncList(TSyncList, 2);
		WD30LoadSyncList(SSyncList, 3);

		String LogName;
		String LogNameOnly;
		String SyncID;

		for (int i = 0; i < LogFiles->Count; i++) {
			LogName = LogFiles->Strings[i];
			LogNameOnly = ExtractFileName(LogName);

			if (!IsCurrentLog(LogNameOnly)) {
				if (LogFilesSyncList->Find(LogNameOnly, NU)) {
					continue;
				}
			}

			ZRecords->Clear();
			TRecords->Clear();
			SRecords->Clear();

			WD30Load(LogName, ZRecords, TRecords, SRecords);

			// ----------- Нули ----------------------------------------------
			for (int i = 0; i < ZRecords->Count; i++) {
				SyncID = DateTimeToWD30SyncStr(ZRecords->Items[i]->DateTime);

				if (!ZSyncList->Find(SyncID, NU)) {
					try {
						WD30ZSaveToServer(Settings, ZRecords->Items[i],
							QueryServer, true);
					}
					catch (Exception &E) {
						WD30ZSaveToServer(Settings, ZRecords->Items[i],
							QueryServer, false);
					}

					ZSyncList->Add(SyncID);

					NewZCount++;

					ProcMess();
					if (CheckExit()) {
						throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
					}
				}
			}

			// ----------- Температуры ---------------------------------------
			for (int i = 0; i < TRecords->Count; i++) {
				SyncID = DateTimeToWD30SyncStr(TRecords->Items[i]->DateTime);

				if (!TSyncList->Find(SyncID, NU)) {
					try {
						WD30TSaveToServer(Settings, TRecords->Items[i],
							QueryServer, true);
					}
					catch (Exception &E) {
						WD30TSaveToServer(Settings, TRecords->Items[i],
							QueryServer, false);
					}

					TSyncList->Add(SyncID);

					NewTCount++;

					ProcMess();
					if (CheckExit()) {
						throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
					}
				}
			}

			// ----------- Датчики -------------------------------------------
			for (int i = 0; i < SRecords->Count; i++) {
				SyncID = DateTimeToWD30SyncStr(SRecords->Items[i]->DateTime);

				if (!SSyncList->Find(SyncID, NU)) {
					if (WD30SLoadFromServer(Settings, SRecords->Items[i],
						QueryServer)) {
						try {
							WD30SSaveToServer(Settings, SRecords->Items[i],
								QueryServer, true);
						}
						catch (Exception &E) {
							WD30SSaveToServer(Settings, SRecords->Items[i],
								QueryServer, false);
						}

						NewSCount++;
					}

					SSyncList->Add(SyncID);

					ProcMess();
					if (CheckExit()) {
						throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
					}
				}
			}

			try {
				if (NewZCount > 0) {
					ZSyncList->SaveToFile(GetSyncFileFullName(SYNC_WD30Z));
				}
				if (NewTCount > 0) {
					TSyncList->SaveToFile(GetSyncFileFullName(SYNC_WD30T));
				}
				if (NewSCount > 0) {
					SSyncList->SaveToFile(GetSyncFileFullName(SYNC_WD30S));
				}

				if (!IsCurrentLog(LogNameOnly)) {
					LogFilesSyncList->Add(LogNameOnly);
					LogFilesSyncList->SaveToFile
						(GetSyncFileFullName(SYNC_WD30LOGS));
				}
			}
			catch (...) {
				throw Exception(IDS_LOG_ERROR_SAVE_SYNCFILE);
			}

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		WriteToLog(Format(IDS_LOG_WD30_DATA_SAVED,
			ARRAYOFCONST((NewZCount, NewTCount, NewSCount,
			StopTimer(FirstTick)))));
	}
	__finally {
		SRecords->Free();
		TRecords->Free();
		ZRecords->Free();

		SSyncList->Free();
		TSyncList->Free();
		ZSyncList->Free();
		LogFilesSyncList->Free();
		LogFiles->Free();

		QueryServer->Free();

		ConnectionServer->Free();
	}
}

// ---------------------------------------------------------------------------
