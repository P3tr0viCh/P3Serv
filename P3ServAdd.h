// ---------------------------------------------------------------------------

#ifndef P3ServAddH
#define P3ServAddH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>

#include "P3ServTSettings.h"
#include "P3ServTDozSumRecord.h"
#include "P3ServTGroupSumRecord.h"
#include "P3ServTGroupsRecord.h"
#include "P3ServTKoksohimRecord.h"

#define SYNC_FOLDER "sync"
#define SYNC_EXT ".sync"
#define SYNC_KOKSOHIM "koksohim"

// ---------------------------------------------------------------------------
void CheckSettings(TSettings * Settings);

String GetMySQLConnectionString(TSettings * Settings);
String GetAccessConnectionString(TSettings * Settings);

void OpenMySQLConnection(TSettings * Settings, TADOConnection * Connection);
void OpenAccessConnection(TSettings * Settings, TADOConnection * Connection);

void CheckConnections(TSettings * Settings);

// ---------------------------------------------------------------------------
void AglodozaDozSumLoad(TSettings * Settings, TDozSumRecordList * Records,
	TADOQuery * Query);
void AglodozaGroupSumLoad(TSettings * Settings, TGroupSumRecordList * Records,
	TADOQuery * Query);
void AglodozaGroupsLoad(TSettings * Settings, TGroupsRecordList * Records,
	TADOQuery * Query);
// ---------------------------------------------------------------------------
void AglodozaDozSumSaveSend(TDozSumRecord * Record, TADOQuery * Query);
void AglodozaGroupSumSaveSend(TGroupSumRecord * Record, TADOQuery * Query);
void AglodozaGroupsSaveSend(TGroupsRecord * Record, TADOQuery * Query);
// ---------------------------------------------------------------------------
void AglodozaDozSumSaveToServer(TSettings * Settings, TDozSumRecord * Record,
	TADOQuery * Query);
void AglodozaGroupSumSaveToServer(TSettings * Settings,
	TGroupSumRecord * Record, TADOQuery * Query);
void AglodozaGroupsSaveToServer(TSettings * Settings, TGroupsRecord * Record,
	TADOQuery * Query);
// ---------------------------------------------------------------------------
void AglodozaDozSumDeleteFromServer(TSettings * Settings,
	TDozSumRecord * Record, TADOQuery * Query);
void AglodozaGroupSumDeleteFromServer(TSettings * Settings,
	TGroupSumRecord * Record, TADOQuery * Query);
void AglodozaGroupsDeleteFromServer(TSettings * Settings,
	TGroupsRecord * Record, TADOQuery * Query);

// ---------------------------------------------------------------------------
void KoksohimLoadSyncList(TStringList * SyncList);
void KoksohimLoad(TSettings * Settings, TKoksohimRecordList * Records);
void KoksohimSaveToServer(TSettings * Settings, TKoksohimRecord * Record,
	TADOQuery * Query);

// ---------------------------------------------------------------------------
void MainFunctionAglodoza(TSettings * Settings);
void MainFunctionKoksohim(TSettings * Settings);

// ---------------------------------------------------------------------------
void SQLAdd(TADOQuery * Query, String Text);
void SQLAdd(TADOQuery * Query, NativeUInt Ident);

// ---------------------------------------------------------------------------
void SQLSetParam(TADOQuery * Query, String ParamName, int Value);
void SQLSetParam(TADOQuery * Query, String ParamName, String Value);
void SQLSetParam(TADOQuery * Query, String ParamName, TDateTime Value);

// ---------------------------------------------------------------------------
void SQLExec(TADOQuery * Query);

// ---------------------------------------------------------------------------
String DateTimeToSQLStr(TDateTime ADateTime);
String DateTimeToKoksohimSyncStr(TDateTime ADateTime);
String FloatToSQLStr(float Value);

// ---------------------------------------------------------------------------
String GetSyncFolder();
String GetSyncFileFullName(String FileName);

// ---------------------------------------------------------------------------
#endif
