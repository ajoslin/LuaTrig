#ifndef LT_PAGE_SCRIPT_H_
#define LT_PAGE_SCRIPT_H_

#include "wx/wx.h"
#include "wx/filepicker.h"
#include "wx/timer.h"
#include "LTPage_FileBase.h"

class LTFrame; //fwd here so we don't have to include
class LuaFile;

class LTPage_Script : public LTPage_FileBase
{
private:
	LuaFile *luaFile;

	wxBoxSizer *pickBaseSizer;
	wxBoxSizer *pickTargetSizer;

	wxButton *openFileButton;

	wxStaticText *pickBaseText;
	wxButton *pickBaseButton;

	wxStaticText *pickTargetText;
	wxButton *pickTargetButton;
	wxFileDialog *pickTargetDialog;
	wxCheckBox *pickTargetCheckBox;

	wxButton *writeButton;
	wxStaticText *successText;
	wxTimer *timer;

	wxFileName *baseScenario;
	wxFileName *targetScenario;
	wxFileName *dummyScenFile;

	void updatePickBaseComboBox();

public:
	LTPage_Script(LTFrame *frame, wxNotebook *parent, wxFileName *fname);

	void onOpenFileButtonPressed(wxCommandEvent &event);
	void onPickBaseButtonPressed(wxCommandEvent &event);
	void onPickTargetButtonPressed(wxCommandEvent &event);
	void onPickTargetCheckBoxChanged(wxCommandEvent &event);
	void onWriteButtonPressed(wxCommandEvent &event);
	void onTimer(wxTimerEvent &event);

	void setBaseScenario(wxFileName *fname);
	void setTargetScenario(wxFileName *fname);
	void checkCanWrite();

	virtual void write(wxFileName *fname);
	virtual void read();


};

#endif