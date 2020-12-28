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

