#include "LTDialog_Settings.h"
#include "wx/stdpaths.h"
#include "LTFrame.h"
#include "../defines.h"

LTDialog_Settings::LTDialog_Settings(LTFrame *parent)
  : wxDialog(parent, -1, wxT(STR_STGS_TITLE), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT | wxSTAY_ON_TOP)
{
	this->frame = parent;

	mainSizer = new wxBoxSizer(wxVERTICAL);
	defaultBtnSizer = new wxBoxSizer(wxHORIZONTAL);
	gridSizer = new wxFlexGridSizer(2, 2, 2);
	okBtnSizer = new wxBoxSizer(wxHORIZONTAL);

	defaultsButton = new wxButton(this, wxID_ANY, wxT(STR_STGS_DEFAULT), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
		
	defaultBtnSizer->Add(defaultsButton, wxEXPAND);

	scenarioText = new wxStaticText(this, wxID_ANY, wxT(STR_STGS_SCN_TITLE));
	scenarioDirPicker = new wxDirPickerCtrl(this, wxID_ANY, frame->getScenarioDir(), wxT(STR_DIR_SELECT), wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
	scriptText = new wxStaticText(this, wxID_ANY, wxT(STR_STGS_LUA_TITLE));
	scriptDirPicker = new wxDirPickerCtrl(this, wxID_ANY, frame->getScriptDir(), wxT(STR_DIR_SELECT), wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);

	gridSizer->Add(scenarioText, 1, wxEXPAND);
	gridSizer->Add(scenarioDirPicker, 1, wxEXPAND);
	gridSizer->Add(scriptText, 1, wxEXPAND);
	gridSizer->Add(scriptDirPicker, 1, wxEXPAND);
	gridSizer->AddGrowableCol(1, 1);

	okButton = new wxButton(this, wxID_OK, wxT(STR_OK));
	cancelButton = new wxButton(this, wxID_CANCEL, wxT(STR_CANCEL));
	okBtnSizer->Add(okButton, wxEXPAND);
	okBtnSizer->Add(cancelButton, wxEXPAND);

	mainSizer->AddSpacer(10);
	mainSizer->Add(defaultBtnSizer, 0, wxALIGN_CENTER);
	mainSizer->AddSpacer(10);
	mainSizer->Add(gridSizer, 1, wxEXPAND);
	mainSizer->AddSpacer(15);
	mainSizer->Add(okBtnSizer, 0, wxALIGN_CENTER | wxALIGN_BOTTOM);
	mainSizer->AddSpacer(5);

	Connect(defaultsButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_Settings::onDefaults));
	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_Settings::onDone));
	Connect(wxID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_Settings::onDone));

	mainSizer->SetMinSize(wxSize(500, 1)); //only care about width
	SetSizerAndFit(mainSizer);
	Center();
}

void LTDialog_Settings::onDefaults(wxCommandEvent& event)
{
	wxString path;
	if (wxIsPlatform64Bit())
	{
	  path = wxT(STR_STGS_SCN_DIR64);
	}
	else
	{
	  path = wxT(STR_STGS_SCN_DIR32);
	}
	scenarioDirPicker->SetPath(path);

	wxString exePath = wxStandardPaths::Get().GetExecutablePath();

	//Shave "LuaTrig.exe" off of the path to just get the dir
	while (exePath.Last()!='/' && exePath.Last()!='\\')
		exePath.RemoveLast();

	scriptDirPicker->SetPath(wxString(exePath + wxT(STR_STGS_LUA_DIR)));
}

void LTDialog_Settings::onDone(wxCommandEvent& event)
{
	if (event.GetId()==wxID_OK)
	{
		frame->setScenarioDir(scenarioDirPicker->GetPath());
		frame->setScriptDir(scriptDirPicker->GetPath());
	}
	EndModal(event.GetId());
}
