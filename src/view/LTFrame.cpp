#include "LTFrame.h"

LTFrame::LTFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	//Get config settings (if they exist)
	Config = new wxFileConfig("LuaTrig", wxEmptyString, "luatrigconfig.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Read("DefaultScenarioDir", &ScenarioDir, wxT(""));
	Config->Read("DefaultScriptsDir", &ScriptsDir, wxT(""));

	//Menu Bar
	MenuBar_Main = new wxMenuBar();

	SubMenu_File = new wxMenu();
	SubMenu_File->Append(MenuItem_About, "&About");
	SubMenu_File->Append(MenuItem_Exit, "E&xit");

	MenuBar_Main->Append(SubMenu_File, "&File");
	this->SetMenuBar(MenuBar_Main);

	//Tab Bar
	TabBar_Main = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	CreateSettingsTabPage();

	TabBar_Main->AddPage(TabPage_Settings, "Settings");
	//TabBar_Main->AddPage(Tab_Import, "Trigger Importer/Exporter");
	//TabBar_Main->AddPage(Tab_TriggerGen, "Trigger Generator");
	TabBar_Main->SetSelection(1);

	//Connect menu events
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LTFrame::OnExit));
	Connect(MenuItem_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::OnMenuOption));
	Connect(MenuItem_Exit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::OnMenuOption));

	ScenarioFile = "";
	ScriptFile = "";
}

void LTFrame::CreateSettingsTabPage()
{
	TabPage_Settings = new wxPanel(TabBar_Main);
	Settings_Sizer_Main = new wxBoxSizer(wxHORIZONTAL);
	Settings_Sizer_DefaultBtn = new wxBoxSizer(wxHORIZONTAL);
	Settings_Sizer_Grid = new wxGridSizer(2, 2, 2);

	Settings_ButtonDefaults = new wxButton(this, wxID_ANY, "Set to Defaults");

	Settings_TextScenario = new wxStaticText(this, wxID_ANY, "Default Scenario folder:");
	Settings_PathScenario = new wxDirPickerCtrl(this, wxID_ANY, ScenarioDir, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
	Settings_TextScript = new wxStaticText(this, wxID_ANY, wxT("Default Lua Scripts folder:"));
	Settings_PathScript = new wxDirPickerCtrl(this, wxID_ANY, ScriptsDir, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);

	Settings_Sizer_DefaultBtn->Add(Settings_ButtonDefaults, 1, wxEXPAND);

	Settings_Sizer_Grid->Add(Settings_TextScenario, 1, wxEXPAND);
	Settings_Sizer_Grid->Add(Settings_PathScenario, 1, wxEXPAND);
	Settings_Sizer_Grid->Add(Settings_TextScript, 1, wxEXPAND);
	Settings_Sizer_Grid->Add(Settings_PathScript, 1, wxEXPAND);

	Settings_Sizer_Main->AddSpacer(15);
	Settings_Sizer_Main->Add(Settings_Sizer_DefaultBtn, 1, wxALIGN_LEFT);
	Settings_Sizer_Main->AddSpacer(15);
	Settings_Sizer_Main->Add(Settings_Sizer_Grid, 1, wxEXPAND);
	Settings_Sizer_Main->AddSpacer(5);

	TabPage_Settings->SetSizerAndFit(Settings_Sizer_Main);

	Connect(Settings_ButtonDefaults->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTFrame::Settings_OnDefaults));
	Connect(Settings_PathScenario->GetId(), wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(LTFrame::Settings_OnChangeScenarioPath));
	Connect(Settings_PathScript->GetId(), wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(LTFrame::Settings_OnChangeScriptsPath));
}

void LTFrame::Settings_OnDefaults(wxCommandEvent& event)
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
	Settings_PathScenario->SetPath(Path);
	Settings_PathScript->SetPath(wxString(wxGetCwd() + "\\scripts");
}

void LTFrame::Settings_OnChangeScenarioPath(wxCommandEvent& event)
{
	ScenarioDir=Settings_PathScenario->GetPath();
	Config->Write("DefaultScenarioDir", parent->ScenarioDir);
}

void LTFrame::Settings_OnChangeScriptsPath(wxCommandEvent& event)
{
	ScriptsDir=Settings_PathScript->GetPath();
	Config->Write("DefaultScriptsDir", parent->ScriptsDir);
}