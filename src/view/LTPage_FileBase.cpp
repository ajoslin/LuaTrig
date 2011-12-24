#include "LTPage_FileBase.h"
#include "LTFrame.h"
#include "../defines.h"

LTPage_FileBase::LTPage_FileBase(LTFrame *frame, wxNotebook *parent, int type, wxFileName *fname)
	: wxPanel(parent)
{
	this->file = fname;
	this->frame=frame;
	this->type=type;

	hasError=false;

	masterSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer = new wxBoxSizer(wxVERTICAL);
	infoSizer = new wxBoxSizer(wxHORIZONTAL);

	closeButton = new wxButton(this, wxID_CANCEL, wxT(STR_CLOSE));
	reloadButton = new wxButton(this, wxID_ANY, wxT(STR_RELOAD));

	wxString stype = type==FTYPE_Scenario ? wxT(STR_SCENARIO) : wxT(STR_SCRIPT);
	numTriggersLabelText = new wxStaticText(this, wxID_ANY, stype+wxT(" ")+wxT(STR_FILE_TRIGCNT)+wxT(" "));
	numTriggersText = new wxStaticText(this, wxID_ANY, wxT(""));

	infoSizer->Add(numTriggersLabelText, 1, wxALIGN_CENTER_VERTICAL);
	infoSizer->Add(numTriggersText, 1, wxALIGN_CENTER_VERTICAL);

	mainSizer->Add(infoSizer);

	masterSizer->AddSpacer(15);
	masterSizer->Add(closeButton);
	masterSizer->Add(reloadButton);
	masterSizer->AddSpacer(10);
	masterSizer->Add(mainSizer);

	SetSizer(masterSizer);

	Connect(wxID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_FileBase::onClose));
	Connect(reloadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_FileBase::onReload));
}

void LTPage_FileBase::onClose(wxCommandEvent& event)
{
	frame->closeFile(file);
}

void LTPage_FileBase::onReload(wxCommandEvent& event)
{
	read();
}

void LTPage_FileBase::setTriggerCount(int count)
{
	wxString str;
	str.Printf(wxT("%d"), count);
	numTriggersText->SetLabel(str);
}