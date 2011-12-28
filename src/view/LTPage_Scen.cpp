#include "LTPage_Scen.h"
#include "LTFrame.h"
#include "../lua/LuaFile.h"
#include "../genie/Scenario.h"
#include "../res/check.xpm"
#include "../defines.h"

LTPage_Scen::LTPage_Scen(LTFrame *frame, wxNotebook *parent, wxFileName *fname)
	: LTPage_FileBase(frame, parent, FTYPE_Scenario, fname)
{
	infoSizer = new wxBoxSizer(wxHORIZONTAL);
	pickSizer = new wxBoxSizer(wxVERTICAL);
	writeSizer = new wxBoxSizer(wxHORIZONTAL);

	saveScriptText = new wxStaticText(this, wxID_ANY, wxT(STR_SCEN_SAVETITLE));
	saveScriptDialog = new wxFileDialog(this, wxT(STR_FILE_SELECT), frame->getScriptDir(), wxT(""), wxT(STR_EXT_LUA), wxFD_SAVE | wxFD_CHANGE_DIR);
	saveScriptButton = new wxButton(this, wxID_ANY, wxT(STR_BROWSE), wxDefaultPosition, wxSize(250, wxDefaultSize.GetHeight()));

	pickSizer->Add(saveScriptText, 1, wxALIGN_CENTER_VERTICAL);
	pickSizer->Add(saveScriptButton);

	writeButton = new wxButton(this, wxID_ANY, wxT(STR_SCEN_WRITE));
	writeButton->Disable();

	writeSizer->Add(writeButton, 1, wxALIGN_CENTER_VERTICAL);

	successText = new wxStaticText(this, wxID_ANY, wxT(""));
	timer = new wxTimer(this, wxID_ANY);

	mainSizer->AddSpacer(15);
	mainSizer->Add(pickSizer);
	mainSizer->AddSpacer(15);
	mainSizer->Add(writeSizer);
	mainSizer->AddSpacer(5);
	mainSizer->Add(successText);

	Connect(saveScriptButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Scen::onSaveButtonPressed));
	Connect(writeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Scen::onExportPressed));
	Connect(timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(LTPage_Scen::onTimer));

	scenario = new Scenario(file->GetFullPath().mb_str().data(), file->GetFullPath().Len());
	read();
}

void LTPage_Scen::onSaveButtonPressed(wxCommandEvent& event)
{
	int id=saveScriptDialog->ShowModal();
	if (id==wxID_CANCEL)
		return;

	//if a valid script location is chosen, enable write
	wxFile *testFile = new wxFile(saveScriptDialog->GetPath().c_str(), wxFile::write);
	if (testFile->IsOpened())
	{
		writeButton->Enable();
		saveScriptButton->SetLabel(saveScriptDialog->GetFilename());
	}
	else
	{
		if (writeButton->Disable()) //if was not already disabled, re-set label
			saveScriptButton->SetLabel(wxT(STR_BROWSE));
	}
	delete testFile;
}

void LTPage_Scen::onExportPressed(wxCommandEvent& event)
{
	write(new wxFileName(saveScriptDialog->GetPath()));
	successText->SetLabel(wxT(STR_TABSUCCESS));
	timer->Start(700, wxTIMER_ONE_SHOT);
}

void LTPage_Scen::onTimer(wxTimerEvent &event)
{
	successText->SetLabel(wxT(""));
}

void LTPage_Scen::write(wxFileName *fname)
{
	wxBeginBusyCursor();

	//copy triggers from scn to luafile
	LuaFile *lf = new LuaFile(fname->GetFullPath().mb_str().data(), fname->GetFullPath().Len());
	lf->triggers=scenario->triggers;
	
	lf->write(fname->GetFullPath().mb_str().data());
	delete lf;

	frame->openScript(fname, true);

	wxEndBusyCursor();
}

void LTPage_Scen::read()
{
	//display busy cursor while opening / reading scen
	wxBeginBusyCursor();

	scenario->open();
	scenario->read(true);
	scenario->cleanup();

	setTriggerCount(scenario->triggers.size());

	wxEndBusyCursor();
}
