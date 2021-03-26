// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <FileCtrl.hpp>

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "P3ServDebug.h"

#include "P3ServAdd.h"
#include "P3ServStrings.h"

#include "P3ServOptions.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptions::Show(TSettings * Settings) {
	bool Result = false;

	TfrmOptions * frmOptions = new TfrmOptions(Application);
	try {
		frmOptions->Settings->Assign(Settings);

		frmOptions->UpdateForm();

		Result = frmOptions->ShowModal() == mrOk;
	}
	__finally {
		delete frmOptions;
	}

	WriteToLog(Result ? IDS_LOG_OPTIONS_OK : IDS_LOG_OPTIONS_CANCEL);

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormCreate(TObject *Sender) {
	Settings = new TSettings();

#ifndef _DEBUG
	PageControl->ActivePageIndex = 0;
#endif

	rgProgramMode->Items->AddObject(tsAglodoza->Caption, (TObject*)pmAglodoza);
	rgProgramMode->Items->AddObject(tsDomna->Caption, (TObject*)pmDomna);
	rgProgramMode->Items->AddObject(tsKoksohim->Caption, (TObject*)pmKoksohim);
	rgProgramMode->Items->AddObject(tsKanat->Caption, (TObject*)pmKanat);
	rgProgramMode->Items->AddObject(tsWD30->Caption, (TObject*)pmWD30);

	btnCheckMySQL->Tag = pmUnknown;
	btnCheckAglodoza->Tag = pmAglodoza;
	btnCheckDomna->Tag = pmDomna;
	btnCheckKoksohim->Tag = pmKoksohim;
	btnCheckKanat->Tag = pmKanat;

	btnAglodozaDatabase->Tag = pmAglodoza;
	btnDomnaDatabase->Tag = pmDomna;
	btnKoksohimDatabase->Tag = pmKoksohim;
	btnKanatDatabase->Tag = pmKanat;

	cboxTimerPeriod->Items->AddObject("Отключено", (TObject*)0);
	cboxTimerPeriod->Items->AddObject("Ежеминутно", (TObject*)1);
	cboxTimerPeriod->Items->AddObject("5 минут", (TObject*)5);
	cboxTimerPeriod->Items->AddObject("10 минут", (TObject*)10);
	cboxTimerPeriod->Items->AddObject("15 минут", (TObject*)15);
	cboxTimerPeriod->Items->AddObject("20 минут", (TObject*)20);
	cboxTimerPeriod->Items->AddObject("Полчаса", (TObject*)30);
	cboxTimerPeriod->Items->AddObject("Ежечасно", (TObject*)60);
	cboxTimerPeriod->DropDownCount = 8;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormDestroy(TObject *Sender) {
	Settings->Free();
}

// ---------------------------------------------------------------------------
void TfrmOptions::UpdateForm() {
	eOptionsPass->Text = Settings->OptionsPass;
	eOptionsPass2->Text = Settings->OptionsPass;

	for (int i = 0; i < rgProgramMode->Items->Count; i++) {
		if ((int)rgProgramMode->Items->Objects[i] == Settings->ProgramMode) {
			rgProgramMode->ItemIndex = i;
			break;
		}
	}

	for (int i = 0; i < cboxTimerPeriod->Items->Count; i++) {
		if ((int)cboxTimerPeriod->Items->Objects[i] == Settings->TimerPeriod) {
			cboxTimerPeriod->ItemIndex = i;
			break;
		}
	}
	seTimerPeriodStart->Value = Settings->TimerPeriodStart;

	eMySQLHost->Text = Settings->MySQLHost;
	eMySQLUser->Text = Settings->MySQLUser;
	eMySQLPass->Text = Settings->MySQLPass;

	eAglodozaScaleNum->Text = IntToStr(Settings->AglodozaScaleNum);
	eAglodozaDatabase->Text = Settings->AglodozaDatabase;

	eDomnaScaleNum->Text = IntToStr(Settings->DomnaScaleNum);
	eDomnaDatabase->Text = Settings->DomnaDatabase;
	eDomnaPass->Text = Settings->DomnaPass;
	cboxHumidity->Checked = Settings->DomnaHumidity;

	eKoksohimScaleNum->Text = IntToStr(Settings->KoksohimScaleNum);
	eKoksohimDatabase->Text = Settings->KoksohimDatabase;

	eKanatScaleNum->Text = IntToStr(Settings->KanatScaleNum);
	eKanatDatabase->Text = Settings->KanatDatabase;

	eWD30ScaleNum->Text = IntToStr(Settings->WD30ScaleNum);
	eWD30Logs->Text = Settings->WD30Logs;
}

// ---------------------------------------------------------------------------
void TfrmOptions::UpdateSettings() {
	Settings->OptionsPass = eOptionsPass->Text;

	Settings->ProgramMode =
		(TProgramMode)rgProgramMode->Items->Objects[rgProgramMode->ItemIndex];

	Settings->TimerPeriod =
		(int)cboxTimerPeriod->Items->Objects[cboxTimerPeriod->ItemIndex];
	Settings->TimerPeriodStart = seTimerPeriodStart->Value;

	Settings->MySQLHost = eMySQLHost->Text;
	Settings->MySQLUser = eMySQLUser->Text;
	Settings->MySQLPass = eMySQLPass->Text;

	Settings->AglodozaScaleNum = StrToInt(eAglodozaScaleNum->Text);
	Settings->AglodozaDatabase = eAglodozaDatabase->Text;

	Settings->DomnaScaleNum = StrToInt(eDomnaScaleNum->Text);
	Settings->DomnaDatabase = eDomnaDatabase->Text;
	Settings->DomnaPass = eDomnaPass->Text;
	Settings->DomnaHumidity = cboxHumidity->Checked;

	Settings->KoksohimScaleNum = StrToInt(eKoksohimScaleNum->Text);
	Settings->KoksohimDatabase = eKoksohimDatabase->Text;

	Settings->KanatScaleNum = StrToInt(eKanatScaleNum->Text);
	Settings->KanatDatabase = eKanatDatabase->Text;

	Settings->WD30ScaleNum = StrToInt(eWD30ScaleNum->Text);
	Settings->WD30Logs = eWD30Logs->Text;
}

void TfrmOptions::ControlSetFocus(TWinControl * Control) {
	TTabSheet * TabSheet;

	if (Control->Parent->ClassNameIs("TTabSheet")) {
		TabSheet = (TTabSheet*)Control->Parent;
	}
	else if (Control->Parent->Parent->ClassNameIs("TTabSheet")) {
		TabSheet = (TTabSheet*)Control->Parent->Parent;
	}

	PageControl->ActivePage = TabSheet;
	Control->SetFocus();
}

void TfrmOptions::CheckEmptyEditNum(TCustomEdit * Edit) {
	if (IsEmpty(Edit->Text)) {
		Edit->Text = "0";
	}
}

bool TfrmOptions::CheckEdit(TCustomEdit * Edit, NativeUInt Message) {
	if (Edit == NULL) {
		return true;
	}

	try {
		StrToInt(Edit->Text);

		return true;
	}
	catch (...) {
		ControlSetFocus(Edit);
		MsgBoxErr(Message);
	}

	return false;
}

bool TfrmOptions::CheckFileExists(TCustomEdit * Edit) {
	if (Edit == NULL) {
		return true;
	}

	if (FileExists(Edit->Text)) {
		return true;
	}

	if (MsgBoxYesNo(Format(IDS_ERROR_LOCAL_DB_NOT_EXISTS, Edit->Text))) {
		return true;
	}
	else {
		ControlSetFocus(Edit);

		return false;
	}
}

bool TfrmOptions::CheckFolderExists(TCustomEdit * Edit) {
	if (Edit == NULL) {
		return true;
	}

	if (DirectoryExists(Edit->Text)) {
		return true;
	}

	if (MsgBoxYesNo(Format(IDS_ERROR_LOCAL_DB_NOT_EXISTS, Edit->Text))) {
		return true;
	}
	else {
		ControlSetFocus(Edit);

		return false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnOkClick(TObject *Sender) {
	if (!AnsiSameStr(eOptionsPass->Text, eOptionsPass2->Text)) {
		MsgBoxErr(IDS_ERROR_CHECK_PASS);

		ControlSetFocus(eOptionsPass);

		return;
	}

	TCustomEdit * eScaleNum;
	TCustomEdit * eDatabase;

	bool CheckFile = true;

	switch (rgProgramMode->ItemIndex + 1) {
	case pmAglodoza:
		eScaleNum = eAglodozaScaleNum;
		eDatabase = eAglodozaDatabase;
		break;
	case pmDomna:
		eScaleNum = eDomnaScaleNum;
		eDatabase = eDomnaDatabase;
		break;
	case pmKoksohim:
		eScaleNum = eKoksohimScaleNum;
		eDatabase = eKoksohimDatabase;
		break;
	case pmKanat:
		eScaleNum = eKanatScaleNum;
		eDatabase = eKanatDatabase;
		break;
	case pmWD30:
		eScaleNum = eWD30ScaleNum;
		eDatabase = eWD30Logs;
		CheckFile = false;
		break;
	}

	if (!CheckEdit(eScaleNum, IDS_ERROR_NEED_INT)) {
		return;
	}

	if (CheckFile) {
		if (!CheckFileExists(eDatabase)) {
			return;
		}
	}
	else {
		if (!CheckFolderExists(eDatabase)) {
			return;
		}
	}

	CheckEmptyEditNum(eAglodozaScaleNum);
	CheckEmptyEditNum(eDomnaScaleNum);
	CheckEmptyEditNum(eKoksohimScaleNum);
	CheckEmptyEditNum(eKanatScaleNum);
	CheckEmptyEditNum(eWD30ScaleNum);

	UpdateSettings();

	if (Settings->Save()) {
		ModalResult = mrOk;
	}
	else {
		MsgBoxErr(IDS_ERROR_SAVE_SETTINGS);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnAglodozaDatabaseClick(TObject *Sender) {
	if (OpenDialog->Execute()) {
		switch (((TButton*)Sender)->Tag) {
		case pmAglodoza:
			eAglodozaDatabase->Text = OpenDialog->FileName;
			break;
		case pmKoksohim:
			eKoksohimDatabase->Text = OpenDialog->FileName;
			break;
		case pmDomna:
			eDomnaDatabase->Text = OpenDialog->FileName;
			break;
		case pmKanat:
			eKanatDatabase->Text = OpenDialog->FileName;
			break;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnWD30LogsClick(TObject *Sender) {
	String Path = eWD30Logs->Text;

	if (SelectDirectory("", "", Path)) {
		eWD30Logs->Text = Path;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnCheckMySQLClick(TObject *Sender) {
	UpdateSettings();

	TADOConnection * Connection = new TADOConnection(NULL);

	PageControl->Enabled = false;
	ShowWaitCursor();

	String Database;
	try {
		try {
			switch (((TButton*)Sender)->Tag) {
			case pmUnknown:
				Database = "mysql";
				OpenMySQLConnection(Settings, Connection);
				break;
			case pmAglodoza:
				Database = "aglodoza";
				Settings->ProgramMode = pmAglodoza;
				OpenAccessConnection(Settings, Connection);
				break;
			case pmDomna:
				Database = "domna";
				Settings->ProgramMode = pmDomna;
				OpenAccessConnection(Settings, Connection);
				break;
			case pmKoksohim:
				Database = "koksohim";
				Settings->ProgramMode = pmKoksohim;
				break;
			case pmKanat:
				Database = "kanat";
				Settings->ProgramMode = pmKanat;
				OpenAccessConnection(Settings, Connection);
				break;
			case pmWD30:
				Database = "wd30";
				Settings->ProgramMode = pmWD30;
				break;
			default:
				return;
			}

			WriteToLog(Format(IDS_LOG_DATABASE_CHECK_RESULT,
				ARRAYOFCONST((Database, "ok"))));
			MsgBox(LoadStr(IDS_TEXT_DATABASE_CHECK_OK));
		}
		catch (Exception &E) {
			WriteToLog(Format(IDS_LOG_DATABASE_CHECK_RESULT,
				ARRAYOFCONST((Database, E.Message))));
			MsgBoxErr(LoadStr(IDS_TEXT_DATABASE_CHECK_FAIL));
		}
	}
	__finally {
		Connection->Free();

		RestoreCursor();
		PageControl->Enabled = true;
	}
}

// ---------------------------------------------------------------------------
