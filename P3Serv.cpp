// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include <UtilsMisc.h>

#include "P3ServStrings.h"

// ---------------------------------------------------------------------------
USEFORM("P3ServLogin.cpp", frmLogin);
USEFORM("P3ServMain.cpp", Main);
USEFORM("P3ServOptions.cpp", frmOptions);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	HANDLE hMutex;

	try {
		hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, L"ru.p3tr0vich.P3Serv");

		if (hMutex) {
			MsgBoxErr(IDS_ERROR_ALREADY_RUN);

			return 0;
		}

		hMutex = CreateMutex(0, 0, L"ru.p3tr0vich.P3Serv");
		Application->Initialize();

#ifndef _DEBUG
		Application->MainFormOnTaskBar = false;
		Application->ShowMainForm = false;
#endif
		Application->Title = LoadStr(IDS_APP_TITLE);
		Application->CreateForm(__classid(TMain), &Main);
		Application->Run();
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}

	ReleaseMutex(hMutex);

	return 0;
}
// ---------------------------------------------------------------------------
