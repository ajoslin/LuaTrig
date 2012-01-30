#include "LTPage_Script.h"
#include "../control/LuaFileController.h"
#include "../control/ScenarioFileController.h"
#include "../defines.h"
#include "LuaTrigMain.h"
#include "LTFrame.h"
#include "LTDialog_ChooseScen.h"

LTPage_Script::LTPage_Script(wxWindow *parent)
	: LTPage_File(parent)
{
	pickBaseSizer = new wxBoxSizer(wxVERTICAL);
	pickTargetSizer = new wxBoxSizer(wxVERTICAL);

	openBtn->Show(); //the File page, this class's parent, default hides the open button. only scripts should show it.

	pickBaseText = new wxStaticText(this, wxID_ANY, wxT(STR_LUA_BASE));
	pickBaseButton = new wxButton(this, wxID_ANY, wxT(STR_BROWSE), wxDefaultPosition, wxSize(250, wxDefaultSize.GetHeight()));

	pickBaseSizer->Add(pickBaseText);
	pickBaseSizer->Add(pickBaseButton);

	pickTargetText = new wxStaticText(this, wxID_ANY, wxT(STR_LUA_TARGET));
	pickTargetButton = new wxButton(this, wxID_ANY, wxT(STR_BROWSE), wxDefaultPosition, wxSize(250, wxDefaultSize.GetHeight()));
	pickTargetDialog = new wxFileDialog(this, wxT(STR_FILE_SELECT), LuaTrigMain::configRead(wxT(STR_CFG_SCNDIR)), wxT(""), wxT(STR_EXT_SCX), wxFD_SAVE | wxFD_CHANGE_DIR);
	pickTargetCheckBox = new wxCheckBox(this, wxID_ANY, wxT(STR_LUA_OVERWRITE));

	pickTargetSizer->Add(pickTargetText, 1, wxALIGN_CENTER_VERTICAL);
	pickTargetSizer->Add(pickTargetButton, 1, wxALIGN_CENTER_VERTICAL);
	pickTargetSizer->Add(pickTargetCheckBox, 1, wxALIGN_CENTER_VERTICAL);

	writeButton = new wxButton(this, wxID_ANY, wxT(STR_LUA_WRITE));
	writeButton->Disable();

	masterSizer->AddSpacer(15);
	masterSizer->Add(pickBaseSizer);
	masterSizer->AddSpacer(15);
	masterSizer->Add(pickTargetSizer);
	masterSizer->AddSpacer(15);
	masterSizer->Add(writeButton);

	//openBtn in _File
	Connect(openBtn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onOpenFileButtonPressed));
	Connect(pickBaseButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onPickBaseButtonPressed));
	Connect(pickTargetButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetButtonPressed));
	Connect(pickTargetCheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(LTPage_Script::onPickTargetCheckBoxChanged));
	Connect(writeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_Script::onWriteButtonPressed));

	currentFile = new LuaFileController();
}

void LTPage_Script::onOpenFileButtonPressed(wxCommandEvent& event)
{
	wxString call=wxT("\"")+wxString::FromUTF8(currentFile->getPath())+wxT("\"");
	system(call.mb_str().data());
}

void LTPage_Script::onPickBaseButtonPressed(wxCommandEvent &event)
{
	//create a dialog with a radiobutton list of all open scenarios to choose as the base scenario
	LTFrame *frame = LTFrame::instance();
	int count=frame->getFileBookPageCount();

	wxString choices[count];
	wxFileName filenames[count];
	int len=0;
	for (int i=0; i<count; i++)
	{
		LTPage_File * file = frame->getFileBookPage(i);
		wxFileName fname = file->getCurrentFileName();
		if (file!=NULL && frame->typeFromFileName(fname)==FTYPE_Scenario)
		{
			choices[len]=fname.GetFullName();
			filenames[len]=fname;
			len++;
		}
	}

	//if no scns open, give error
	if (len==0)
	{
		wxMessageDialog *msg = new wxMessageDialog(this, wxT(STR_LUA_BASE_ERR), wxT(STR_ERROR), wxOK);
		msg->ShowModal();
		delete msg;
	}
	else
	{
		LTDialog_ChooseScen *chooseScnDialog = new LTDialog_ChooseScen(this, choices, len);
		int choice=chooseScnDialog->ShowModal();
		delete chooseScnDialog;

		if (choice!=wxNOT_FOUND)
			setBaseScenario(filenames[choice]);
	}
}

void LTPage_Script::onPickTargetButtonPressed(wxCommandEvent &event)
{
	if (targetScenario.FileExists())
		pickTargetDialog->SetPath(targetScenario.GetFullPath());

	int id=pickTargetDialog->ShowModal();
	if (id==wxID_OK)
	{
		targetScenario.Assign(pickTargetDialog->GetPath());
		setTargetScenario(targetScenario);
	}
}

void LTPage_Script::onPickTargetCheckBoxChanged(wxCommandEvent &event)
{
	if (pickTargetCheckBox->GetValue()==true)
	{
		setTargetScenario(baseScenario);
	}
}

void LTPage_Script::onWriteButtonPressed(wxCommandEvent &event)
{
	write(targetScenario);
}

void LTPage_Script::setBaseScenario(wxFileName fname)
{
	baseScenario = fname;

	if (!fname.FileExists())
	{
		pickBaseButton->SetLabel(wxT(STR_BROWSE));
	}
	else
	{
		pickBaseButton->SetLabel(fname.GetFullName());
	}
	
	if (pickTargetCheckBox->GetValue()==true)
		setTargetScenario(fname);
	
	checkCanWrite();
}

void LTPage_Script::setTargetScenario(wxFileName fname)
{
	targetScenario = fname;

	if (fname.GetFullPath()==wxT(""))
	{
		pickTargetButton->SetLabel(wxT(STR_BROWSE));
	}
	else
	{
		pickTargetButton->SetLabel(fname.GetFullName());
	}
	if (fname!=baseScenario)
		pickTargetCheckBox->SetValue(false);
	checkCanWrite();
}

void LTPage_Script::checkCanWrite()
{
	if (targetScenario.GetFullPath()!=wxT("") && baseScenario.FileExists())
		writeButton->Enable(true);
	else
		writeButton->Disable();
}

void LTPage_Script::open(wxFileName fname)
{
	currentFile->setPath(fname.GetFullPath().mb_str().data());
	read();
}

void LTPage_Script::write(wxFileName fname)
{
	wxBeginBusyCursor();

	ScenarioFileController * newScn = new ScenarioFileController();
	newScn->setPath(baseScenario.GetFullPath().mb_str().data());
	newScn->copyTriggers(currentFile);
	newScn->write(fname.GetFullPath().mb_str().data());
	delete newScn;

	onOpenFile(fname);

	wxEndBusyCursor();
}

void LTPage_Script::read()
{
	wxBeginBusyCursor();

	FileError readErr = currentFile->read();
	if (!readErr.message.empty())
	{
		wxString errStr(readErr.message.c_str(), wxConvUTF8);
		//replace 'filename.lua:linenum: error' with 'filename.lua: line linenum: error' for readability
		errStr.Replace(wxT(".lua:"), wxT(".lua: line "), false); 
		setLabelError(errStr);

		pickBaseSizer->Show(false);
		pickTargetText->Show(false);
		pickTargetSizer->Show(false);
		writeButton->Show(false);
	}
	else
	{
		setLabelTriggers(currentFile->getTriggers().size());

		pickBaseSizer->Show(true);
		pickTargetText->Show(true);
		pickTargetSizer->Show(true);
		writeButton->Show(true);
	}

	wxEndBusyCursor();
}

