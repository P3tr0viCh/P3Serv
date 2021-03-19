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
	TTabSheet *tsDomna;
	TTabSheet *tsKoksohim;
	TTabSheet *tsKanat;
	TComboBox *cboxTimerPeriod;
	TSpinEdit *seTimerPeriodStart;
	TLabel *lblTimerPeriodStart;
	TLabel *lblTimerPeriod;
	TGroupBox *gbOptions;
	TGroupBox *gbTimer;
	TGroupBox *gbMySQL;
	TRadioGroup *rgProgramMode;
	TLabeledEdit *eOptionsPass;
	TLabeledEdit *eOptionsPass2;
	TLabeledEdit *eMySQLHost;
	TLabeledEdit *eMySQLUser;
	TLabeledEdit *eMySQLPass;
	TLabeledEdit *eAglodozaScaleNum;
	TLabeledEdit *eAglodozaDatabase;
	TLabeledEdit *eDomnaScaleNum;
	TLabeledEdit *eDomnaDatabase;
	TLabeledEdit *eDomnaPass;
	TLabeledEdit *eKoksohimScaleNum;
	TLabeledEdit *eKoksohimDatabase;
	TLabeledEdit *eKanatScaleNum;
	TLabeledEdit *eKanatDatabase;
	TCheckBox *cboxHumidity;
	TButton *btnCheckMySQL;
	TButton *btnAglodozaDatabase;
	TButton *btnDomnaDatabase;
	TButton *btnKoksohimDatabase;
	TButton *btnKanatDatabase;
	TButton *btnCheckAglodoza;
	TButton *btnCheckDomna;
	TButton *btnCheckKoksohim;
	TButton *btnCheckKanat;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnAglodozaDatabaseClick(TObject *Sender);
	void __fastcall btnCheckMySQLClick(TObject *Sender);

private:
	TSettings * Settings;

	void ControlSetFocus(TWinControl * Control);

	void CheckEmptyEditNum(TCustomEdit * Edit);
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
