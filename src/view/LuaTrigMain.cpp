#include "LuaTrigMain.h"
#include "LTFrame.h"
#include "../defines.h"

#include <iostream>

bool LuaTrigMain::OnInit()
{
	MainFrame = LTFrame::instance(wxT(STR_LUATRIG));
	MainFrame->SetSize(700, 520);
	MainFrame->Show(true);
	SetTopWindow(MainFrame);

	std::cout << LTFrame::instance() << std::endl;

	return true;
}

wxString LuaTrigMain::configRead(wxString key)
{
	wxFileConfig *cfg = new wxFileConfig(wxT(STR_LUATRIG), wxEmptyString, wxT(STR_CFG_FNAME), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	wxString value;
	cfg->Read(key, &value);
	delete cfg;
	return value;
}

void LuaTrigMain::configWrite(wxString key, wxString value)
{
	wxFileConfig *cfg = new wxFileConfig(wxT(STR_LUATRIG), wxEmptyString, wxT(STR_CFG_FNAME), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	cfg->Write(key, value);
	delete cfg;
}

IMPLEMENT_APP(LuaTrigMain)
