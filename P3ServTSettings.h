// ---------------------------------------------------------------------------

#ifndef P3ServTSettingsH
#define P3ServTSettingsH

#include <System.Classes.hpp>
#include <System.IniFiles.hpp>

#define CFG_EXT ".cfg"

// ---------------------------------------------------------------------------
enum TProgramMode {
	pmUnknown, pmAglodoza, pmKoksohim, pmDomna
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
	// Коксохим
	int FKoksohimScaleNum;
	String FKoksohimDatabase;
	// Доменная печь
	int FDomnaScaleNum;
	String FDomnaDatabase;
	String FDomnaUser;
	String FDomnaPass;

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

	__property int KoksohimScaleNum = {
		read = FKoksohimScaleNum, write = FKoksohimScaleNum};
	__property String KoksohimDatabase = {
		read = FKoksohimDatabase, write = FKoksohimDatabase};

	__property int DomnaScaleNum = {
		read = FDomnaScaleNum, write = FDomnaScaleNum};
	__property String DomnaDatabase = {
		read = FDomnaDatabase, write = FDomnaDatabase};
	__property String DomnaUser = {read = FDomnaUser, write = FDomnaUser};
	__property String DomnaPass = {read = FDomnaPass, write = FDomnaPass};
};

// ---------------------------------------------------------------------------
#endif
