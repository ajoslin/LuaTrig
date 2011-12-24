#ifndef LT_FILE_BASE_H_
#define LT_FILE_BASE_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/filename.h"

class LTFrame; //fwd so we don't have to include

class LTPage_FileBase : public wxPanel
{
protected:
	LTFrame *frame;

	wxBoxSizer *masterSizer;

	wxBoxSizer *mainSizer;
	wxBoxSizer *infoSizer;

	wxButton *closeButton;
	wxButton *reloadButton;

	wxStaticText *numTriggersLabelText;
	wxStaticText *numTriggersText;

	bool hasError;

public:
	LTPage_FileBase(LTFrame *frame, wxNotebook *parent, int type, wxFileName *fname);

	virtual void onClose(wxCommandEvent &event);
	virtual void onReload(wxCommandEvent &event);

	virtual void write(wxFileName *fname) = 0;
	virtual void read() = 0;

	//sets numTriggersText statictext
	void setTriggerCount(int count);

	wxFileName *file;
	int type;
};

#endif