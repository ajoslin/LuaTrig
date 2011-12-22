#ifndef LT_FILE_BASE_H_
#define LT_FILE_BASE_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/filename.h"

class LTFrame; //fwd so we don't have to include

enum FileType
{
	FTYPE_Script,
	FTYPE_Scenario
};

class LTPage_FileBase : public wxPanel
{
protected:
	LTFrame *frame;

	wxBoxSizer *areaSizer;
	wxBoxSizer *infoSizer;

	wxButton *closeButton;
	wxButton *reloadButton;

	wxStaticText *numTriggersLabelText;
	wxStaticText *numTriggersText;

	FileType type;

public:
	LTPage_FileBase(LTFrame *frame, wxNotebook *parent, FileType type, wxFileName *fname);

	virtual void onClose(wxCommandEvent &event);
	virtual void onReload(wxCommandEvent &event);
	
	virtual void write(wxFileName *fname) = 0;
	virtual void read() = 0;

	//called by LTFrame when the program's open files have changed
	//Used by LTPage_Script
	virtual void onOpenFilesChanged();

	FileType getType() { return type; }

	wxFileName *file;
};

#endif