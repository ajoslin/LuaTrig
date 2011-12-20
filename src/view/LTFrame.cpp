#include "LTFrame.h"
#include "../res/info.xpm"
#include "../res/aoc.xpm"
#include "../res/lua.xpm"
#include "../res/brain.xpm"
#include "../res/gear.xpm"
#include "LTDialog_Settings.h"
#include "LTDialog_About.h"

LTFrame::LTFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	//Get config settings (if they exist)
  config = new wxFileConfig(wxT("LuaTrig"), wxEmptyString, wxT("luatrigconfig.ini"), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
  config->Read(wxT("DefaultScenarioDir"), &scenarioDir, wxT(""));
  config->Read(wxT("DefaultScriptDir"), &scriptDir, wxT(""));
  config->Read(wxT("FirstTimeStartup"), &firstTimeStartup, true);
  config->Write(wxT("FirstTimeStartup"), false);
	delete config;

	CreateStatusBar();

	toolBar = CreateToolBar(wxTB_TEXT | wxTB_HORIZONTAL);
	toolBar->AddTool(ICHOICE_About, wxT("About"), wxBitmap(info_xpm));
	toolBar->AddTool(ICHOICE_Settings, wxT("Settings"), wxBitmap(gear_xpm), wxT("Adjust program settings"));
	toolBar->AddSeparator();
	toolBar->AddTool(ICHOICE_OpenScenario, wxT("Open Scenario"), wxBitmap(aoc_xpm), wxT("Open a scenario"));
	toolBar->AddTool(ICHOICE_OpenScript, wxT("Open Script"), wxBitmap(lua_xpm), wxT("Open a lua trigger-script file"));
	toolBar->AddSeparator();
	toolBar->AddTool(ICHOICE_TriggerGen, wxT("Generate Triggers"), wxBitmap(brain_xpm), wxT("Coming soon"));
	toolBar->ToggleTool(ICHOICE_TriggerGen, false); //disabled - not done yet
	toolBar->Realize();

	//Tab Bar
	tabBarMain = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//fileOpenPanel = new LTDialog_ImportExport(this, tabBarMain);

	//TabBar_Main->AddPage(Tab_TriggerGen, "Trigger Generator");
	//TabBar_Main->SetSelection(0);

	//Connect menu events
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LTFrame::onExit));
	Connect(ICHOICE_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onAbout));
	Connect(ICHOICE_Settings, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onSettings));
	Connect(ICHOICE_OpenScenario, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onOpenScenario));
	Connect(ICHOICE_OpenScript, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onOpenScript));
	Connect(ICHOICE_TriggerGen, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onTriggerGen));

	scenarioFile = wxT("");
	scriptFile = wxT("");

	if (firstTimeStartup) //on first startup, open settings dialog
	{
		wxCommandEvent settingsCmd(wxEVT_COMMAND_MENU_SELECTED, ICHOICE_Settings);
		ProcessEvent(settingsCmd);
	}
}

void LTFrame::onExit(wxCloseEvent& event)
{
	tabBarMain->Show(false);
	tabBarMain->Destroy();
	Destroy();
}

void LTFrame::onAbout(wxCommandEvent& event)
{
	LTDialog_About about(this);
	about.ShowModal();
}

void LTFrame::onSettings(wxCommandEvent& event)
{
	LTDialog_Settings settings(this);
	settings.ShowModal();
}

void LTFrame::onOpenScenario(wxCommandEvent& event)
{
	
}

void LTFrame::onOpenScript(wxCommandEvent& event)
{
	
}

void LTFrame::onTriggerGen(wxCommandEvent& event)
{
	
}

void LTFrame::setScenarioDir(wxString path)
{
	scenarioDir=path;
	config = new wxFileConfig(wxT("LuaTrig"), wxEmptyString, wxT("luatrigconfig.ini"), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	config->Write(wxT("DefaultScenarioDir"), path);
	delete config;
}

void LTFrame::setScriptDir(wxString path)
{
	scriptDir=path;
	config = new wxFileConfig(wxT("LuaTrig"), wxEmptyString, wxT("luatrigconfig.ini"), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	config->Write(wxT("DefaultScriptDir"), path);
	delete config;
}
