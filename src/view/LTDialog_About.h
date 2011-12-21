#ifndef LT_DIALOG_ABOUT_H_
#define LT_DIALOG_ABOUT_H_

#include "wx/wx.h"
#include "wx/hyperlink.h"

class LTDialog_About : public wxDialog
{
private:
	wxBoxSizer *sizer;
	wxBoxSizer *widthSizer;

	wxStaticText *title1;
	wxStaticText *title2;
	wxStaticText *title3;

	wxStaticText *ref;
	wxHyperlinkCtrl *aoktsLink;
	wxHyperlinkCtrl *tseLink;
	
	wxButton *doneButton;
public:
	LTDialog_About(wxWindow *parent);

	void onDone(wxCommandEvent &event);
};

#endif