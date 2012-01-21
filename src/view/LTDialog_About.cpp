#include "LTDialog_About.h"
#include "../defines.h"

LTDialog_About::LTDialog_About(wxWindow *parent)
  : wxDialog(parent, -1, wxT(STR_ABT_TITLE), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT | wxSTAY_ON_TOP)
{
	mainSizer = new wxBoxSizer(wxVERTICAL);

	title1 = new wxStaticText(this, wxID_ANY, wxT(STR_LUATRIG));
	title2 = new wxStaticText(this, wxID_ANY, wxT(STR_ABT_ANDY));
	title3 = new wxStaticText(this, wxID_ANY, wxT(STR_ABT_DATE));
	title4 = new wxHyperlinkCtrl(this, wxID_ANY, wxT("https://github.com/andy-joslin/LuaTrig/"), wxT("https://github.com/andy-joslin/LuaTrig/"));
	ref = new wxStaticText(this, wxID_ANY, wxT(STR_ABT_REFTITLE));
	aoktsLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT(STR_ABT_AOKTS), wxT(STR_ABT_AOKTS_LINK));
	tseLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT(STR_ABT_TSE), wxT(STR_ABT_TSE_LINK));

	doneButton = new wxButton(this, wxID_OK, wxT(STR_OK));

	mainSizer->AddSpacer(15);
	mainSizer->Add(title1, 0, wxALIGN_CENTER);
	mainSizer->Add(title2, 0, wxALIGN_CENTER);
	mainSizer->Add(title3, 0, wxALIGN_CENTER);
	mainSizer->Add(title4, 0, wxALIGN_CENTER);
	mainSizer->AddSpacer(20);
	mainSizer->Add(ref, 0, wxALIGN_CENTER);
	mainSizer->Add(aoktsLink, 0, wxALIGN_CENTER);
	mainSizer->Add(tseLink, 0, wxALIGN_CENTER);
	mainSizer->AddSpacer(15);
	mainSizer->Add(doneButton, 1, wxALIGN_CENTER | wxALIGN_BOTTOM);
	mainSizer->AddSpacer(5);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTDialog_About::onDone));

	mainSizer->SetMinSize(wxSize(300, 200));
	SetSizerAndFit(mainSizer);
	SetDefaultItem(doneButton);
	Center();
} 

void LTDialog_About::onDone(wxCommandEvent &event)
{
	EndModal(wxID_OK);
}
