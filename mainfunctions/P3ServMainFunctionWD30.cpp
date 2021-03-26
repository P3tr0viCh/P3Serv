// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsStr.h>
#include <UtilsLog.h>
#include <UtilsMisc.h>

#include "P3ServStrings.h"

#include "P3ServAdd.h"
#include "P3ServTWD30ZRecord.h"
#include "P3ServTWD30TRecord.h"
#include "P3ServTWD30SensorsRecord.h"

#include "P3ServMainFunctionWD30.h"

// 18.03.2021 00:59:49.919
#define WD30_LOG_DATETIME 23

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void WD30LoadLogFilesSyncList(TStringList * LogFilesSyncList) {
	String FileName = GetSyncFileFullName(SYNC_WD30LOGS);

	if (FileExists(FileName)) {
		LogFilesSyncList->LoadFromFile(FileName);
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
void WD30Load(String LogName, TWD30ZRecordList * ZRecords,
	TWD30TRecordList * TRecords, TWD30SensorsRecordList * SensorsRecords) {

	TWD30ZRecord * ZRecord;
	TWD30TRecord * TRecord;
	TWD30SensorsRecord * SensorsRecord;

	TFormatSettings FormatSettings;
	FormatSettings.DecimalSeparator = '.';

	TStringList * LogFile = new TStringList();

	try {
		LogFile->LoadFromFile(LogName);

		int P;
		int ZIndex;
		int TIndex;

		String S;
		String D;
		String V;

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

			// ----------- Нули ----------------------------------------------
			// Под каждое значение отведено 7 символов

			if (S[WD30_LOG_DATETIME + 2] == 'Z') {
				D = S.SubString(1, WD30_LOG_DATETIME);

				S.Delete(1, WD30_LOG_DATETIME + 2);

				ZRecord = new TWD30ZRecord();

				ZRecord->DateTime = StrToDateTime(D);

				ZIndex = 1;

				while (!S.IsEmpty()) {
					V = S.SubString(1, 7);

					ZRecord->Z[ZIndex] = StrToInt(V);

					ZIndex++;

					S.Delete(1, 7);
				}

				ZRecords->Add(ZRecord);

				continue;
			}

			// ----------- Температуры ---------------------------------------
			// Температура дублируется, разница - 1 пробел и 2 пробела

			if (S[WD30_LOG_DATETIME + 2] == 'T') {
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

				TIndex = 1;

				S = S + " ";

				while (!S.IsEmpty()) {
					P = S.Pos(" ");

					V = S.SubString(1, P - 1);

					TRecord->T[TIndex] = StrToFloat(V, FormatSettings);

					TIndex++;

					S.Delete(1, P);
				}

				TRecords->Add(TRecord);

				continue;
			}

			// ----------- Sensors -------------------------------------------
			P = S.Pos(" LocPos ");

			if (P > 0) {
				D = S.SubString(1, P - 1);

				S.Delete(1, P + 3);

				SensorsRecord = new TWD30SensorsRecord();

				SensorsRecord->DateTime = StrToDateTime(D);

				// TIndex = 1;
				//
				// S = S + " ";
				//
				// while (!S.IsEmpty()) {
				// P = S.Pos(" ");
				//
				// V = S.SubString(1, P - 1);
				//
				// TRecord->T[TIndex] = StrToFloat(V, FormatSettings);
				//
				// TIndex++;
				//
				// S.Delete(1, P);
				// }

				SensorsRecords->Add(SensorsRecord);

				continue;
			}
		}
	}
	__finally {
		LogFile->Free();
	}
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
	TWD30SensorsRecordList * SensorsRecords = new TWD30SensorsRecordList();

	TStringList * LogFiles = new TStringList();
	TStringList * LogFilesSyncList = new TStringList();

	int NU;

	try {
		WD30FindLogs(Settings->WD30Logs, LogFiles);

		WD30LoadLogFilesSyncList(LogFilesSyncList);

		String LogName;
		String LogNameOnly;

		for (int i = 0; i < LogFiles->Count; i++) {
			LogName = LogFiles->Strings[i];
			LogNameOnly = ExtractFileName(LogName);

			if (!IsCurrentLog(LogNameOnly)) {
				if (LogFilesSyncList->Find(LogNameOnly, NU)) {
					continue;
				}
			}

			WD30Load(LogName, ZRecords, TRecords, SensorsRecords);

			for (int i = 0; i < ZRecords->Count; i++) {
				WriteToLog(ZRecords->Items[i]->ToString());
			}

			for (int i = 0; i < TRecords->Count; i++) {
				WriteToLog(TRecords->Items[i]->ToString());
			}

			for (int i = 0; i < SensorsRecords->Count; i++) {
				WriteToLog(SensorsRecords->Items[i]->ToString());
			}

			if (!IsCurrentLog(LogNameOnly)) {
				LogFilesSyncList->Add(LogNameOnly);
				try {
					LogFilesSyncList->SaveToFile
						(GetSyncFileFullName(SYNC_WD30LOGS));
				}
				catch (...) {
					throw Exception(IDS_LOG_ERROR_SAVE_SYNCFILE);
				}
			}

			ProcMess();
			if (CheckExit()) {
				throw EAbort(IDS_LOG_ERROR_TERMINATED_IN_WORK_PROGRESS);
			}
		}

		// WriteToLog(Format(IDS_LOG_WD30_DATA_SAVED,
		// ARRAYOFCONST((SyncListNewValues->Count, StopTimer(FirstTick)))));
	}
	__finally {
		SensorsRecords->Free();
		TRecords->Free();
		ZRecords->Free();

		LogFilesSyncList->Free();
		LogFiles->Free();

		QueryServer->Free();

		ConnectionServer->Free();
	}
}

// ---------------------------------------------------------------------------
