#include "LTPage_FileBase.h"

LTPage_FileBase::LTPage_FileBase(wxNotebook *parent, FileType type, wxString dir, wxString filename)
	: wxPanel(parent)
{
	this->type=type;
	this->directory=dir;
	this->filename=filename;

	areaSizer = new wxBoxSizer(wxVERTICAL);

	closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"));
	reloadButton = new wxButton(this, wxID_CANCEL, wxT("Reload"));

	areaSizer->AddSpacer(15);
	areaSizer->Add(closeButton, 0, wxALIGN_BOTTOM | wxALIGN_LEFT);
	areaSizer->Add(reloadButton);

	SetSizer(areaSizer);

	Connect(closeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_FileBase::onClose));
	Connect(reloadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_FileBase::onReload));
}

void LTPage_FileBase::onClose(wxCommandEvent& event)
{
	wxNotebook *parent=(wxNotebook *)GetParent();
	printf("%d\n", parent->GetSelection());
	parent->DeletePage(parent->GetSelection());
}

void LTPage_FileBase::onReload(wxCommandEvent& event)
{
	read();
}
