#ifndef MAIN_FRAME_H_
#define MAIN_FRAME_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/fileconf.h"
#include "LTPage_Settings.h"


enum InterfaceChoices
{
	Menu_About,
	Menu_Exit,
	Tab_Settings,
	Tab_ImportExport,
	Tab_TriggerGen
};

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	wxFileConfig *Config;

	//App Events
	void OnSaveLua(wxCommandEvent& event);
	void OnSaveScen(wxCommandEvent& event);
	void OnLoadLua(wxCommandEvent& event);
	void OnLoadScen(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnExit(wxCloseEvent& event);
	void OnMenuOption(wxCommandEvent& event);

	//App Variables
	wxString ScenFile;
	wxString ScriptFile;
	
	wxMenuBar *MenuBar_Main;
	wxMenu *SubMenu_File;

	wxNotebook *TabBar_Main;
	LTPage_Settings *Page_Settings;
	//LTPage_ImportExport *Page_ImportExport;
	//LTPage_TriggerGen *Page_TriggerGen;
	
	wxString ScenarioDir;
	wxString ScriptsDir;
};

#endif