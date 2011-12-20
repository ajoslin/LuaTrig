#include "LTMain.h"

bool MainApp::OnInit()
{
	LTMain = new LTFrame(wxT("LuaTrig"));
	LTMain->SetSize(640, 480);
	LTMain->Show(true);
	SetTopWindow(LTMain);

	return true;
}

IMPLEMENT_APP(MainApp)