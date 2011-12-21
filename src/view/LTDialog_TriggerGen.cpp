#include "LTDialog_TriggerGen.h"

LTDialog_TriggerGen::LTDialog_TriggerGen(wxWindow *parent)
	: wxDialog(parent, -1, wxT("Generate Triggers"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT | wxSTAY_ON_TOP)
{

	sizer = new wxBoxSizer(wxVERTICAL);
	widthSizer = new wxBoxSizer(wxHORIZONTAL);

	title = new wxStaticText(this, wxID_ANY, wxT("Coming soon!"));
	okButton = new wxButton(this, wxID_OK, wxT("OK"));

	widthSizer->AddSpacer(150);
	sizer->AddSpacer(15);
	sizer->Add(widthSizer);
	sizer->Add(title, 0, wxALIGN_CENTER);
	sizer->AddSpacer(10);
	sizer->Add(okButton, 0, wxALIGN_CENTER | wxALIGN_BOTTOM);
	sizer->AddSpacer(5);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_TriggerGen::onDone));
	SetSizerAndFit(sizer);
};

void LTDialog_TriggerGen::onDone(wxCommandEvent &event)
{
	EndModal(wxID_OK);
}