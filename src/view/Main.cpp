#include "Main.h"

bool LTrig::OnInit()
{
	MainFrame = new LTFrame(wxT("LuaTrig"));
	MainFrame->SetSize(640, 480);
	MainFrame->Show(true);
	SetTopWindow(MainFrame);

	return true;
}

IMPLEMENT_APP(LTrig)