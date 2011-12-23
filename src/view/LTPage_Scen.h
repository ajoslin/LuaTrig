#ifndef LT_PAGE_SCEN_H_
#define LT_PAGE_SCEN_H_

#include "wx/wx.h"
#include "wx/filedlg.h"
#include "wx/timer.h"
#include "LTPage_FileBase.h"

class LTFrame; //fwd here so we don't have to include
class Scenario;

class LTPage_Scen : public LTPage_FileBase
{
private:
	Scenario *scenario;
	
	wxBoxSizer *pickSizer;
	wxBoxSizer *writeSizer;

	wxStaticText *saveScriptText;
	wxFileDialog *saveScriptDialog;
	wxButton *saveScriptButton;

	wxButton *writeButton;
	wxCheckBox *commentsCheckBox;
	wxStaticText *successText;
	wxTimer *successTimer;


public:	
	LTPage_Scen(LTFrame *frame, wxNotebook *parent, wxFileName *fname);

	void onSaveButtonPressed(wxCommandEvent &event);
	void onExportPressed(wxCommandEvent &event);
	void onSuccessTimer(wxTimerEvent &event);

	virtual void write(wxFileName *fname);
	virtual void read();
};

#endif