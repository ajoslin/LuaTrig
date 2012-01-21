#include "LTPage_Scen.h"
#include "../control/LuaFileController.h"
#include "../control/ScenarioFileController.h"
#include "../defines.h"
#include "LuaTrigMain.h"

LTPage_Scen::LTPage_Scen(wxWindow *parent)
	: LTPage_File(parent)
{
	pickSizer = new wxBoxSizer(wxVERTICAL);
	writeSizer = new wxBoxSizer(wxHORIZONTAL);

	saveScriptText = new wxStaticText(this, wxID_ANY, wxT(STR_SCEN_SAVETITLE));
	saveScriptDialog = new wxFileDialog(this, wxT(STR_FILE_SELECT), LuaTrigMain::configRead(wxT(STR_CFG_LUADIR)), wxT(""), wxT(STR_EXT_LUA), wxFD_SAVE | wxFD_CHANGE_DIR);
	saveScriptButton = new wxButton(this, wxID_ANY, wxT(STR_BROWSE), wxDefaultPosition, wxSize(250, wxDefaultSize.GetHeight()));

	pickSizer->Add(saveScriptText, 1, wxALIGN_CENTER_VERTICAL);
	pickSizer->Add(saveScriptButton);

	writeButton = new wxButton(this, wxID_ANY, wxT(STR_SCEN_WRITE));
	writeButton->Disable();

	writeSizer->Add(writeButton, 1, wxALIGN_CENTER_VERTICAL);

	masterSizer->AddSpacer(15);
	masterSizer->Add(pickSizer);
	masterSizer->AddSpacer(15);
	masterSizer->Add(writeSizer);

	Connect(saveScriptButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Scen::onSaveButtonPressed));
	Connect(writeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Scen::onWriteButtonPressed));

	currentFile = new ScenarioFileController();
}

void LTPage_Scen::onSaveButtonPressed(wxCommandEvent& event)
{
	int id=saveScriptDialog->ShowModal();
	if (id==wxID_CANCEL)
		return;
	
	writeButton->Enable();
	saveScriptButton->SetLabel(saveScriptDialog->GetFilename());
}

void LTPage_Scen::onWriteButtonPressed(wxCommandEvent& event)
{
	wxFileName fname(wxString(saveScriptDialog->GetPath()));
	write(fname);
}

void LTPage_Scen::open(wxFileName fname)
{
	currentFile->setPath(fname.GetFullPath().mb_str().data());
	read();
}

void LTPage_Scen::write(wxFileName fname)
{
	wxBeginBusyCursor();

	LuaFileController * newLua = new LuaFileController();
	newLua->setPath(fname.GetFullPath().mb_str().data());
	newLua->copyTriggers(currentFile);
	newLua->write();
	delete newLua;

	onOpenFile(fname);

	wxEndBusyCursor();
}

void LTPage_Scen::read()
{
	//display busy cursor while opening / reading scen
	wxBeginBusyCursor();

	//scenarios never have errors right now, no need to handle it
	FileError fileErr=currentFile->read();

	setLabelTriggers(currentFile->getTriggers().size());

	wxEndBusyCursor();
}

