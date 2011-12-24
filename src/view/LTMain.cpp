#include "LTMain.h"
#include "../defines.h"

bool LTMain::OnInit()
{
	LTMain = new LTFrame(wxT(STR_LUATRIG));
	LTMain->SetSize(640, 480);
	LTMain->Show(true);
	SetTopWindow(LTMain);

	return true;
}

IMPLEMENT_APP(LTMain)