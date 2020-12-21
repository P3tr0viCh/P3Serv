// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <AboutFrm.h>

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsKAndM.h>
#include <UtilsFiles.h>
#include <UtilsFileIni.h>

#include "P3ServDebug.h"

#include "P3ServAdd.h"
#include "P3ServStrings.h"

#include "P3ServMainFunctionAglodoza.h"
#include "P3ServMainFunctionKoksohim.h"

#include "P3ServLogin.h"
#include "P3ServOptions.h"

#include "P3ServMain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMain *Main;

// ---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender) {
#ifdef _DEBUG
	randomize();
#endif
	FSettings = new TSettings();

	Caption = Application->Title + " " + GetFileVer(Application->ExeName);

	WriteToLogProgramStart();

	if (!Settings->Load()) {
		MsgBoxErr(IDS_ERROR_LOAD_SETTINGS);

		Application->Terminate();

		return;
	}

	MainFunction();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender) {
	FSettings->Free();

	WriteToLogProgramStop();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::ApplicationEventsException(TObject * Sender,
	Exception * E) {
	WriteToLog(Format(IDS_LOG_EXCEPTION, E->Message));

	MsgBoxErr(Format(IDS_ERROR_UNKNOWN_EXCEPTION, E->Message));
}

// ---------------------------------------------------------------------------
void TMain::TrayIconMenuClick(TTrayIconMenuItem TrayIconMenuItem) {
	TimerSetEnabled(false);
	PopupMenuSetEnabled(false);

	try {
		switch (TrayIconMenuItem) {
		case tmCheck:
			MainFunction();

			break;
		case tmAbout:
			WriteToLog(IDS_LOG_ABOUT);
			ShowAbout(16, MAXBYTE, MAXBYTE, MAXBYTE, NULL, NULL, NULL, NULL,
				NULL, LoadStr(IDS_COPYRIGHT));

			break;
		case tmOptions:
#ifndef FORCELOGON
			if (TfrmLogin::Show(Settings->OptionsPass))
#endif
			{
				if (TfrmOptions::Show(Settings)) {
					if (!Settings->Load()) {
						MsgBoxErr(IDS_ERROR_LOAD_SETTINGS);

						Application->Terminate();
					}
				}
			}

			break;
		case tmClose:
		default:
#ifndef FORCECLOSE
			if (MsgBoxYesNo(IDS_QUESTION_CLOSE_PROGRAM))
#endif
				Application->Terminate();
		}
	}
	__finally {
		PopupMenuSetEnabled(true);
		TimerSetEnabled(true);
	}
}

// ---------------------------------------------------------------------------
enum TTimerPeriod {
	tpOff = 0, tp1 = 1, tp5 = 5, tp10 = 10, tp15 = 15, tp20 = 20, tp30 = 30,
	tp60 = 60
};

// ---------------------------------------------------------------------------
void TMain::TimerSetEnabled(bool Enabled) {
	// TODO
	TTimerPeriod SettingsTimerPeriod = tp30;

	if (Enabled) {
		if (SettingsTimerPeriod == tpOff) {
			Timer->Enabled = false;
			return;
		}

		int P = SettingsTimerPeriod;
		int C = 59 / P;

		int T = 0;

		for (int m = 0; m < 60; m++) {

			for (int i = 1; i <= C; i++) {
				T = P * i;
				if (m < T) {
					break;
				}
			}

			if (m >= T) {
				T = 0;
			}

			WriteToLog(IntToStr(m) + "=" + IntToStr(T));
		}

		// TODO
		Timer->Enabled = false;
	}
	else {
		Timer->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void TMain::PopupMenuSetEnabled(bool Enabled) {
	miCheck->Enabled = Enabled;
	miOptions->Enabled = Enabled;
	miAbout->Enabled = Enabled;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::miCheckClick(TObject *Sender) {
	TrayIconMenuClick(tmCheck);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::miOptionsClick(TObject *Sender) {
	TrayIconMenuClick(tmOptions);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::miAboutClick(TObject *Sender) {
	TrayIconMenuClick(tmAbout);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::miCloseClick(TObject *Sender) {
	TrayIconMenuClick(tmClose);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::TrayIconClick(TObject *Sender) {
	SetForegroundWindow(Application->Handle);
}

// ---------------------------------------------------------------------------
void TMain::MainFunction() {
	TrayIcon->Hint = LoadStr(IDS_APP_WORK_IN_PROGRESS);
	TrayIconLoadFromResourceName(TrayIcon, "R_ICON_PROGRESS");

	TimerSetEnabled(false);

	try {
		try {
			switch (Settings->ProgramMode) {
			case pmAglodoza:
				MainFunctionAglodoza(Settings);
				break;
			case pmKoksohim:
				MainFunctionKoksohim(Settings);
				break;
			case pmDomna:
				throw Exception("TODO: domna");
				// break;
			default:
				throw Exception("check settings");
			}
		}
		catch (Exception &E) {
			WriteToLog(Format(IDS_LOG_EXCEPTION_IN_MAIN_FUNCTION, E.Message));
		}
	}
	__finally {
		TimerSetEnabled(true);

		TrayIconLoadFromResourceName(TrayIcon, "MAINICON");
		TrayIcon->Hint = LoadStr(IDS_APP_TITLE);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::TimerTimer(TObject *Sender) {
	MainFunction();
}

// ---------------------------------------------------------------------------
