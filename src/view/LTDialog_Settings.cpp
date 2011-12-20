#include "LTDialog_Settings.h"
#include "wx/stdpaths.h"
#include "LTFrame.h"

LTDialog_Settings::LTDialog_Settings(LTFrame *parent)
	: wxDialog(parent, -1, "Settings", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT | wxSTAY_ON_TOP)
{
	this->frame = parent;

	areaSizer = new wxBoxSizer(wxVERTICAL);
	defaultBtnSizer = new wxBoxSizer(wxHORIZONTAL);
	gridSizer = new wxFlexGridSizer(2, 2, 2);
	okBtnSizer = new wxBoxSizer(wxHORIZONTAL);

	defaultsButton = new wxButton(this, wxID_ANY, wxT("Set Default Folders"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	
	defaultBtnSizer->Add(defaultsButton, wxEXPAND);

	scenarioText = new wxStaticText(this, wxID_ANY, "Scenario folder:");
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


	areaSizer->AddSpacer(10);
	areaSizer->Add(defaultBtnSizer, 0, wxALIGN_CENTER);
	areaSizer->AddSpacer(10);
	areaSizer->Add(gridSizer, 1, wxEXPAND);
	areaSizer->AddSpacer(15);
	areaSizer->Add(okBtnSizer, 0, wxALIGN_CENTER | wxALIGN_BOTTOM);
	areaSizer->AddSpacer(5);

	SetSizerAndFit(areaSizer);

	Connect(defaultsButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_Settings::onDefaults));
	Connect(scenarioDirPicker->GetId(), wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(LTDialog_Settings::onChangeScenarioPath));
	Connect(scriptDirPicker->GetId(), wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(LTDialog_Settings::onChangeScriptsPath));
	Connect(wxID_OK, wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(LTDialog_Settings::onDone));
	Connect(wxID_CANCEL, wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(LTDialog_Settings::onDone));

	SetSize(500,200);
}

void LTDialog_Settings::onDefaults(wxCommandEvent& event)
{
	wxString path;
	if (wxIsPlatform64Bit())
	{
		path = "c:\\Program Files (x86)\\Microsoft Games\\Age of Empires II\\Scenario";
	}
	else
	{
		path = "c:\\Program Files\\Microsoft Games\\Age of Empires II\\Scenario";
	}
	scenarioDirPicker->SetPath(path);

	wxString exePath = wxStandardPaths::Get().GetExecutablePath();

	//Shave "LuaTrig.exe" off of the path to just get the dir
	while (exePath.Last()!='\\')
		exePath.RemoveLast();

	scriptDirPicker->SetPath(wxString(exePath + "scripts"));
}

void LTDialog_Settings::onChangeScenarioPath(wxCommandEvent& event)
{
}

void LTDialog_Settings::onChangeScriptsPath(wxCommandEvent& event)
{
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