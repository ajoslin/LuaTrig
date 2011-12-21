#ifndef LT_DIALOG_TRIGGERGEN_H_
#define LT_DIALOG_TRIGGERGEN_H_

#include "wx/wx.h"

class LTDialog_TriggerGen : public wxDialog
{
private:
	wxBoxSizer *sizer;
	wxBoxSizer *widthSizer;
	
	wxStaticText *title;
	wxButton *okButton;
public:
	LTDialog_TriggerGen(wxWindow *parent);	

	void onDone(wxCommandEvent& event);
};

#endif