// ---------------------------------------------------------------------------

#ifndef P3ServOptionsH
#define P3ServOptionsH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>

#include "P3ServTSettings.h"
#include <Vcl.Samples.Spin.hpp>

// ---------------------------------------------------------------------------
class TfrmOptions : public TForm {
__published:
	TButton *btnOk;
	TButton *btnCancel;
	TOpenDialog *OpenDialog;
	TPageControl *PageControl;
	TTabSheet *tsMain;
	TTabSheet *tsMySQL;
	TTabSheet *tsAglodoza;
	TGroupBox *gbOptions;
	TLabeledEdit *eOptionsPass;
	TLabeledEdit *eOptionsPass2;
	TLabeledEdit *eAglodozaScaleNum;
	TLabeledEdit *eAglodozaDatabase;
	TButton *btnAglodozaDatabase;
	TGroupBox *gbMySQL;
	TLabeledEdit *eMySQLHost;
	TLabeledEdit *eMySQLUser;
	TLabeledEdit *eMySQLPass;
	TRadioGroup *rgProgramMode;
	TButton *btnCheckMySQL;
	TButton *btnCheckAglodoza;
	TTabSheet *tsKoksohim;
	TTabSheet *tsDomna;
	TLabeledEdit *eKoksohimScaleNum;
	TLabeledEdit *eKoksohimDatabase;
	TButton *btnCheckKoksohim;
	TButton *btnKoksohimDatabase;
	TLabeledEdit *eDomnaScaleNum;
	TLabeledEdit *eDomnaDatabase;
	TButton *btnCheckDomna;
	TButton *btnDomnaDatabase;
	TGroupBox *gbTimer;
	TComboBox *cboxTimerPeriod;
	TSpinEdit *seTimerPeriodStart;
	TLabel *lblTimerPeriodStart;
	TLabel *lblTimerPeriod;
	TLabeledEdit *eDomnaPass;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnAglodozaDatabaseClick(TObject *Sender);
	void __fastcall btnCheckMySQLClick(TObject *Sender);

private:
	TSettings * Settings;

	void ControlSetFocus(TWinControl * Control);

	bool CheckEdit(TCustomEdit * Edit, NativeUInt Message);
	bool CheckFileExists(TCustomEdit * Edit);

	void UpdateForm();
	void UpdateSettings();

public:
	__fastcall TfrmOptions(TComponent* Owner);

	static bool Show(TSettings * Settings);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
// ---------------------------------------------------------------------------
#endif
