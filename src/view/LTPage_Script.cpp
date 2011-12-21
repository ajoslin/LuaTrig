#include "LTPage_Script.h"
#include "LTFrame.h"

LTPage_Script::LTPage_Script(LTFrame *frame, wxNotebook *parent, wxString dir, wxString filename)
	: LTPage_FileBase(parent, FTYPE_Scenario, dir, filename)
{
}

void LTPage_Script::write(wxString path)
{
	
}

void LTPage_Script::read()
{
}