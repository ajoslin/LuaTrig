#include "LTPage_File.h"
#include "LTFrame.h"
#include "../defines.h"
#include <stdio.h>

LTPage_File::LTPage_File(wxWindow *parent)
	: wxPanel(parent)
{
	masterSizer = new wxBoxSizer(wxVERTICAL);
	textSizer = new wxBoxSizer(wxHORIZONTAL);

	closeBtn = new wxButton(this, wxID_ANY, wxT(STR_CLOSE));
	reloadBtn = new wxButton(this, wxID_ANY, wxT(STR_RELOAD));
	openBtn = new wxButton(this, wxID_ANY, wxT(STR_OPEN));
	openBtn->Show(false);

	textTitle = new wxStaticText(this, wxID_ANY, wxEmptyString);
	textContent = new wxStaticText(this, wxID_ANY, wxEmptyString);

	masterSizer->AddSpacer(5);
	masterSizer->Add(closeBtn);
	masterSizer->Add(reloadBtn);
	masterSizer->Add(openBtn);
	masterSizer->AddSpacer(10);
	textSizer->Add(textTitle);
	textSizer->AddSpacer(10);
	textSizer->Add(textContent);
	masterSizer->Add(textSizer);
	masterSizer->AddSpacer(10);

	SetSizer(masterSizer);

	Connect(closeBtn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_File::onCloseButtonPressed));
	Connect(reloadBtn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LTPage_File::onReloadButtonPressed));
}

void LTPage_File::onCloseButtonPressed(wxCommandEvent& event)
{
	onCloseFile();
}

void LTPage_File::onReloadButtonPressed(wxCommandEvent& event)
{
	read();
	masterSizer->Layout();
}

void LTPage_File::onOpenFile(wxFileName fname)
{
	LTFrame::instance()->openFile(fname);
}

void LTPage_File::onCloseFile()
{
	wxFileName fname(wxString(currentFile->getPath()));
	LTFrame::instance()->closeFile(fname);
}

void LTPage_File::setLabelTriggers(int trigCount)
{
	textTitle->SetLabel(wxT(STR_FILE_TRIGCNT));
	textContent->SetLabel(wxString::Format(wxT("%i"), trigCount));
}

void LTPage_File::setLabelError(wxString err)
{
	textTitle->SetLabel(wxT(STR_ERROR));
	textContent->SetLabel(err);
}

wxFileName LTPage_File::getCurrentFileName()
{
	wxFileName fn(wxString(currentFile->getPath()));
	return fn;
}
