// ---------------------------------------------------------------------------

#ifndef P3ServAddH
#define P3ServAddH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>

#include "P3ServTSettings.h"

#define SYNC_FOLDER "sync"
#define SYNC_EXT ".sync"

// ---------------------------------------------------------------------------
void CheckSettings(TSettings * Settings);

String GetMySQLConnectionString(TSettings * Settings);
String GetAccessConnectionString(TSettings * Settings);

void OpenMySQLConnection(TSettings * Settings, TADOConnection * Connection);
void OpenAccessConnection(TSettings * Settings, TADOConnection * Connection);

void CheckConnections(TSettings * Settings);

// ---------------------------------------------------------------------------
void SQLAdd(TADOQuery * Query, String Text);
void SQLAdd(TADOQuery * Query, NativeUInt Ident);

// ---------------------------------------------------------------------------
void SQLSetParam(TADOQuery * Query, String ParamName, int Value);
void SQLSetParam(TADOQuery * Query, String ParamName, float Value);
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
