// ---------------------------------------------------------------------------

#pragma hdrstop

#include <System.IniFiles.hpp>

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFiles.h>
#include <UtilsFileIni.h>
#include <UtilsCryptoPP.h>

#include "P3ServEncKey.h"

#include "P3ServDebug.h"

#include "P3ServStrings.h"

#include "P3ServTSettings.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TSettings::TSettings() {
	FConfigFileName = GetConfigFileName();

	FOptionsPass = "";

	FProgramMode = pmUnknown;

	FTimerPeriod = 0;
	FTimerPeriodStart = 0;

	FMySQLHost = "";
	FMySQLPort = "3306";
	FMySQLDatabase = "wdb3";
	FMySQLUser = "";
	FMySQLPass = "";

	FAglodozaScaleNum = 0;
	FAglodozaDatabase = "";
	FAglodozaUser = "Admin";
	FAglodozaPass = "";

	FDomnaScaleNum = 0;
	FDomnaDatabase = "";
	FDomnaUser = "Admin";
	FDomnaPass = "";
	FDomnaHumidity = false;

	FKoksohimScaleNum = 0;
	FKoksohimDatabase = "";

	FKanatScaleNum = 0;
	FKanatDatabase = "";
	FKanatUser = "Admin";
	FKanatPass = "";

	FWD30ScaleNum = 0;
	FWD30Logs = "C:\\WSys32d\\Log";
}

// ---------------------------------------------------------------------------
__fastcall TSettings::~TSettings() {
	//
}

// ---------------------------------------------------------------------------
bool __fastcall TSettings::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TSettings * Settings = (TSettings*) Obj;

	if (Settings->OptionsPass != OptionsPass)
		return false;

	if (Settings->ProgramMode != ProgramMode)
		return false;

	if (Settings->TimerPeriod != TimerPeriod)
		return false;
	if (Settings->TimerPeriodStart != TimerPeriodStart)
		return false;

	if (Settings->MySQLHost != MySQLHost)
		return false;
	if (Settings->MySQLPort != MySQLPort)
		return false;
	if (Settings->MySQLDatabase != MySQLDatabase)
		return false;
	if (Settings->MySQLUser != MySQLUser)
		return false;
	if (Settings->MySQLPass != MySQLPass)
		return false;

	if (Settings->AglodozaScaleNum != AglodozaScaleNum)
		return false;
	if (Settings->AglodozaDatabase != AglodozaDatabase)
		return false;
	if (Settings->AglodozaUser != AglodozaUser)
		return false;
	if (Settings->AglodozaPass != AglodozaPass)
		return false;

	if (Settings->DomnaScaleNum != DomnaScaleNum)
		return false;
	if (Settings->DomnaDatabase != DomnaDatabase)
		return false;
	if (Settings->DomnaUser != DomnaUser)
		return false;
	if (Settings->DomnaPass != DomnaPass)
		return false;
	if (Settings->DomnaHumidity != DomnaHumidity)
		return false;

	if (Settings->KoksohimScaleNum != KoksohimScaleNum)
		return false;
	if (Settings->KoksohimDatabase != KoksohimDatabase)
		return false;

	if (Settings->KanatScaleNum != KanatScaleNum)
		return false;
	if (Settings->KanatDatabase != KanatDatabase)
		return false;
	if (Settings->KanatUser != KanatUser)
		return false;
	if (Settings->KanatPass != KanatPass)
		return false;

	if (Settings->WD30ScaleNum != WD30ScaleNum)
		return false;
	if (Settings->WD30Logs != WD30Logs)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TSettings::Assign(TSettings * Source) {
	FOptionsPass = Source->OptionsPass;

	FProgramMode = Source->ProgramMode;

	FTimerPeriod = Source->TimerPeriod;
	FTimerPeriodStart = Source->TimerPeriodStart;

	FMySQLHost = Source->MySQLHost;
	FMySQLPort = Source->MySQLPort;
	FMySQLDatabase = Source->MySQLDatabase;
	FMySQLUser = Source->MySQLUser;
	FMySQLPass = Source->MySQLPass;

	FAglodozaScaleNum = Source->AglodozaScaleNum;
	FAglodozaDatabase = Source->AglodozaDatabase;
	FAglodozaUser = Source->AglodozaUser;
	FAglodozaPass = Source->AglodozaPass;

	FDomnaScaleNum = Source->DomnaScaleNum;
	FDomnaDatabase = Source->DomnaDatabase;
	FDomnaUser = Source->DomnaUser;
	FDomnaPass = Source->DomnaPass;
	FDomnaHumidity = Source->DomnaHumidity;

	FKoksohimScaleNum = Source->KoksohimScaleNum;
	FKoksohimDatabase = Source->KoksohimDatabase;

	FKanatScaleNum = Source->KanatScaleNum;
	FKanatDatabase = Source->KanatDatabase;
	FKanatUser = Source->KanatUser;
	FKanatPass = Source->KanatPass;

	FWD30ScaleNum = Source->WD30ScaleNum;
	FWD30Logs = Source->WD30Logs;
}

