#include "LTPage_Scen.h"
#include "LTFrame.h"
#include "string.h"
#include "../lua/LuaFile.h"

LTPage_Scen::LTPage_Scen(LTFrame *frame, wxNotebook *parent, wxString dir, wxString filename)
	: LTPage_FileBase(parent, FTYPE_Scenario, dir, filename)
{
	this->frame = frame;

	infoSizer = new wxBoxSizer(wxHORIZONTAL);
	pickSizer = new wxBoxSizer(wxHORIZONTAL);
	exportSizer = new wxBoxSizer(wxHORIZONTAL);

	numTriggersLabelText = new wxStaticText(this, wxID_ANY, wxT("Scenario Trigger Count: "));
	numTriggersText = new wxStaticText(this, wxID_ANY, wxT(""));

	infoSizer->Add(numTriggersLabelText, 1, wxALIGN_CENTER_VERTICAL);
	infoSizer->Add(numTriggersText, 1, wxALIGN_CENTER_VERTICAL);

	saveScriptText = new wxStaticText(this, wxID_ANY, wxT("Choose script file location: "));
	saveScriptDialog = new wxFileDialog(this, wxT("Select a location"), frame->getScriptDir(), wxT(""), wxT("Lua file (*.lua)|*.lua"), wxFD_SAVE | wxFD_CHANGE_DIR);
	saveScriptButton = new wxButton(this, wxID_ANY, wxT("Browse..."));

	pickSizer->Add(saveScriptText, 1, wxALIGN_CENTER_VERTICAL);
	pickSizer->Add(saveScriptButton);

	exportButton = new wxButton(this, wxID_ANY, wxT("Write Triggers"));
	exportButton->Disable();
	commentsCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Generate Comments"));
	commentsCheckBox->SetValue(true);

	exportSizer->Add(exportButton, 1, wxALIGN_CENTER_VERTICAL);
	exportSizer->AddSpacer(5);
	exportSizer->Add(commentsCheckBox, 1, wxALIGN_CENTER_VERTICAL);

	areaSizer->AddSpacer(10);
	areaSizer->Add(infoSizer);
	areaSizer->AddSpacer(15);
	areaSizer->Add(pickSizer);
	areaSizer->AddSpacer(10);
	areaSizer->Add(exportSizer);

	wxString path;
	path = dir + wxT('/') + filename;
	scenario = new Scenario(path.c_str());
	read();

	Connect(saveScriptButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Scen::onSaveButtonPressed));
	Connect(exportButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Scen::onExportPressed));

}

void LTPage_Scen::onSaveButtonPressed(wxCommandEvent& event)
{
	int id=saveScriptDialog->ShowModal();
	if (id==wxID_CANCEL)
		return;

	//if a valid script location is chosen, enable export
	wxFile *testFile = new wxFile(saveScriptDialog->GetPath().c_str(), wxFile::write);
	if (testFile->IsOpened())
	{
		exportButton->Enable();
		saveScriptButton->SetLabel(saveScriptDialog->GetFilename());
	}
	else
	{
		if (exportButton->Disable()) //if was not already disabled, re-set label
			saveScriptButton->SetLabel(wxT("Browse..."));
	}
	delete testFile;
}

void LTPage_Scen::onExportPressed(wxCommandEvent& event)
{
	write(saveScriptDialog->GetPath());
}

void LTPage_Scen::write(wxString path)
{
	wxBeginBusyCursor();

	//copy triggers from scn to luafile
	LuaFile *lf = new LuaFile(path.c_str());
	lf->triggers=scenario->triggers;
	
	lf->write(path.c_str(), commentsCheckBox->GetValue());
	delete lf;

	wxEndBusyCursor();
}

void LTPage_Scen::read()
{
	//display busy cursor while opening / reading scen
	wxBeginBusyCursor();

	//remove triggercount before reloading, to make it look reloadish
	numTriggersText->SetLabel(wxT("")); 

	scenario->open();
	scenario->read(true);
	scenario->cleanup();

	char *triggersStr = new char[sizeof(long)*8+1];
	sprintf(triggersStr, "%d", scenario->numtriggers);
	numTriggersText->SetLabel(wxString(triggersStr));

	wxEndBusyCursor();
}