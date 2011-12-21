#ifndef LT_PAGE_SCRIPT_H_
#define LT_PAGE_SCRIPT_H_

#include "wx/wx.h"
#include "wx/filepicker.h"
#include "LTPage_FileBase.h"

class LTFrame; //fwd here so we don't have to

class LTPage_Script : public LTPage_FileBase
{
private:
	LTFrame *frame;
public:
	LTPage_Script(LTFrame *frame, wxNotebook *parent, wxString dir, wxString filename);
	
	virtual void write(wxString path);
	virtual void read();
};

#endif