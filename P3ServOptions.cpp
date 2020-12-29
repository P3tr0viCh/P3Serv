// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

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

	PageControl->ActivePageIndex = 0;

	rgProgramMode->Items->AddObject("�������������", (TObject*)pmAglodoza);
	rgProgramMode->Items->AddObject("�������� ����", (TObject*)pmDomna);
	rgProgramMode->Items->AddObject("�������� ���", (TObject*)pmKoksohim);

	btnCheckMySQL->Tag = pmUnknown;
	btnCheckAglodoza->Tag = pmAglodoza;
	btnCheckKoksohim->Tag = pmKoksohim;
	btnCheckDomna->Tag = pmDomna;

	btnAglodozaDatabase->Tag = pmAglodoza;
	btnKoksohimDatabase->Tag = pmKoksohim;
	btnDomnaDatabase->Tag = pmDomna;

	cboxTimerPeriod->Items->AddObject("���������", (TObject*)0);
	cboxTimerPeriod->Items->AddObject("����������", (TObject*)1);
	cboxTimerPeriod->Items->AddObject("5 �����", (TObject*)5);
	cboxTimerPeriod->Items->AddObject("10 �����", (TObject*)10);
	cboxTimerPeriod->Items->AddObject("15 �����", (TObject*)15);
	cboxTimerPeriod->Items->AddObject("20 �����", (TObject*)20);
	cboxTimerPeriod->Items->AddObject("�������", (TObject*)30);
	cboxTimerPeriod->Items->AddObject("��������", (TObject*)60);
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

	eKoksohimScaleNum->Text = IntToStr(Settings->KoksohimScaleNum);
	eKoksohimDatabase->Text = Settings->KoksohimDatabase;
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

	Settings->KoksohimScaleNum = StrToInt(eKoksohimScaleNum->Text);
	Settings->KoksohimDatabase = eKoksohimDatabase->Text;
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

bool TfrmOptions::CheckEdit(TCustomEdit * Edit, NativeUInt Message) {
	try {
		StrToInt(Edit->Text);

		return true;
	}
	catch (...) {
		MsgBoxErr(Message);
		ControlSetFocus(Edit);
	}

	return false;
}

bool TfrmOptions::CheckFileExists(TCustomEdit * Edit) {
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

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnOkClick(TObject *Sender) {
	if (!AnsiSameStr(eOptionsPass->Text, eOptionsPass2->Text)) {
		MsgBoxErr(IDS_ERROR_CHECK_PASS);

		ControlSetFocus(eOptionsPass);

		return;
	}

	switch (rgProgramMode->ItemIndex + 1) {
	case pmAglodoza:
		if (!CheckEdit(eAglodozaScaleNum, IDS_ERROR_NEED_INT)) {
			return;
		}

		if (!CheckFileExists(eAglodozaDatabase)) {
			return;
		}

		break;
	case pmKoksohim:
		if (!CheckEdit(eKoksohimScaleNum, IDS_ERROR_NEED_INT)) {
			return;
		}

		if (!CheckFileExists(eKoksohimDatabase)) {
			return;
		}

		break;
	case pmDomna:
		if (!CheckEdit(eDomnaScaleNum, IDS_ERROR_NEED_INT)) {
			return;
		}

		if (!CheckFileExists(eDomnaDatabase)) {
			return;
		}

		break;
	}

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
		}
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
