#ifndef MAIN_FRAME_H_
#define MAIN_FRAME_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/filepicker.h"
#include "wx/filename.h"
#include "wx/image.h"
#include "wx/toolbar.h"
#include "wx/tbarbase.h"
#include "wx/imaglist.h"
#include <vector>

class LTPage_File; //forward these so we don't have to include
class LTDialog_Settings;
class LTDialog_About;

enum ToolbarChoices
{
	TOOLBAR_About,
	TOOLBAR_Settings,
	TOOLBAR_OpenScenario,
	TOOLBAR_OpenScript,
	TOOLBAR_Console
};

enum FileType
{
	FTYPE_Script,
	FTYPE_Scenario
};

class LTFrame : public wxFrame
{
private:
	LTFrame(wxString title);

	wxString currentScenarioDir;
	wxString currentScriptDir;

	wxToolBar *toolBar;

	//wx things
	wxNotebook *openFilesBook;
	wxImageList *openFilesImageList;
	
	LTDialog_About *aboutDialog;
	LTDialog_Settings *settingsDialog;
	wxFileDialog *openScenarioDialog;
	wxFileDialog *openScriptDialog;

	//wx Events
	void onToolbarExit(wxCloseEvent& event); 
	void onToolbarSettings(wxCommandEvent& event);
	void onToolbarOpenScenario(wxCommandEvent& event);
	void onToolbarOpenScript(wxCommandEvent& event);
	void onToolbarAbout(wxCommandEvent& event);

	static LTFrame *__instance;

public:
	//gets type from filename extension (eg .scx=FTYPE_Scenario)
	int typeFromFileName(wxFileName fname);
	
	//others
	void openFile(wxFileName fname, int type=-1, bool select=true);
	void closeFile(wxFileName fname);
	int indexOfFile(wxFileName fname);

	LTPage_File * getFileBookPage(int i);
	int getFileBookPageCount();

	static LTFrame *instance(wxString title = wxEmptyString);
};

#endif


