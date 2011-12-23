#include "LTDialog_About.h"

LTDialog_About::LTDialog_About(wxWindow *parent)
  : wxDialog(parent, -1, wxT("About LuaTrig"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT | wxSTAY_ON_TOP)
{
	mainSizer = new wxBoxSizer(wxVERTICAL);

	title1 = new wxStaticText(this, wxID_ANY, wxT("LuaTrig"));
	title2 = new wxStaticText(this, wxID_ANY, wxT("Created by Andy \"Impeached\" Joslin"));
	title3 = new wxStaticText(this, wxID_ANY, wxT("December 2011"));
	ref = new wxStaticText(this, wxID_ANY, wxT("Based on sources from:"));
	aoktsLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT("AoK Trigger Studio, created by DiGiT"), wxT("http://sourceforge.net/projects/aokts/"));
	tseLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT("Trigger Script Editor, created by Jatayu"), wxT("http://aok.heavengames.com/blacksmith/showfile.php?fileid=10278"));

	doneButton = new wxButton(this, wxID_OK, wxT("OK"));

	mainSizer->AddSpacer(15);
	mainSizer->Add(title1, 0, wxALIGN_CENTER);
	mainSizer->Add(title2, 0, wxALIGN_CENTER);
	mainSizer->Add(title3, 0, wxALIGN_CENTER);
	mainSizer->AddSpacer(10);
	mainSizer->Add(ref, 0, wxALIGN_CENTER);
	mainSizer->Add(aoktsLink, 0, wxALIGN_CENTER);
	mainSizer->Add(tseLink, 0, wxALIGN_CENTER);
	mainSizer->AddSpacer(15);
	mainSizer->Add(doneButton, 1, wxALIGN_CENTER | wxALIGN_BOTTOM);
	mainSizer->AddSpacer(5);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_About::onDone));

	mainSizer->SetMinSize(wxSize(285, 1)); //only care about width
	SetSizerAndFit(mainSizer);
	SetDefaultItem(doneButton);
} 

void LTDialog_About::onDone(wxCommandEvent &event)
{
	EndModal(wxID_OK);
}