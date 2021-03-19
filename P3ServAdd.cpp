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

	int ScaleNum;
	String Database = "";
	String ProgramMode = "";

	switch (Settings->ProgramMode) {
	case pmAglodoza:
		ScaleNum = Settings->AglodozaScaleNum;
		Database = Settings->AglodozaDatabase;
		ProgramMode = "aglodoza";
		break;
	case pmDomna:
		ScaleNum = Settings->DomnaScaleNum;
		Database = Settings->DomnaDatabase;
		ProgramMode = "domna";
		break;
	case pmKoksohim:
		ScaleNum = Settings->KoksohimScaleNum;
		Database = Settings->KoksohimDatabase;
		ProgramMode = "koksohim";
		break;
	case pmKanat:
		ScaleNum = Settings->KanatScaleNum;
		Database = Settings->KanatDatabase;
		ProgramMode = "kanat";
		break;
	default:
		throw EIniFileException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
			"program mode"));
	}

	if (ScaleNum == 0 || IsEmpty(Database)) {
		throw EIniFileException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
			ProgramMode));
	}

	if (!FileExists(Database)) {
		throw EFileNotFoundException(Format(IDS_LOG_ERROR_CHECK_SETTINGS,
			ProgramMode + " (database not exists)"));
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
	case pmAglodoza:
		Database = Settings->AglodozaDatabase;
		User = Settings->AglodozaUser;
		Pass = Settings->AglodozaPass;
		break;
	case pmDomna:
		Database = Settings->DomnaDatabase;
		User = Settings->DomnaUser;
		Pass = Settings->DomnaPass;
		break;
	case pmKanat:
		Database = Settings->KanatDatabase;
		User = Settings->KanatUser;
		Pass = Settings->KanatPass;
		break;
	default:
		throw Exception("GetAccessConnectionString");
	}

	return Format(IDS_CONNECTION_ACCESS, ARRAYOFCONST((Database, User, Pass)));
}

void OpenMySQLConnection(TSettings * Settings, TADOConnection * Connection) {
	Connection->ConnectionString = GetMySQLConnectionString(Settings);

	// WriteToLog(Connection->ConnectionString);

	try {
		Connection->Open();
	}
	catch (Exception &E) {
		throw Exception(Format(IDS_LOG_ERROR_SERVER_DB_OPEN, E.Message));
	}
}

// ---------------------------------------------------------------------------
void OpenAccessConnection(TSettings * Settings, TADOConnection * Connection) {
	Connection->ConnectionString = GetAccessConnectionString(Settings);

	// WriteToLog(Connection->ConnectionString);

	try {
		Connection->Open();
	}
	catch (Exception &E) {
		throw Exception(Format(IDS_LOG_ERROR_LOCAL_DB_OPEN, E.Message));
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
void SQLSetParam(TADOQuery * Query, String ParamName, float Value) {
	Query->Parameters->ParamByName(ParamName)->DataType = ftFloat;
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
