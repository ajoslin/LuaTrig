#ifndef LT_PAGE_SCRIPT_H_
#define LT_PAGE_SCRIPT_H_

#include "wx/wx.h"
#include "wx/filepicker.h"
#include "LTPage_File.h"

class LTFrame; //fwd here so we don't have to include
class LuaFile;

class LTPage_Script : public LTPage_File
{
private:
	wxBoxSizer *pickBaseSizer;
	wxBoxSizer *pickTargetSizer;

	wxStaticText *pickBaseText;
	wxButton *pickBaseButton;

	wxStaticText *pickTargetText;
	wxButton *pickTargetButton;
	wxFileDialog *pickTargetDialog;
	wxCheckBox *pickTargetCheckBox;

	wxButton *writeButton;

	wxFileName baseScenario;
	wxFileName targetScenario;

	void setBaseScenario(wxFileName fname);
	void setTargetScenario(wxFileName fname);
	void checkCanWrite();

public:
	LTPage_Script(wxWindow *parent);

	void onOpenFileButtonPressed(wxCommandEvent &event);
	void onPickBaseButtonPressed(wxCommandEvent &event);
	void onPickTargetButtonPressed(wxCommandEvent &event);
	void onPickTargetCheckBoxChanged(wxCommandEvent &event);
	void onWriteButtonPressed(wxCommandEvent &event);

	void write(wxFileName fname);
	void open(wxFileName fname);
	void read();
};

#endif
