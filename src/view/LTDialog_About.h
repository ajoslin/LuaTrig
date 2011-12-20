#ifndef LT_DIALOG_ABOUT_H_
#define LT_DIALOG_ABOUT_H_

#include "wx/wx.h"
#include "wx/hyperlink.h"

class LTDialog_About : public wxDialog
{
public:
	LTDialog_About(wxWindow *parent);

	void onExit(wxCloseEvent &event);
};

#endif