#include "LTPage_Script.h"
#include "LTFrame.h"
#include "wx/clntdata.h"
#include "../lua/LuaFile.h"
#include "../genie/Scenario.h"
#include "LTDialog_ChooseScen.h"

LTPage_Script::LTPage_Script(LTFrame *frame, wxNotebook *parent, wxFileName *fname)
	: LTPage_FileBase(frame, parent, FTYPE_Script, fname)
{
	pickBaseSizer = new wxBoxSizer(wxVERTICAL);
	pickTargetSizer = new wxBoxSizer(wxHORIZONTAL);

	pickBaseText = new wxStaticText(this, wxID_ANY, wxT("Scenario this script is based from: "));
	pickBaseButton = new wxButton(this, wxID_ANY, wxT("Choose Scenario..."));

	pickBaseSizer->Add(pickBaseText);
	//pickBaseSizer->AddSpacer(5);
	pickBaseSizer->Add(pickBaseButton);

	pickTargetText = new wxStaticText(this, wxID_ANY, wxT("Select location to save scenario to: "));
	pickTargetButton = new wxButton(this, wxID_ANY, wxT("Browse..."));
	pickTargetDialog = new wxFileDialog(this, wxT("Select a location"), frame->getScenarioDir(), wxT(""), wxT("Scx file (*.scx)|*.scx"), wxFD_SAVE | wxFD_CHANGE_DIR);
	pickTargetCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Save to base scenario"));

	pickTargetSizer->Add(pickTargetButton, 1, wxALIGN_CENTER_VERTICAL);
	pickTargetSizer->AddSpacer(5);
	pickTargetSizer->Add(pickTargetCheckBox, 1, wxALIGN_CENTER_VERTICAL);

	writeButton = new wxButton(this, wxID_ANY, wxT("Write Scenario File"));
	successText = new wxStaticText(this, wxID_ANY, wxT(""));
	successTimer = new wxTimer(this, wxID_ANY);

	areaSizer->AddSpacer(15);
	areaSizer->Add(pickBaseSizer);
	areaSizer->AddSpacer(15);
	areaSizer->Add(pickTargetText);
	areaSizer->Add(pickTargetSizer);
	areaSizer->AddSpacer(15);
	areaSizer->Add(writeButton);
	areaSizer->AddSpacer(5);
	areaSizer->Add(successText);

	Connect(pickBaseButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onPickBaseButtonPressed));
	Connect(pickTargetButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetButtonPressed));
	Connect(pickTargetCheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetCheckBoxChanged));
	Connect(writeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onWriteButtonPressed));
	Connect(successTimer->GetId(), wxEVT_TIMER, wxTimerEventHandler(LTPage_Script::onSuccessTimer));

	//Set these to null by default
	baseScenario = new wxFileName(wxT(""));
	targetScenario = new wxFileName(wxT(""));

	//hide while it's reading 
	areaSizer->Show(false);
	luaFile = new LuaFile(file->GetFullPath().mb_str().data(), file->GetFullPath().Len());
	read();
	areaSizer->Show(true);

}

void LTPage_Script::onPickBaseButtonPressed(wxCommandEvent &event)
{
	//create an array of strings for the pick scenario dialog
	//first get len
	int len=0;
	for (int i=0; igit resolveframe->openFiles.size(); i++)
		if (frame->openFiles[i]->type==FTYPE_Scenario) 
			len++;
	
	//create array of len, and fill it with scens
	wxString choices[len];
	int idx=0;
	for (int i=0; i<frame->openFiles.size(); i++)
	{
		if (frame->openFiles[i]->type==FTYPE_Scenario)
		{
			wxFileName *file=frame->openFiles[i]->file;
			choices[idx++]=/*file->GetDirs().Last() + wxT("/") + */file->GetFullName();
		}
	}
	
	//finally create the dialog
	LTDialog_ChooseScen *chooseScnDialog = new LTDialog_ChooseScen(this, choices, len);
	int choice=chooseScnDialog->ShowModal();
	delete chooseScnDialog;
	if (choice != wxNOT_FOUND)
	{
		baseScenario->Assign(choices[choice]);
		setBaseScenario(baseScenario);
	}
}

void LTPage_Script::onPickTargetButtonPressed(wxCommandEvent &event)
{
	if (targetScenario->FileExists())
		pickTargetDialog->SetPath(targetScenario->GetFullPath());

	int id=pickTargetDialog->ShowModal();
	if (id==wxID_OK)
	{
		targetScenario->Assign(pickTargetDialog->GetPath());
		setTargetScenario(baseScenario);
	}
}

void LTPage_Script::onPickTargetCheckBoxChanged(wxCommandEvent &event)
{
	if (pickTargetCheckBox->GetValue()==true)
	{
		setTargetScenario(baseScenario);
		//pickTargetButton->Disable();
	}
	else
	{
		pickTargetButton->Enable(true);
		pickTargetButton->SetLabel(wxT("Browse..."));
	}
}

void LTPage_Script::onWriteButtonPressed(wxCommandEvent &event)
{
	
}

void LTPage_Script::onSuccessTimer(wxTimerEvent &event)
{
	
}

void LTPage_Script::setBaseScenario(wxFileName *fname)
{
	baseScenario->Assign(fname->GetFullPath());

	if (!fname->FileExists())
		pickBaseButton->SetLabel(wxT("Choose Scenario..."));
	else
		pickBaseButton->SetLabel(fname->GetFullName());
	
	if (pickTargetCheckBox->GetValue()==true)
		setTargetScenario(fname);
}

void LTPage_Script::setTargetScenario(wxFileName *fname)
{
	targetScenario->Assign(fname->GetFullPath());

	if (!fname->FileExists())
	{
		if (pickTargetCheckBox->GetValue()==true)
			pickTargetButton->SetLabel(wxT("No Base Scenario!"));
		else
			pickTargetButton->SetLabel(wxT("Browse..."));
	}
	else
	{
		pickTargetButton->SetLabel(fname->GetFullName());
		//if targetScenario changes and same as base scenario is checked but it's not the same...
		//then uncheck same as base scenario
		if (pickTargetCheckBox->GetValue()==true && fname!=baseScenario)
			pickTargetCheckBox->SetValue(false);
	}
}


void LTPage_Script::write(wxFileName *fname)
{
	
}

void LTPage_Script::read()
{
