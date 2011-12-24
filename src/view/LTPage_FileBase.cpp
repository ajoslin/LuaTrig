#include "LTPage_FileBase.h"
#include "LTFrame.h"
#include "../defines.h"

LTPage_FileBase::LTPage_FileBase(LTFrame *frame, wxNotebook *parent, int type, wxFileName *fname)
	: wxPanel(parent)
{
	this->file = fname;
	this->frame=frame;
	this->type=type;

	areaSizer = new wxBoxSizer(wxVERTICAL);
	infoSizer = new wxBoxSizer(wxHORIZONTAL);

	closeButton = new wxButton(this, wxID_CANCEL, wxT(STR_CLOSE));
	reloadButton = new wxButton(this, wxID_ANY, wxT(STR_RELOAD));

	wxString stype = type==FTYPE_Scenario ? wxT(STR_SCENARIO) : wxT(STR_SCRIPT);
	numTriggersLabelText = new wxStaticText(this, wxID_ANY, stype+wxT(" ")+wxT(STR_FILE_TRIGCNT)+wxT(" "));
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