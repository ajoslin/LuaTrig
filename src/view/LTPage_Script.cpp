#include "LTPage_Script.h"
#include "LTFrame.h"
#include "../lua/LuaFile.h"
#include "../genie/Scenario.h"
#include "LTDialog_ChooseScen.h"
#include "../defines.h"
#include "wx/msgdlg.h"

LTPage_Script::LTPage_Script(LTFrame *frame, wxNotebook *parent, wxFileName *fname)
	: LTPage_FileBase(frame, parent, FTYPE_Script, fname)
{
	pickBaseSizer = new wxBoxSizer(wxVERTICAL);
	pickTargetSizer = new wxBoxSizer(wxVERTICAL);

	openFileButton = new wxButton(this, wxID_ANY, wxT(STR_LUA_OPEN));
	topButtonsSizer->Add(openFileButton);

	pickBaseText = new wxStaticText(this, wxID_ANY, wxT(STR_LUA_BASE));
	pickBaseButton = new wxButton(this, wxID_ANY, wxT(STR_BROWSE), wxDefaultPosition, wxSize(250, wxDefaultSize.GetHeight()));

	pickBaseSizer->Add(pickBaseText);
	//pickBaseSizer->AddSpacer(5);
	pickBaseSizer->Add(pickBaseButton);

	pickTargetText = new wxStaticText(this, wxID_ANY, wxT(STR_LUA_TARGET));
	pickTargetButton = new wxButton(this, wxID_ANY, wxT(STR_BROWSE), wxDefaultPosition, wxSize(250, wxDefaultSize.GetHeight()));
	pickTargetDialog = new wxFileDialog(this, wxT(STR_FILE_SELECT), frame->getScenarioDir(), wxT(""), wxT(STR_EXT_SCX), wxFD_SAVE | wxFD_CHANGE_DIR);
	pickTargetCheckBox = new wxCheckBox(this, wxID_ANY, wxT(STR_LUA_OVERWRITE));

	pickTargetSizer->Add(pickTargetButton, 1, wxALIGN_CENTER_VERTICAL);
	pickTargetSizer->AddSpacer(5);
	pickTargetSizer->Add(pickTargetCheckBox, 1, wxALIGN_CENTER_VERTICAL);

	writeButton = new wxButton(this, wxID_ANY, wxT(STR_LUA_WRITE));
	writeButton->Disable();
	successText = new wxStaticText(this, wxID_ANY, wxT(""));
	timer = new wxTimer(this, wxID_ANY);

	mainSizer->AddSpacer(15);
	mainSizer->Add(pickBaseSizer);
	mainSizer->AddSpacer(15);
	mainSizer->Add(pickTargetText);
	mainSizer->Add(pickTargetSizer);
	mainSizer->AddSpacer(15);
	mainSizer->Add(writeButton);
	mainSizer->AddSpacer(5);
	mainSizer->Add(successText);

	Connect(openFileButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onOpenFileButtonPressed));
	Connect(pickBaseButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onPickBaseButtonPressed));
	Connect(pickTargetButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetButtonPressed));
	Connect(pickTargetCheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetCheckBoxChanged));
	Connect(writeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onWriteButtonPressed));
	Connect(timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(LTPage_Script::onTimer));

	//Set these to none by default
	baseScenario = new wxFileName(wxT(""));
	targetScenario = new wxFileName(wxT(""));

	luaFile = new LuaFile(file->GetFullPath().mb_str().data(), file->GetFullPath().Len());
	read();

}

void LTPage_Script::onOpenFileButtonPressed(wxCommandEvent& event)
{
	system(file->GetFullPath());
}

