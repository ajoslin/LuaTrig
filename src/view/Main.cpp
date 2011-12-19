#include "Main.h"

bool MainApp::OnInit()
{
	Main = new MainFrame(wxT("LuaTrig"));
	Main->SetSize(640, 480);
	Main->Show(true);
	SetTopWindow(Main);

	return true;
}

IMPLEMENT_APP(MainApp)