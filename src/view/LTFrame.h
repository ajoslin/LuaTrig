#ifndef MAIN_FRAME_H_
#define MAIN_FRAME_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/fileconf.h"
#include "wx/filepicker.h"
#include "wx/image.h"
#include "wx/toolbar.h"
#include "wx/tbarbase.h"


enum InterfaceChoices
{
	ICHOICE_About,
	ICHOICE_Settings,
	ICHOICE_OpenScenario,
	ICHOICE_OpenScript,
	ICHOICE_TriggerGen
};

class LTFrame : public wxFrame
{
private:
	//Misc variables
	wxString scenarioFile;
	wxString scriptFile;
	wxString scenarioDir;
	wxString scriptDir;
	bool firstTimeStartup;

	//wxWidgets
	wxNotebook *tabBarMain;
	wxToolBar *toolBar;

public:
	LTFrame(const wxString& title);

	wxFileConfig *config;

	//App Events
	void onExit(wxCloseEvent& event); 
	void onAbout(wxCommandEvent& event);
	void onSettings(wxCommandEvent& event);
	void onOpenScenario(wxCommandEvent& event);
	void onOpenScript(wxCommandEvent& event);
	void onTriggerGen(wxCommandEvent& event);

	void setScenarioDir(wxString path);
	wxString getScenarioDir() { return scenarioDir; };
	void setScriptDir(wxString path);
	wxString getScriptDir() { return scriptDir; };
};

#endif

