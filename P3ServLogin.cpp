// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsMisc.h>

#include "P3ServDebug.h"

#include "P3ServStrings.h"

#include "P3ServLogin.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmLogin::TfrmLogin(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmLogin::Show(String RightPass) {
	bool Result = false;

	TfrmLogin * frmLogin = new TfrmLogin(Application);
	try {
		frmLogin->RightPass = RightPass;

		Result = frmLogin->ShowModal() == mrOk;
	}
	__finally {
		delete frmLogin;
	}

	WriteToLog(Result ? IDS_LOG_LOGIN_OK : IDS_LOG_LOGIN_CANCEL);

	return Result;
}

// ---------------------------------------------------------------------------
bool TfrmLogin::CheckPass() {
	if (!AnsiSameStr(ePass->Text, RightPass)) {
		ePass->Clear();
		ePass->SetFocus();

		MsgBoxErr(IDS_ERROR_PASS_WRONG);

		return false;
	}

	return true;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmLogin::btnOkClick(TObject *Sender) {
	if (!CheckPass()) {
		ModalResult = mrNone;
	}
}

// ---------------------------------------------------------------------------
