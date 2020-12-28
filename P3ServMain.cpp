// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <DateUtils.hpp>

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
			miClose->Enabled = false;
#ifndef FORCECLOSE
			if (MsgBoxYesNo(IDS_QUESTION_CLOSE_PROGRAM))
#endif
				Application->Terminate();
			miClose->Enabled = true;
		}
	}
	__finally {
		PopupMenuSetEnabled(true);
		TimerSetEnabled(true);
	}
}

// ---------------------------------------------------------------------------
void TMain::TimerSetEnabled(bool Enabled) {
	if (CheckExit()) {
		return;
	}

	if (Enabled) {
		if (Settings->TimerPeriod == 0) {
			Timer->Enabled = false;
			return;
		}

		int P = Settings->TimerPeriod;
		int C = MinsPerHour / P;

		TimeToWork = Now();

		bool NextHour = false;
		int NextMin = 0;
		int CurrentMin = MinuteOf(TimeToWork);

		if (Settings->TimerPeriodStart > Settings->TimerPeriod && CurrentMin <
			Settings->TimerPeriodStart - Settings->TimerPeriod) {
			NextMin = Settings->TimerPeriodStart - Settings->TimerPeriod;
		}
		else {
			for (int i = 0; i <= C; i++) {
				NextMin = P * i + Settings->TimerPeriodStart;

				if (CurrentMin < NextMin) {
					break;
				}
			}

			if (NextMin >= MinsPerHour) {
				NextMin = NextMin - MinsPerHour;

				NextHour = true;
			}
		}

		Word Hour, Min, Sec, MSec;

		DecodeTime(TimeToWork, Hour, Min, Sec, MSec);

		Min = NextMin;

		ReplaceTime(TimeToWork, EncodeTime(Hour, Min, 0, 0));

		if (NextHour) {
			TimeToWork = IncHour(TimeToWork);
		}

		WriteToLog("next work: " + DateTimeToStr(TimeToWork));

		Timer->Enabled = true;
	}
	else {
		Timer->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::TimerTimer(TObject *Sender) {
	if (Now() >= TimeToWork) {
		TrayIconMenuClick(tmCheck);
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
		TrayIconLoadFromResourceName(TrayIcon, "MAINICON");
		TrayIcon->Hint = LoadStr(IDS_APP_TITLE);
	}
}

// ---------------------------------------------------------------------------
