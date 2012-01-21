#ifndef MAIN_H_
#define MAIN_H_

#include "wx/wx.h"
#include "wx/fileconf.h"

class LTFrame; //fwd so we don't have to include it here

class LuaTrigMain: public wxApp
{
private:
    virtual bool OnInit();
    
    LTFrame * MainFrame;

    static wxFileConfig *appConfig;
   
public:
    static wxString configRead(wxString key);
    static void configWrite(wxString key, wxString value);
};

DECLARE_APP(LuaTrigMain)

#endif

