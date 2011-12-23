#ifndef LT_DIALOG_CHOOSE_SCEN_H_
#define LT_DIALOG_CHOOSE_SCEN_H_

#include "wx/wx.h"
#include "wx/radiobox.h"

class LTDialog_ChooseScen : public wxDialog
{
private:
	wxBoxSizer *mainSizer;
	wxBoxSizer *buttonSizer;

	wxRadioBox *radioBox;

	wxButton *okButton;
	wxButton *cancelButton;
	
public:
	LTDialog_ChooseScen(wxWindow *parent, wxString choices[], int nChoices);

	void onDone(wxCommandEvent &event);
	void onExit(wxCloseEvent &event);
};

#endif