#include "LTDialog_Settings.h"
#include "wx/stdpaths.h"
#include "LTFrame.h"

LTDialog_Settings::LTDialog_Settings(LTFrame *parent)
  : wxDialog(parent, -1, wxT("Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT | wxSTAY_ON_TOP)
{
	this->frame = parent;

	mainSizer = new wxBoxSizer(wxVERTICAL);
	defaultBtnSizer = new wxBoxSizer(wxHORIZONTAL);
	gridSizer = new wxFlexGridSizer(2, 2, 2);
	okBtnSizer = new wxBoxSizer(wxHORIZONTAL);

	defaultsButton = new wxButton(this, wxID_ANY, wxT("Set Default Folders"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
		
	defaultBtnSizer->Add(defaultsButton, wxEXPAND);

	scenarioText = new wxStaticText(this, wxID_ANY, wxT("Scenario folder:"));
	scenarioDirPicker = new wxDirPickerCtrl(this, wxID_ANY, frame->getScenarioDir(), wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
	scriptText = new wxStaticText(this, wxID_ANY, wxT("Lua Scripts folder:"));
	scriptDirPicker = new wxDirPickerCtrl(this, wxID_ANY, frame->getScriptDir(), wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);

	gridSizer->Add(scenarioText, 1, wxEXPAND);
	gridSizer->Add(scenarioDirPicker, 1, wxEXPAND);
	gridSizer->Add(scriptText, 1, wxEXPAND);
	gridSizer->Add(scriptDirPicker, 1, wxEXPAND);
	gridSizer->AddGrowableCol(1, 1);

	okButton = new wxButton(this, wxID_OK, wxT("OK"));
	cancelButton = new wxButton(this, wxID_CANCEL, wxT("Cancel"));
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
}

void LTDialog_Settings::onDefaults(wxCommandEvent& event)
{
	wxString path;
	if (wxIsPlatform64Bit())
	{
	  path = wxT("c:/Program Files (x86)/Microsoft Games/Age of Empires II/Scenario");
	}
	else
	{
	  path = wxT("c:/Program Files/Microsoft Games/Age of Empires II/Scenario");
	}
	scenarioDirPicker->SetPath(path);

	wxString exePath = wxStandardPaths::Get().GetExecutablePath();

	//Shave "LuaTrig.exe" off of the path to just get the dir
	while (exePath.Last()!='/' && exePath.Last()!='\\')
		exePath.RemoveLast();

	scriptDirPicker->SetPath(wxString(exePath + wxT("scripts")));
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