void LTPage_Script::onPickBaseButtonPressed(wxCommandEvent &event)
{
	//create an array of strings for the pick scenario dialog
	//first get len
	int len=0;
	for (int i=0; i<frame->openFiles.size(); i++)
		if (frame->openFiles[i]->type==FTYPE_Scenario) 
			len++;
		
	//if len is 0, no scns opened
	if (len==0)
	{
		wxMessageDialog *msg = new wxMessageDialog(this, wxT(STR_LUA_BASE_ERR), wxT(STR_ERROR), wxOK);
		msg->ShowModal();
		delete msg;
	}
	else
	{
		//create array of len, and fill it with scens
		wxString choices[len];
		wxString choicePaths[len];

		int idx=0;
		for (int i=0; i<frame->openFiles.size(); i++)
		{
			if (frame->openFiles[i]->type==FTYPE_Scenario)
			{
				wxFileName *file=frame->openFiles[i]->file;
				choices[idx]=/*file->GetDirs().Last() + wxT("/") + */file->GetFullName();
				choicePaths[idx]=file->GetFullPath();
				idx++;
			}
		}
		
		//finally create the dialog
		LTDialog_ChooseScen *chooseScnDialog = new LTDialog_ChooseScen(this, choices, len);
		int choice=chooseScnDialog->ShowModal();
		delete chooseScnDialog;
		
		if (choice != wxNOT_FOUND)
		{
			baseScenario->Assign(choicePaths[choice]);
			setBaseScenario(baseScenario);
		}
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
		setTargetScenario(targetScenario);
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
		//pickTargetButton->Enable(true);
		//if targetscenario is still same as base scenario, ignore someone turning checkbox off
		if (baseScenario==targetScenario)
		{
			wxCommandEvent checkCmd(wxEVT_COMMAND_CHECKBOX_CLICKED, pickTargetCheckBox->GetId());
			ProcessEvent(checkCmd);
			printf("unchecked but same\n");
		}
	}
}

void LTPage_Script::onWriteButtonPressed(wxCommandEvent &event)
{
	write(targetScenario);
	successText->SetLabel(wxT(STR_TABSUCCESS));
	timer->Start(700, wxTIMER_ONE_SHOT);
}

void LTPage_Script::onTimer(wxTimerEvent &event)
{
	if (hasError)
	{
		wxCommandEvent cmdClose(wxEVT_COMMAND_BUTTON_CLICKED, wxID_CANCEL);
		ProcessEvent(cmdClose);
	}
	else
		successText->SetLabel(wxT(""));
}

void LTPage_Script::setBaseScenario(wxFileName *fname)
{
	baseScenario->Assign(fname->GetFullPath());

	if (!fname->FileExists())
	{
		pickBaseButton->SetLabel(wxT(STR_BROWSE));
	}
	else
	{
		pickBaseButton->SetLabel(fname->GetFullName());
	}
	
	if (pickTargetCheckBox->GetValue()==true)
		setTargetScenario(fname);
	
	checkCanWrite();
}

void LTPage_Script::setTargetScenario(wxFileName *fname)
{
	targetScenario->Assign(fname->GetFullPath());

	if (fname->GetFullPath()==wxT(""))
	{
		pickTargetButton->SetLabel(wxT(STR_BROWSE));
	}
	else
	{
		pickTargetButton->SetLabel(fname->GetFullName());
	}
	if (fname!=baseScenario)
		pickTargetCheckBox->SetValue(false);
	checkCanWrite();
}

void LTPage_Script::checkCanWrite()
{
	if (targetScenario->GetFullPath()!=wxT("") && baseScenario->FileExists())
		writeButton->Enable(true);
	else
		writeButton->Disable();
}


void LTPage_Script::write(wxFileName *fname)
{
	wxBeginBusyCursor();

	Scenario *out = new Scenario(baseScenario->GetFullPath().mb_str().data(), baseScenario->GetFullPath().Len());
	out->triggers=luaFile->triggers;
	out->write(fname->GetFullPath().mb_str().data());

	wxEndBusyCursor();
}

void LTPage_Script::read()
{
	wxBeginBusyCursor();

	bool haserrors = luaFile->read();
	if (haserrors)
	{
		wxString err=wxString::FromUTF8(luaFile->error());

		//replace filename:linenum:error with filename: Line linenum:error for readability
		err.Replace(wxT(".lua:"), wxT(".lua: line "), false); 
		frame->onError(err);

		//close after an ms, it doesn't want to close immediately
		timer->Start(1, wxTIMER_ONE_SHOT);
		hasError=true;
	}
	else
	{
		setTriggerCount(luaFile->triggers.size());
	}

	wxEndBusyCursor();
}