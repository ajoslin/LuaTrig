#ifndef LT_DIALOG_ABOUT_H_
#define LT_DIALOG_ABOUT_H_

#include "wx/wx.h"
#include "wx/hyperlink.h"

class LTDialog_About : public wxDialog
{
private:
	wxBoxSizer *mainSizer;

	wxStaticText *title1;
	wxStaticText *title2;
	wxStaticText *title3;
	wxHyperlinkCtrl *title4;

	wxStaticText *ref;
	wxHyperlinkCtrl *aoktsLink;
	wxHyperlinkCtrl *tseLink;
	
	wxButton *doneButton;
public:
	LTDialog_About(wxWindow *parent);

	void onDone(wxCommandEvent &event);
};

#endif
