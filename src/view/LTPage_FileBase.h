#ifndef LT_FILE_BASE_H_
#define LT_FILE_BASE_H_

#include "wx/wx.h"
#include "wx/notebook.h"

enum FileType
{
	FTYPE_Lua,
	FTYPE_Scenario
};

class LTPage_FileBase : public wxPanel
{
protected:
	FileType type;

	wxButton *closeButton;
	wxButton *reloadButton;
	wxBoxSizer *areaSizer;

	wxString directory;
	wxString filename;

public:
	LTPage_FileBase(wxNotebook *parent, FileType type, wxString dir, wxString filename);

	virtual void onClose(wxCommandEvent &event);
	virtual void onReload(wxCommandEvent &event);
	
	virtual void write(wxString path) = 0;
	virtual void read() = 0;
};

#endif