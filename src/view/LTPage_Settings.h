#ifndef LTPAGE_H_
#define LTPAGE_H_

#include "MainFrame.h"
#include "wx/wx.h"
#include "wx/filepicker.h"
#include "wx/filefn.h"

class LTPage_Settings : public wxPanel
{
public:
	LTPage_Settings(MainFrame& parent);
 
	void OnDefaults(wxCommandEvent& event);
	void OnChangeScenarioPath(wxCommandEvent& event);
	void OnChangeScriptsPath(wxCommandEvent& event);

	wxFrame *parent;

	wxBoxSizer *Sizer_Main;
	wxBoxSizer *Sizer_DefaultBtn;
	wxGridSizer *Sizer_Grid;

	wxButton *ButtonDefaults;

	wxStaticText *TextScenario;
	wxDirPickerCtrl *PathScenario;

	wxStaticText *TextScripts;
	wxDirPickerCtrl *PathScripts;
	
};

#endif