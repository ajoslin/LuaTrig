#include "LTDialog_About.h"

LTDialog_About::LTDialog_About(wxWindow *parent)
  : wxDialog(parent, -1, wxT("About LuaTrig"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT)
{
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText *title = new wxStaticText(this, wxID_ANY, wxT("LuaTrig\nCreated by Andy \"Impeached\" Joslin, December 2011"));
	wxStaticText *ref = new wxStaticText(this, wxID_ANY, wxT("Based on sources from:"));
	wxHyperlinkCtrl *aoktsLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT("-  AoK Trigger Studio, created by DiGiT: "), wxT("http://sourceforge.net/projects/aokts/"));
	wxHyperlinkCtrl *tseLink = new wxHyperlinkCtrl(this, wxID_ANY, wxT("- Trigger Script Editor, created by Jatayu: "), wxT("http://aok.heavengames.com/blacksmith/showfile.php?fileid=10278"));

	wxButton *doneButton = new wxButton(this, wxID_ANY, wxT("OK"));
	
	sizer->AddSpacer(15);
	sizer->Add(title);
	sizer->AddSpacer(10);
	sizer->Add(ref);
	sizer->Add(aoktsLink);
	sizer->Add(tseLink);
	sizer->AddSpacer(15);
	sizer->Add(doneButton, 1, wxALIGN_CENTER | wxALIGN_BOTTOM);
	sizer->AddSpacer(5);

	SetSizerAndFit(sizer);

}
