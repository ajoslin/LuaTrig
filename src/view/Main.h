#ifndef MAIN_H_
#define MAIN_H_

#include "wx/wx.h"
#include "LTFrame.h"

class LTrig: public wxApp
{
    virtual bool OnInit();
    
    LTFrame * MainFrame;
};

DECLARE_APP(LTrig)

#endif
