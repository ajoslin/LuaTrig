#include "LTFrame.h"
#include "../res/info.xpm"
#include "../res/aoc.xpm"
#include "../res/lua.xpm"
#include "../res/gear.xpm"
#include "../res/aoc_16.xpm"
#include "../res/lua_16.xpm"
#include "../res/appicon.xpm"
#include "LTPage_Scen.h"
#include "LTPage_Script.h"
#include "LTPage_File.h"
#include "LTDialog_About.h"
#include "LTDialog_Settings.h"
#include "LuaTrigMain.h"
#include "../defines.h"

#define FILEBOOK_IMAGE_SCEN 	0
#define FILEBOOK_IMAGE_SCRIPT 	1

LTFrame *LTFrame::__instance = NULL;

LTFrame *LTFrame::instance(wxString title)
{
	if (__instance==NULL)
		__instance = new LTFrame(title);
	return __instance;
}

LTFrame::LTFrame(wxString title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	__instance = this;

	//Get config settings (if they exist
	currentScenarioDir=LuaTrigMain::configRead(wxT(STR_CFG_SCNDIR));
	currentScriptDir=LuaTrigMain::configRead(wxT(STR_CFG_LUADIR));
	bool openSettings=currentScenarioDir == wxT(""); //if scndir is blank (aka not set in config), open settings on startup

	CreateStatusBar();

	toolBar = CreateToolBar(wxTB_TEXT | wxTB_HORIZONTAL);
	toolBar->AddTool(TOOLBAR_About, wxT(STR_TOOLBAR_ABT), wxBitmap(info_xpm));
	toolBar->AddTool(TOOLBAR_Settings, wxT(STR_TOOLBAR_STGS), wxBitmap(gear_xpm));
	toolBar->AddSeparator();
	toolBar->AddTool(TOOLBAR_OpenScenario, wxT(STR_TOOLBAR_SCN), wxBitmap(aoc_xpm));
	toolBar->AddTool(TOOLBAR_OpenScript, wxT(STR_TOOLBAR_LUA), wxBitmap(lua_xpm));
	toolBar->Realize();

	//Tab Bar
	openFilesImageList = new wxImageList(16, 16, false, 0);
	openFilesImageList->Add(wxBitmap(aoc_16_xpm));
	openFilesImageList->Add(wxBitmap(lua_16_xpm));

	openFilesBook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	openFilesBook->SetImageList(openFilesImageList);

	//Dialogs
	aboutDialog = new LTDialog_About(this);
	settingsDialog = new LTDialog_Settings(this);
	openScenarioDialog = new wxFileDialog(this, wxT(STR_FILE_SELECT), wxT(""), wxT(""), wxT(STR_EXT_SCX), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	openScriptDialog = new wxFileDialog(this, wxT(STR_FILE_SELECT), wxT(""), wxT(""), wxT(STR_EXT_LUA), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	//Connect menu events
	Connect(TOOLBAR_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onToolbarAbout));
	Connect(TOOLBAR_Settings, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onToolbarSettings));
	Connect(TOOLBAR_OpenScenario, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onToolbarOpenScenario));
	Connect(TOOLBAR_OpenScript, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LTFrame::onToolbarOpenScript));

	if (openSettings)
	{
		wxCommandEvent settingsCmd(wxEVT_COMMAND_MENU_SELECTED, TOOLBAR_Settings);
		ProcessEvent(settingsCmd);
	}
}

void LTFrame::onToolbarAbout(wxCommandEvent& event)
{
	aboutDialog->ShowModal();
}

void LTFrame::onToolbarSettings(wxCommandEvent& event)
{
	settingsDialog->loadDirs();
	settingsDialog->ShowModal();
}

void LTFrame::onToolbarOpenScenario(wxCommandEvent& event)
{
	openScenarioDialog->SetDirectory(currentScenarioDir);
	int id=openScenarioDialog->ShowModal();
	
	if (id==wxID_OK)
	{
		wxFileName fname(openScenarioDialog->GetPath());
		openFile(fname, FTYPE_Scenario);
	}
}

void LTFrame::onToolbarOpenScript(wxCommandEvent& event)
{
	openScriptDialog->SetDirectory(currentScriptDir);
	int id=openScriptDialog->ShowModal();
	
	if (id==wxID_OK)
	{
		wxFileName fname(openScriptDialog->GetPath());
		openFile(fname, FTYPE_Script);
	}
}

int LTFrame::typeFromFileName(wxFileName fname)
{
	wxString path(fname.GetFullPath());
	wxString ext=path.Right(4);

	if (ext==wxT(".scx") || ext==wxT(".scn"))
		return FTYPE_Scenario;

	return FTYPE_Script;
}


void LTFrame::openFile(wxFileName fname, int type, bool select)
{
	//if file is open, just go to it and read it
	int openIndex = indexOfFile(fname);
	if (openIndex!=-1)
	{
		( (LTPage_File *)openFilesBook->GetPage(openIndex) )->read();
		openFilesBook->ChangeSelection(openIndex);
	}
	else
	{
		if (type==-1)
			type=typeFromFileName(fname);

		LTPage_File *newPage;
		if (type==FTYPE_Scenario)
			newPage = new LTPage_Scen(openFilesBook);
		else
			newPage = new LTPage_Script(openFilesBook);
		newPage->open(fname);

		openFilesBook->AddPage(
			newPage, 
			fname.GetFullName(), 
			select, 
			type==FTYPE_Scenario ? FILEBOOK_IMAGE_SCEN : FILEBOOK_IMAGE_SCRIPT
		);
	}
}

void LTFrame::closeFile(wxFileName fname)
{
	for (int i=0; i<openFilesBook->GetPageCount(); i++)
	{
		LTPage_File *page = (LTPage_File *)openFilesBook->GetPage(i);
		if (page!=NULL)
		{
			wxFileName pageFile = page->getCurrentFileName();
			if (pageFile==fname)
			{
				openFilesBook->DeletePage(i);
				break;
			}
		}
	}
}

int LTFrame::indexOfFile(wxFileName fname)
{
	for (int i=0; i<openFilesBook->GetPageCount(); i++)
	{
		LTPage_File *page = (LTPage_File *)openFilesBook->GetPage(i);
		if (page!=NULL && page->getCurrentFileName()==fname)
			return i;
	}
	return -1;
}

LTPage_File * LTFrame::getFileBookPage(int i)
{
	return (LTPage_File *)openFilesBook->GetPage(i);
}

int LTFrame::getFileBookPageCount()
{
	return openFilesBook->GetPageCount();
}
