#include "LTDialog_About.h"

LTDialog_About::LTDialog_About(wxWindow *parent)
  : wxDialog(parent, -1, wxT("About LuaTrig"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT | wxSTAY_ON_TOP)
{
	sizer = new wxBoxSizer(wxVERTICAL);
	widthSizer = new wxBoxSizer(wxHORIZONTAL);

	title1 = new wxStaticText(this, wxID_ANY, wxT("LuaTrig"));
	title2 = new wxStaticText(this, wxID_ANY, wxT("Created by Andy \"Impeached\" Joslin"));
	title3 = new wxStaticText(this, wxID_ANY, wxT("December 2011"));
	ref = new wxStaticText(this, wxID_ANY, wxT("Based on sources from:"));
	aoktsLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT("AoK Trigger Studio, created by DiGiT"), wxT("http://sourceforge.net/projects/aokts/"));
	tseLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT("Trigger Script Editor, created by Jatayu"), wxT("http://aok.heavengames.com/blacksmith/showfile.php?fileid=10278"));

	doneButton = new wxButton(this, wxID_OK, wxT("OK"));
	
	widthSizer->AddSpacer(285); //285 width

	sizer->AddSpacer(15);
	sizer->Add(widthSizer);
	sizer->Add(title1, 0, wxALIGN_CENTER);
	sizer->Add(title2, 0, wxALIGN_CENTER);
	sizer->Add(title3, 0, wxALIGN_CENTER);
	sizer->AddSpacer(10);
	sizer->Add(ref, 0, wxALIGN_CENTER);
	sizer->Add(aoktsLink, 0, wxALIGN_CENTER);
	sizer->Add(tseLink, 0, wxALIGN_CENTER);
	sizer->AddSpacer(15);
	sizer->Add(doneButton, 1, wxALIGN_CENTER | wxALIGN_BOTTOM);
	sizer->AddSpacer(5);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_About::onDone));

	SetSizerAndFit(sizer);
} 

void LTDialog_About::onDone(wxCommandEvent &event)
{
	EndModal(wxID_OK);
}