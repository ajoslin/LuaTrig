#ifndef LT_DIALOG_SETTINGS_H_
#define LT_DIALOG_SETTINGS_H_

#include "wx/wx.h"
#include "wx/fileconf.h"
#include "wx/filepicker.h"

class LTFrame; //fwd declaration so no need to include ltframe

class LTDialog_Settings : public wxDialog
{
private:
	LTFrame *frame;

	wxBoxSizer *mainSizer;
	wxBoxSizer *defaultBtnSizer;
	wxFlexGridSizer *gridSizer;
	wxBoxSizer *okBtnSizer;

	wxStaticText *instructionsText;
	wxButton *defaultsButton;

	wxStaticText *scenarioText;
	wxDirPickerCtrl *scenarioDirPicker;
	wxStaticText *scriptText;
	wxDirPickerCtrl *scriptDirPicker;

	wxButton *okButton;
	wxButton *cancelButton;


public:
	LTDialog_Settings(LTFrame *parent);

	void onDefaults(wxCommandEvent& event);
	void onDone(wxCommandEvent &event);
};

#endif