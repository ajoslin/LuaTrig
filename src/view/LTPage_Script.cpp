#include "LTPage_Script.h"
#include "LTFrame.h"
#include "wx/clntdata.h"

LTPage_Script::LTPage_Script(LTFrame *frame, wxNotebook *parent, wxFileName *fname)
	: LTPage_FileBase(frame, parent, FTYPE_Script, fname)
{
	pickBaseSizer = new wxBoxSizer(wxVERTICAL);
	pickTargetSizer = new wxBoxSizer(wxHORIZONTAL);

	pickBaseText = new wxStaticText(this, wxID_ANY, wxT("Select the scenario this script is based from: "));
	pickBaseComboBox = new wxComboBox(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);

	pickBaseSizer->Add(pickBaseText, 1, wxALIGN_CENTER_VERTICAL);
	pickBaseSizer->Add(pickBaseComboBox, 1, wxALIGN_CENTER_VERTICAL);

	pickTargetText = new wxStaticText(this, wxID_ANY, wxT("Select location to save scenario to: "));
	pickTargetButton = new wxButton(this, wxID_ANY, wxT("Browse..."));
	pickTargetDialog = new wxFileDialog(this, wxT("Select a location"), frame->getScenarioDir(), wxT(""), wxT("Scx file (*.scx)|*.scx"), wxFD_SAVE | wxFD_CHANGE_DIR);
	pickTargetCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Save to base scenario"));

	pickTargetSizer->Add(pickTargetButton, 1, wxALIGN_CENTER_VERTICAL);
	pickTargetSizer->AddSpacer(5);
	pickTargetSizer->Add(pickTargetCheckBox, 1, wxALIGN_CENTER_VERTICAL);

	writeButton = new wxButton(this, wxID_ANY, wxT("Write Scenario"));
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

	Connect(pickBaseComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(LTPage_Script::onScenarioComboBoxChanged));
	Connect(pickTargetButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetButtonPressed));
	Connect(pickTargetCheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetCheckBoxChanged));
	Connect(writeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onWriteButtonPressed));
	Connect(successTimer->GetId(), wxEVT_TIMER, wxTimerEventHandler(LTPage_Script::onSuccessTimer));

	//Set these to null by default
	baseScenario = new wxFileName(wxT(""));
	targetScenario = new wxFileName(wxT(""));
	dummyScenFile = new wxFileName(wxT(""));
	updatePickBaseComboBox();
}

void LTPage_Script::onScenarioComboBoxChanged(wxCommandEvent &event)
{
	int index=pickBaseComboBox->GetCurrentSelection();
	wxFileName *fname = (wxFileName *)pickBaseComboBox->GetClientObject(index);
	setBaseScenario(fname);
}

void LTPage_Script::onPickTargetButtonPressed(wxCommandEvent &event)
{
	
}

void LTPage_Script::onPickTargetCheckBoxChanged(wxCommandEvent &event)
{
	if (pickTargetCheckBox->GetValue()==true)
	{
		setTargetScenario(baseScenario);
		pickTargetButton->Disable();
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
	if (fname==NULL)
		baseScenario->Assign(wxT(""));
	else
		baseScenario->Assign(fname->GetFullPath());

	if (!fname->FileExists())
	  pickBaseComboBox->SetValue(wxT("None"));
	else
		pickBaseComboBox->SetValue(fname->GetFullName());
	
	if (pickTargetCheckBox->GetValue()==true)
		setTargetScenario(fname);
}

void LTPage_Script::setTargetScenario(wxFileName *fname)
{
	if (fname==NULL)
		targetScenario->Assign(wxT(""));
	else
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
	}
}

void LTPage_Script::updatePickBaseComboBox()
{
	pickBaseComboBox->Clear();
	pickBaseComboBox->Append(wxT("None"), dummyScenFile);
	for (int i=0; i<frame->openFiles.size(); i++)
		if (frame->openFiles[i]->getType()==FTYPE_Scenario)
			pickBaseComboBox->Append(frame->openFiles[i]->file->GetFullName(), (wxClientData *)frame->openFiles[i]->file);
}

void LTPage_Script::onOpenFilesChanged()
{
	updatePickBaseComboBox();
}

void LTPage_Script::write(wxFileName *fname)
{
	
}

void LTPage_Script::read()
{
}
