#ifndef MAIN_H_
#define MAIN_H_

#include "wx/wx.h"
#include "LTFrame.h"

class LTMain: public wxApp
{
    virtual bool OnInit();
    
    LTFrame * LTMain;
};

DECLARE_APP(LTMain)

#endif
