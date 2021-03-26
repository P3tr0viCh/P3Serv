// ---------------------------------------------------------------------------

#ifndef P3ServTSettingsH
#define P3ServTSettingsH

#include <System.Classes.hpp>
#include <System.IniFiles.hpp>

#define CFG_EXT ".cfg"

#define CHECK_CRC

// ---------------------------------------------------------------------------
enum TProgramMode {
	pmUnknown, pmAglodoza, pmDomna, pmKoksohim, pmKanat, pmWD30
};

// ---------------------------------------------------------------------------
class TSettings : public TObject {
private:
	String FConfigFileName;

	String FOptionsPass;

	TProgramMode FProgramMode;

	int FTimerPeriod;
	int FTimerPeriodStart;

	// MySQL
	String FMySQLHost;
	String FMySQLPort;
	String FMySQLDatabase;
	String FMySQLUser;
	String FMySQLPass;

	// Аглодозировка
	int FAglodozaScaleNum;
	String FAglodozaDatabase;
	String FAglodozaUser;
	String FAglodozaPass;
	// Доменная печь
	int FDomnaScaleNum;
	String FDomnaDatabase;
	String FDomnaUser;
	String FDomnaPass;
	bool FDomnaHumidity;
	// Коксохим
	int FKoksohimScaleNum;
	String FKoksohimDatabase;
	// Канатная дорога
	int FKanatScaleNum;
	String FKanatDatabase;
	String FKanatUser;
	String FKanatPass;
	// ВД-30
	int FWD30ScaleNum;
	String FWD30Logs;

	String GetConfigFileName();

	String CRC(String Text);

	String Encrypt(String Text);
	String Decrypt(String Text);

	String GetCRC();
	void CheckCRC(String CRC);

	void LoadSettings();
	void SaveSettings();

public:
	__fastcall TSettings();
	__fastcall ~TSettings();

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TSettings * Source);
	String __fastcall ToString();

	bool Load();
	bool Save();

	__property String ConfigFileName = {read = FConfigFileName};

	__property String OptionsPass = {read = FOptionsPass, write = FOptionsPass};

	__property TProgramMode ProgramMode = {
		read = FProgramMode, write = FProgramMode};

	__property int TimerPeriod = {read = FTimerPeriod, write = FTimerPeriod};
	__property int TimerPeriodStart = {
		read = FTimerPeriodStart, write = FTimerPeriodStart};

	__property String MySQLHost = {read = FMySQLHost, write = FMySQLHost};
	__property String MySQLPort = {read = FMySQLPort, write = FMySQLPort};
	__property String MySQLDatabase = {
		read = FMySQLDatabase, write = FMySQLDatabase};
	__property String MySQLUser = {read = FMySQLUser, write = FMySQLUser};
	__property String MySQLPass = {read = FMySQLPass, write = FMySQLPass};

	__property int AglodozaScaleNum = {
		read = FAglodozaScaleNum, write = FAglodozaScaleNum};
	__property String AglodozaDatabase = {
		read = FAglodozaDatabase, write = FAglodozaDatabase};
	__property String AglodozaUser = {
		read = FAglodozaUser, write = FAglodozaUser};
	__property String AglodozaPass = {
		read = FAglodozaPass, write = FAglodozaPass};

	__property int DomnaScaleNum = {
		read = FDomnaScaleNum, write = FDomnaScaleNum};
	__property String DomnaDatabase = {
		read = FDomnaDatabase, write = FDomnaDatabase};
	__property String DomnaUser = {read = FDomnaUser, write = FDomnaUser};
	__property String DomnaPass = {read = FDomnaPass, write = FDomnaPass};
	__property bool DomnaHumidity = {
		read = FDomnaHumidity, write = FDomnaHumidity};

	__property int KoksohimScaleNum = {
		read = FKoksohimScaleNum, write = FKoksohimScaleNum};
	__property String KoksohimDatabase = {
		read = FKoksohimDatabase, write = FKoksohimDatabase};

	__property int KanatScaleNum = {
		read = FKanatScaleNum, write = FKanatScaleNum};
	__property String KanatDatabase = {
		read = FKanatDatabase, write = FKanatDatabase};
	__property String KanatUser = {read = FKanatUser, write = FKanatUser};
	__property String KanatPass = {read = FKanatPass, write = FKanatPass};

	__property int WD30ScaleNum = {read = FWD30ScaleNum, write = FWD30ScaleNum};
	__property String WD30Logs = {read = FWD30Logs, write = FWD30Logs};
};

// ---------------------------------------------------------------------------
#endif
