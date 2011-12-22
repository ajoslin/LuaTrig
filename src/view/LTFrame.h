#ifndef MAIN_FRAME_H_
#define MAIN_FRAME_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/fileconf.h"
#include "wx/filepicker.h"
#include "wx/filename.h"
#include "wx/image.h"
#include "wx/toolbar.h"
#include "wx/tbarbase.h"
#include "wx/imaglist.h"
#include "LTDialog_About.h"
#include "LTDialog_Settings.h"
#include "LTDialog_TriggerGen.h"
#include "LTPage_FileBase.h"
#include <vector>

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
	wxImageList *tabBarImageList;
	wxToolBar *toolBar;
	LTDialog_About *aboutDialog;
	LTDialog_Settings *settingsDialog;
	wxFileDialog *openScenarioDialog;
	wxFileDialog *openScriptDialog;
	LTDialog_TriggerGen *triggerGenDialog;

public:
	LTFrame(const wxString& title);

	wxFileConfig *config;

	//wx Events
	void onExit(wxCloseEvent& event); 
	void onAbout(wxCommandEvent& event);
	void onSettings(wxCommandEvent& event);
	void onOpenDialogScenario(wxCommandEvent& event);
	void onOpenDialogScript(wxCommandEvent& event);
	void onTriggerGen(wxCommandEvent& event);

	//Functions
	//isOpen returns index of open file with path
	int fileIndex(wxFileName *fname);
	void openScenario(wxFileName *fname, bool select = true);
	void openScript(wxFileName *fname, bool select = true);
	void closeSelectedFile();

	//Getters/setters
	void setScenarioDir(wxString path);
	wxString getScenarioDir() { return scenarioDir; };
	void setScriptDir(wxString path);
	wxString getScriptDir() { return scriptDir; };

	std::vector<LTPage_FileBase *> openFiles;
};

#endif

