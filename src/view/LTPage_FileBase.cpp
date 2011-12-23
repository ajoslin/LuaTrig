#include "LTPage_FileBase.h"
#include "LTFrame.h"

LTPage_FileBase::LTPage_FileBase(LTFrame *frame, wxNotebook *parent, int type, wxFileName *fname)
	: wxPanel(parent)
{
	this->file = fname;
	this->frame=frame;
	this->type=type;

	areaSizer = new wxBoxSizer(wxVERTICAL);
	infoSizer = new wxBoxSizer(wxHORIZONTAL);

	closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"));
	reloadButton = new wxButton(this, wxID_ANY, wxT("Reload"));

	wxString stype = type==FTYPE_Scenario ? wxT("Scenario") : wxT("Script");
	numTriggersLabelText = new wxStaticText(this, wxID_ANY, stype + wxT(" Trigger Count: "));
	numTriggersText = new wxStaticText(this, wxID_ANY, wxT(""));

	infoSizer->Add(numTriggersLabelText, 1, wxALIGN_CENTER_VERTICAL);
	infoSizer->Add(numTriggersText, 1, wxALIGN_CENTER_VERTICAL);

	areaSizer->AddSpacer(15);
	areaSizer->Add(closeButton);
	areaSizer->Add(reloadButton);
	areaSizer->AddSpacer(10);
	areaSizer->Add(infoSizer);

	SetSizer(areaSizer);

	Connect(closeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_FileBase::onClose));
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