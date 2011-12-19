#ifndef MAIN_FRAME_H_
#define MAIN_FRAME_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/fileconf.h"
#include "wx/filepicker.h"


enum InterfaceChoices
{
	MenuItem_About,
	MenuItem_Exit,
	TabPage_Settings,
	TabPage_ImportExport,
	TabPage_TriggerGen,
	Settings_ScenarioDir,
	Settings_ScriptDir
};

class LTFrame : public wxFrame
{
public:
	LTFrame(const wxString& title);

	wxFileConfig *Config;

	//App Events
	void OnExit(wxCloseEvent& event); 
	void OnMenuOption(wxCommandEvent& event);

	//Misc variables
	wxString ScenarioFile;
	wxString ScriptFile;
	wxString ScenarioDir;
	wxString ScriptsDir;

	//Create
	void CreateSettingsTabPage();

	//TABS
	
	//SETTINGS
	void Settings_OnDefaults(wxCommandEvent& event);
	void Settings_OnChangeScenarioPath(wxCommandEvent& event);
	void Settings_OnChangeScriptsPath(wxCommandEvent& event);

	wxBoxSizer *Settings_Sizer_Main;
	wxBoxSizer *Settings_Sizer_DefaultBtn;
	wxGridSizer *Settings_Sizer_Grid;
	wxButton *Settings_ButtonDefaults;
	wxStaticText *Settings_TextScenario;
	wxDirPickerCtrl *Settings_PathScenario;
	wxStaticText *Settings_TextScript;
	wxDirPickerCtrl *Settings_PathScript;
	

	//App Variables
	
	
	wxMenuBar *MenuBar_Main;
	wxMenu *SubMenu_File;

	wxNotebook *TabBar_Main;
	wxPanel *TabPage_Settings;
	wxPanel *TabPage_ImportExport;
	wxPanel *TabPage_TriggerGen;
	
	

	//SETTINGS
	
	DECLARE_EVENT_TABLE();
};

#endif

