#include "LTFrame.h"
#include "../res/info.xpm"
#include "../res/aoc.xpm"
#include "../res/lua.xpm"
#include "../res/brain.xpm"
#include "../res/gear.xpm"
#include "../res/aoc_16.xpm"
#include "../res/lua_16.xpm"
#include "LTPage_Scen.h"
#include "LTPage_Script.h"
#include "LTPage_FileBase.h"
#include "LTDialog_About.h"
#include "LTDialog_Settings.h"
#include "LTDialog_TriggerGen.h"


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
	tabBarImageList = new wxImageList(16, 16, false, 0);
	tabBarImageList->Add(wxBitmap(aoc_16_xpm));
	tabBarImageList->Add(wxBitmap(lua_16_xpm));

	tabBarMain = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	tabBarMain->SetImageList(tabBarImageList);

	//Connect menu events
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LTFrame::onExit));
	Connect(ICHOICE_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onAbout));
	Connect(ICHOICE_Settings, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onSettings));
	Connect(ICHOICE_OpenScenario, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onOpenDialogScenario));
	Connect(ICHOICE_OpenScript, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onOpenDialogScript));
	Connect(ICHOICE_TriggerGen, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onTriggerGen));

	scenarioFile = wxT("");
	scriptFile = wxT("");

	aboutDialog = new LTDialog_About(this);
	settingsDialog = new LTDialog_Settings(this);
	openScenarioDialog = new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Scx files (*.scx)|*.scx"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	openScriptDialog = new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Lua files (*.lua)|*.lua"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	triggerGenDialog = new LTDialog_TriggerGen(this);

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
	aboutDialog->ShowModal();
}

void LTFrame::onSettings(wxCommandEvent& event)
{
	settingsDialog->ShowModal();
}

void LTFrame::onOpenDialogScenario(wxCommandEvent& event)
{
	openScenarioDialog->SetDirectory(scenarioDir);
	int id=openScenarioDialog->ShowModal();
	
	if (id==wxID_OK)
	{
		openScenario(new wxFileName(openScenarioDialog->GetPath()));
	}
}

void LTFrame::onOpenDialogScript(wxCommandEvent& event)
{
	openScriptDialog->SetDirectory(scriptDir);
	int id=openScriptDialog->ShowModal();
	
	if (id==wxID_OK)
	{
		openScript(new wxFileName(openScriptDialog->GetPath()));
	}
}

void LTFrame::onTriggerGen(wxCommandEvent& event)
{
	triggerGenDialog->ShowModal();
}


//return index of open file
int LTFrame::fileIndex(wxFileName *fname)
{
	for (int i=0; i<openFiles.size(); i++)
		if (openFiles[i]->file->GetFullPath()==fname->GetFullPath())
			return i;
	return -1;
}

void LTFrame::openScenario(wxFileName *fname, bool select)
{
	//if file already is open, just read it again and return
	int index=fileIndex(fname);
	if (index!=-1)
	{
		openFiles[index]->read();
		delete fname;
		return;
	}

	LTPage_Scen *newPage = new LTPage_Scen(this, tabBarMain, fname);
	tabBarMain->AddPage(newPage, fname->GetFullName(), select, 0);
	openFiles.push_back(newPage);
}

void LTFrame::openScript(wxFileName *fname, bool select)
{
	//if file already is open, just read it again and return
	int index=fileIndex(fname);
	if (index!=-1)
	{
		openFiles[index]->read();
		delete fname;
		return;
	}

	LTPage_Script *newPage = new LTPage_Script(this, tabBarMain, fname);
	tabBarMain->AddPage(newPage, fname->GetFullName(), select, 1);
	openFiles.push_back(newPage);
}

bool LTFrame::closeFile(wxFileName *fname)
{
	for (int i=0; i<openFiles.size(); i++)
	{
		if (openFiles[i]->file==fname)
		{
			tabBarMain->RemovePage(i);
			openFiles.erase(openFiles.begin()+i);
		}
	}
	return false;
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

