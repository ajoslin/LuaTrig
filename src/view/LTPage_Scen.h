#ifndef LT_PAGE_SCEN_H_
#define LT_PAGE_SCEN_H_

#include "wx/wx.h"
#include "wx/filedlg.h"
#include "LTPage_FileBase.h"
#include "../genie/Scenario.h"

class LTFrame; //fwd here so we don't have to include

class LTPage_Scen : public LTPage_FileBase
{
private:
	LTFrame *frame;
	Scenario *scenario;

	wxBoxSizer *infoSizer;
	wxBoxSizer *pickSizer;
	wxBoxSizer *exportSizer;

	wxStaticText *numTriggersLabelText;
	wxStaticText *numTriggersText;

	wxStaticText *saveScriptText;
	wxFileDialog *saveScriptDialog;
	wxButton *saveScriptButton;

	wxButton *exportButton;
	wxCheckBox *commentsCheckBox;

public:	
	LTPage_Scen(LTFrame *frame, wxNotebook *parent, wxString dir, wxString filename);

	void onSaveButtonPressed(wxCommandEvent &event);
	void onExportPressed(wxCommandEvent &event);

	virtual void write(wxString path);
	virtual void read();
};

#endif