// ---------------------------------------------------------------------------
String __fastcall TSettings::ToString() {
	String S;

	S = "TSettings{";
	S += "OptionsPass='" + OptionsPass + "'";
	S += ",";
	S += "ProgramMode='" + IntToStr(ProgramMode) + "'";
	S += ",";
	S += "TimerPeriod='" + IntToStr(TimerPeriod) + "'";
	S += ",";
	S += "TimerPeriodStart='" + IntToStr(TimerPeriodStart) + "'";
	S += ",";

	S += "MySQLHost='" + MySQLHost + "'";
	S += ",";
	S += "MySQLPort='" + MySQLPort + "'";
	S += ",";
	S += "MySQLDatabase='" + MySQLDatabase + "'";
	S += ",";
	S += "MySQLUser='" + MySQLUser + "'";
	S += ",";
	S += "MySQLPass='" + MySQLPass + "'";

	S += ",";

	S += "AglodozaScaleNum='" + IntToStr(AglodozaScaleNum) + "'";
	S += ",";
	S += "AglodozaDatabase='" + AglodozaDatabase + "'";
	S += ",";
	S += "AglodozaUser='" + AglodozaUser + "'";
	S += ",";
	S += "AglodozaPass='" + AglodozaPass + "'";

	S += ",";

	S += "DomnaScaleNum='" + IntToStr(DomnaScaleNum) + "'";
	S += ",";
	S += "DomnaDatabase='" + DomnaDatabase + "'";
	S += ",";
	S += "DomnaUser='" + DomnaUser + "'";
	S += ",";
	S += "DomnaPass='" + DomnaPass + "'";
	S += ",";
	S += "DomnaHumidity='" + BoolToStr(DomnaHumidity) + "'";

	S += ",";

	S += "KoksohimScaleNum='" + IntToStr(KoksohimScaleNum) + "'";
	S += ",";
	S += "KoksohimDatabase='" + KoksohimDatabase + "'";

	S += ",";

	S += "KanatScaleNum='" + IntToStr(KanatScaleNum) + "'";
	S += ",";
	S += "KanatDatabase='" + KanatDatabase + "'";
	S += ",";
	S += "KanatUser='" + KanatUser + "'";
	S += ",";
	S += "KanatPass='" + KanatPass + "'";

	S += ",";

	S += "WD30ScaleNum='" + IntToStr(WD30ScaleNum) + "'";
	S += ",";
	S += "WD30Logs='" + WD30Logs + "'";

	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
String TSettings::GetConfigFileName() {
	return ChangeFileExt(Application->ExeName, CFG_EXT);
}

// ---------------------------------------------------------------------------
String TSettings::CRC(String Text) {
	try {
		return HashSHA256(Text);
	}
	catch (...) {
		return "";
	}
}

// ---------------------------------------------------------------------------
String TSettings::Encrypt(String Text) {
	if (IsEmpty(Text)) {
		return "";
	}

	try {
		return EncryptAES(Text, ENC_KEY);
	}
	catch (...) {
		return "";
	}
}

// ---------------------------------------------------------------------------
String TSettings::Decrypt(String Text) {
	if (IsEmpty(Text)) {
		return "";
	}

	try {
		return DecryptAES(Text, ENC_KEY);
	}
	catch (...) {
		throw EEncodingError("decrypt");
	}
}

// ---------------------------------------------------------------------------
String TSettings::GetCRC() {
	String S = ToString();
	S = CRC(S);
	S = Encrypt(S);
	return S;
}

// ---------------------------------------------------------------------------
void TSettings::CheckCRC(String S) {
#ifdef DISABLE_CHECK_CRC
	return;
#endif

	if (IsEmpty(S)) {
		throw EEncodingError(IDS_LOG_ERROR_CRC_EMPTY);
	}

	S = Decrypt(S);

	String RightCRC = ToString();
	// WriteToLog(RightCRC);
	RightCRC = CRC(RightCRC);

	if (!SameStr(S, RightCRC)) {
		throw EEncodingError(IDS_LOG_ERROR_CRC_WRONG);
	}
}

// ---------------------------------------------------------------------------
void TSettings::LoadSettings() {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	String Section;

	try {
		Section = "Main";
		OptionsPass = Decrypt(IniFile->ReadString(Section, "OptionsPass",
			OptionsPass));
		ProgramMode = (TProgramMode)IniFile->ReadInteger(Section, "ProgramMode",
			ProgramMode);
		TimerPeriod = IniFile->ReadInteger(Section, "TimerPeriod", TimerPeriod);
		TimerPeriodStart = IniFile->ReadInteger(Section, "TimerPeriodStart",
			TimerPeriodStart);

		Section = "ScaleInfo";
		AglodozaScaleNum = IniFile->ReadInteger(Section, "AglodozaNum",
			AglodozaScaleNum);
		KoksohimScaleNum = IniFile->ReadInteger(Section, "KoksohimNum",
			KoksohimScaleNum);
		DomnaScaleNum = IniFile->ReadInteger(Section, "DomnaNum",
			DomnaScaleNum);
		KanatScaleNum = IniFile->ReadInteger(Section, "KanatNum",
			KanatScaleNum);
		WD30ScaleNum = IniFile->ReadInteger(Section, "WD30Num", WD30ScaleNum);

		Section = "MySQLConnection";
		MySQLHost = IniFile->ReadString(Section, "Host", MySQLHost);
		MySQLPort = IniFile->ReadString(Section, "Port", MySQLPort);
		MySQLDatabase = IniFile->ReadString(Section, "Database", MySQLDatabase);
		MySQLUser = IniFile->ReadString(Section, "User", MySQLUser);
		MySQLPass = Decrypt(IniFile->ReadString(Section, "Pass", MySQLPass));

		Section = "AglodozaConnection";
		AglodozaDatabase = IniFile->ReadString(Section, "Database",
			AglodozaDatabase);
		AglodozaUser = IniFile->ReadString(Section, "User", AglodozaUser);
		AglodozaPass = Decrypt(IniFile->ReadString(Section, "Pass",
			AglodozaPass));

		Section = "DomnaConnection";
		DomnaDatabase = IniFile->ReadString(Section, "Database", DomnaDatabase);
		DomnaUser = IniFile->ReadString(Section, "User", DomnaUser);
		DomnaPass = Decrypt(IniFile->ReadString(Section, "Pass", DomnaPass));
		DomnaHumidity = IniFile->ReadBool(Section, "Humidity", DomnaHumidity);

		Section = "KoksohimConnection";
		KoksohimDatabase = IniFile->ReadString(Section, "Database",
			KoksohimDatabase);

		Section = "KanatConnection";
		KanatDatabase = IniFile->ReadString(Section, "Database", KanatDatabase);
		KanatUser = IniFile->ReadString(Section, "User", KanatUser);
		KanatPass = Decrypt(IniFile->ReadString(Section, "Pass", KanatPass));

		Section = "WD30Connection";
		WD30Logs = IniFile->ReadString(Section, "Logs", WD30Logs);

#ifdef CHECK_CRC
		CheckCRC(IniFile->ReadString("CRC", "CRC", ""));
#endif
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::SaveSettings() {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	String Section;

	try {
		IniFile->WriteString("CRC", "CRC", GetCRC());

		Section = "Main";
		IniFile->WriteString(Section, "OptionsPass", Encrypt(OptionsPass));
		IniFile->WriteInteger(Section, "ProgramMode", ProgramMode);
		IniFile->WriteInteger(Section, "TimerPeriod", TimerPeriod);
		IniFile->WriteInteger(Section, "TimerPeriodStart", TimerPeriodStart);

		Section = "ScaleInfo";
		IniFile->WriteString(Section, "AglodozaNum", AglodozaScaleNum);
		IniFile->WriteString(Section, "DomnaNum", DomnaScaleNum);
		IniFile->WriteString(Section, "KoksohimNum", KoksohimScaleNum);
		IniFile->WriteString(Section, "KanatNum", KanatScaleNum);
		IniFile->WriteString(Section, "WD30Num", WD30ScaleNum);

		Section = "MySQLConnection";
		IniFile->WriteString(Section, "Host", MySQLHost);
		IniFile->WriteString(Section, "Port", MySQLPort);
		IniFile->WriteString(Section, "Database", MySQLDatabase);
		IniFile->WriteString(Section, "User", MySQLUser);
		IniFile->WriteString(Section, "Pass", Encrypt(MySQLPass));

		Section = "AglodozaConnection";
		IniFile->WriteString(Section, "Database", AglodozaDatabase);
		IniFile->WriteString(Section, "User", AglodozaUser);
		IniFile->WriteString(Section, "Pass", Encrypt(AglodozaPass));

		Section = "DomnaConnection";
		IniFile->WriteString(Section, "Database", DomnaDatabase);
		IniFile->WriteString(Section, "User", DomnaUser);
		IniFile->WriteString(Section, "Pass", Encrypt(DomnaPass));
		IniFile->WriteBool(Section, "Humidity", DomnaHumidity);

		Section = "KoksohimConnection";
		IniFile->WriteString(Section, "Database", KoksohimDatabase);

		Section = "KanatConnection";
		IniFile->WriteString(Section, "Database", KanatDatabase);
		IniFile->WriteString(Section, "User", KanatUser);
		IniFile->WriteString(Section, "Pass", Encrypt(KanatPass));

		Section = "WD30Connection";
		IniFile->WriteString(Section, "Logs", WD30Logs);
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
bool TSettings::Load() {
	if (!FileExists(ConfigFileName)) {
		WriteToLog(Format(IDS_LOG_ERROR_LOAD_SETTINGS, "not exists"));

		return true;
	}

	try {
		LoadSettings();
	}
	catch (Exception &E) {
		WriteToLog(Format(IDS_LOG_ERROR_LOAD_SETTINGS, E.Message));

		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
bool TSettings::Save() {
	try {
		SaveSettings();
	}
	catch (Exception &E) {
		WriteToLog(Format(IDS_LOG_ERROR_SAVE_SETTINGS, E.Message));

		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
