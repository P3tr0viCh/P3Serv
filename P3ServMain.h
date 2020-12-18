// ---------------------------------------------------------------------------

#ifndef P3ServMainH
#define P3ServMainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.AppEvnts.hpp>

#include "P3ServTSettings.h"

// ---------------------------------------------------------------------------
class TMain : public TForm {
__published:
	TPopupMenu *PopupMenu;
	TMenuItem *miCheck;
	TMenuItem *miSeparator01;
	TMenuItem *miOptions;
	TMenuItem *miSeparator02;
	TMenuItem *miAbout;
	TMenuItem *miSeparator03;
	TMenuItem *miClose;
	TTrayIcon *TrayIcon;
	TApplicationEvents *ApplicationEvents;

	void __fastcall miCheckClick(TObject *Sender);
	void __fastcall miOptionsClick(TObject *Sender);
	void __fastcall miAboutClick(TObject *Sender);
	void __fastcall miCloseClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall TrayIconClick(TObject *Sender);
	void __fastcall ApplicationEventsException(TObject *Sender, Exception *E);

private:
	enum TTrayIconMenuItem {
		tmCheck, tmOptions, tmAbout, tmClose
	};

	TSettings * FSettings;

	void TrayIconMenuClick(TTrayIconMenuItem TrayIconMenuItem);

	void PopupMenuSetEnabled(bool Enabled);

	void MainFunction();

public:
	__fastcall TMain(TComponent* Owner);

	__property TSettings * Settings = {read = FSettings};
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif
