#include "LTPage_Settings.h"

LTPage_Settings::LTPage_Settings(wxFrame& parent)
	: wxPanel(parent);
{
	Sizer_Main = new wxBoxSizer(wxHORIZONTAL);
	Sizer_DefaultBtn = new wxBoxSizer(wxHORIZONTAL);
	Sizer_Grid = new wxGridSizer(2, 2, 2);

	ButtonDefaults = new wxButton(this, wxID_ANY, "Set to Defaults");

	TextScenario = new wxStaticText(this, wxID_ANY, "Default Scenario folder:");
	PathScenario = new wxDirPickerCtrl(this, wxID_ANY, &(parent->ScenarioDir), "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DRI_MUST_EXIST);
	TextScript = new wxStaticText(this, wxID_ANY, "Default Lua Scripts folder:");
	PathScript = new wxDirPickerCtrl(this, wxID_ANY, &(parent->ScriptsDir), "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DRI_MUST_EXIST);

	Sizer_DefaultBtn->Add(ButtonDefaults, 1, wxEXPAND);

	Sizer_Grid->Add(TextScenario, 1, wxEXPAND);
	Sizer_Grid->Add(PathScenario, 1, wxEXPAND);
	Sizer_Grid->Add(TextScripts, 1, wxEXPAND);
	Sizer_Grid->Add(PathScripts, 1, wxEXPAND);

	Sizer_Main->AddSpacer(15);
	Sizer_Main->Add(Sizer_DefaultBtn, 1, wxALIGN_LEFT);
	Sizer_Main->AddSpacer(15);
	Sizer_Main->Add(Grid, 1, wxEXPAND);
	Sizer_Main->AddSpacer(5);

	this->SetSizerAndFit(MainOpen);

	Connect(ButtonDefaults->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Settings::OnDefaults));
	Connect(PathScenario->GetId(), wxEVT_DIRPICKER_CHANGED, wxCommandEventHandler(LTPage_Settings::OnChangeScenarioPath));
	Connect(PathScripts->GetId(), wxEVT_DIRPICKER_CHANGED, wxCommandEventHandler(LTPage_Settings::OnChangeScriptsPath));
}

void LTPage_Settings::OnDefaults(wxCommandEvent& event)
{
	wxString Path;

	if (wxIsPlatform64Bit())
	{
		Path = "C:\\Program Files (x86)\\Microsoft Games\\Age of Empires II\\Scenario";
	}
	else
	{
		Path = "C:\\Program Files\\Microsoft Games\\Age of Empires II\\Scenario";
	}
	PathScenario->SetPath(Path);
	PathScripts->SetPath(wxString(wxGetCwd() + "\\scripts");
}

void LTPage_Settings::OnChangeScenarioPath(wxCommandEvent& event)
{
	parent->ScenarioDir=PathScenario->GetPath();
	parent->Config->Write("DefaultScenarioDir", parent->ScenarioDir);
}

void LTPage_Settings::OnChangeScriptsPath(wxCommandEvent& event)
{
	parent->ScriptsDir=PathScripts->GetPath();
	parent->Config->Write("DefaultScriptsDir", parent->ScriptsDir);
}