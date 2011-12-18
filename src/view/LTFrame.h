#ifndef LT_FRAME_H_
#define LT_FRAME_H_

#include "wx/wx.h"
#include "wx/dirdlg.h"

class LTFrame : public wxFrame
{
public:
	LTFrame(const wxString& title);

	//Constructors
	/*void InitSettingsControls();
	void InitImportControls();
	void InitExportControls();
	void InitTriggerGenControls();

	bool OnSaveLua(wxCommandEvent& event);
	bool OnSaveScen(wxCommandEvent& event);
	bool OnLoadLua(wxCommandEvent& event);
	bool OnLoadScen(wxCommandEvent& event);	*/
};

#endif