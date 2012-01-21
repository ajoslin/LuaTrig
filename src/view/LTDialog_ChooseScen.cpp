#include "LTDialog_ChooseScen.h"
#include "../defines.h"

LTDialog_ChooseScen::LTDialog_ChooseScen(wxWindow *parent, wxString choices[], int nChoices)
  : wxDialog(parent, -1, wxT(STR_CHSSCN_TITLE), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT | wxSTAY_ON_TOP)
{
	mainSizer = new wxBoxSizer(wxVERTICAL);
	buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	radioBox = new wxRadioBox(this, wxID_ANY, wxT(STR_CHSSCN_RADIO), wxDefaultPosition, wxDefaultSize, nChoices, choices, 0, wxRA_SPECIFY_ROWS);

	mainSizer->AddSpacer(10);
	mainSizer->Add(radioBox, 1, wxALIGN_CENTER);

	okButton = new wxButton(this, wxID_OK, wxT(STR_OK));
	cancelButton = new wxButton(this, wxID_CANCEL, wxT(STR_CANCEL));

	buttonSizer->Add(okButton);
	buttonSizer->Add(cancelButton);

	mainSizer->AddSpacer(15);
	mainSizer->Add(buttonSizer, 1, wxALIGN_BOTTOM | wxALIGN_CENTER);
	mainSizer->AddSpacer(5);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_ChooseScen::onDone));
	Connect(wxID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_ChooseScen::onDone));
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LTDialog_ChooseScen::onExit));

	mainSizer->SetMinSize(wxSize(300, 100));
	SetSizerAndFit(mainSizer);
	SetDefaultItem(okButton);
	Center();
} 

void LTDialog_ChooseScen::onDone(wxCommandEvent &event)
{
	if (event.GetId()==wxID_OK)
		EndModal(radioBox->GetSelection());
	else
		EndModal(wxNOT_FOUND);
}

void LTDialog_ChooseScen::onExit(wxCloseEvent &event)
{
	EndModal(wxNOT_FOUND);
}
