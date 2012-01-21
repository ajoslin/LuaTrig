#ifndef LT_PAGE_SCEN_H_
#define LT_PAGE_SCEN_H_

#include "wx/wx.h"
#include "wx/filedlg.h"
#include "LTPage_File.h"

class LTPage_Scen : public LTPage_File
{
private:	
	wxBoxSizer *pickSizer;
	wxBoxSizer *writeSizer;

	wxStaticText *saveScriptText;
	wxFileDialog *saveScriptDialog;
	wxButton *saveScriptButton;
	wxButton *saveUnitsScriptButton;

	wxButton *writeButton;

public:	
	LTPage_Scen(wxWindow *parent);

	void onSaveButtonPressed(wxCommandEvent &event);
	void onWriteButtonPressed(wxCommandEvent &event);

	void write(wxFileName fname);
	void open(wxFileName fname);
	void read();
};

#endif
