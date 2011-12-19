#ifndef MAIN_H_
#define MAIN_H_

#include "wx/wx.h"
#include "MainFrame.h"

class MainApp: public wxApp
{
    virtual bool OnInit();
    
    MainFrame * Main;
};

DECLARE_APP(MainApp)

#endif
