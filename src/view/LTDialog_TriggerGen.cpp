#include "LTDialog_TriggerGen.h"

LTDialog_TriggerGen::LTDialog_TriggerGen(wxWindow *parent)
	: wxDialog(parent, -1, wxT("Generate Triggers"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT | wxSTAY_ON_TOP)
{

	mainSizer = new wxBoxSizer(wxVERTICAL);

	title = new wxStaticText(this, wxID_ANY, wxT("Coming soon!"));
	okButton = new wxButton(this, wxID_OK, wxT("OK"));

	mainSizer->AddSpacer(15);
	mainSizer->Add(title, 0, wxALIGN_CENTER);
	mainSizer->AddSpacer(10);
	mainSizer->Add(okButton, 0, wxALIGN_CENTER | wxALIGN_BOTTOM);
	mainSizer->AddSpacer(5);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_TriggerGen::onDone));

	mainSizer->SetMinSize(wxSize(150, 1)); //only care about width
	SetSizerAndFit(mainSizer);
	SetDefaultItem(okButton);
};

void LTDialog_TriggerGen::onDone(wxCommandEvent &event)
{
	EndModal(wxID_OK);
}