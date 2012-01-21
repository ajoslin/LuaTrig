#ifndef LT_FILE_BASE_H_
#define LT_FILE_BASE_H_

#include "../control/FileController.h"
#include "wx/wx.h"
#include "wx/filename.h"

class LTPage_File : public wxPanel
{
protected:
	LTPage_File(wxWindow *parent);

	wxBoxSizer *masterSizer;
	wxBoxSizer *textSizer;

	wxButton *closeBtn;
	wxButton *reloadBtn;
	wxButton *openBtn;

	wxStaticText *textTitle;
	wxStaticText *textContent;

	FileController *currentFile;

	void setLabelTriggers(int num);
	void setLabelError(wxString err);

public:
	virtual void write(wxFileName fname) = 0;
	virtual void open(wxFileName fname) = 0;
	virtual void read() = 0;

	void onCloseButtonPressed(wxCommandEvent &e);
	void onReloadButtonPressed(wxCommandEvent &e);

	//these send events to this wxPanel, for the parent frame to catch and actually open/close the file given
	void onOpenFile(wxFileName fname);
	void onCloseFile();

	wxFileName getCurrentFileName();
};

#endif
