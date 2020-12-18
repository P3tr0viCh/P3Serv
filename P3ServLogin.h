// ---------------------------------------------------------------------------

#ifndef P3ServLoginH
#define P3ServLoginH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TfrmLogin : public TForm {
__published:
	TButton *btnOk;
	TButton *btnCancel;
	TLabeledEdit *ePass;
	void __fastcall btnOkClick(TObject *Sender);

private:
	String RightPass;

public:
	__fastcall TfrmLogin(TComponent* Owner);

	static bool Show(String RightPass);

	bool CheckPass();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmLogin *frmLogin;
// ---------------------------------------------------------------------------
#endif
