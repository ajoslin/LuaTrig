#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	//Get config settings (if they exist)
	Config = new wxFileConfig("LuaTrig", wxEmptyString, "luatrigconfig.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Read("DefaultScenarioDir", &ScenarioDir, wxT(""));
	Config->Read("DefaultScriptsDir", &ScriptsDir, wxT(""));

	//Create all the tabs' pages
	Page_Settings = new LTPage_Settings(this);

	//Menu Bar
	MenuBar_Main = new wxMenuBar();

	SubMenu_File = new wxMenu();
	SubMenu_File->Append(Menu_About, "&About");
	SubMenu_File->Append(Menu_Exit, "E&xit");

	MenuBar_Main->Append(SubMenu_File, "&File");
	this->SetMenuBar(MenuBar_Main);

	//Tab Bar
	TabBar_Main = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	TabBar_Main->AddPage(Tab_Settings, "Settings");
	TabBar_Main->AddPage(Tab_Import, "Trigger Importer/Exporter");
	TabBar_Main->AddPage(Tab_TriggerGen, "Trigger Generator");
	TabBar_Main->SetSelection(1);

	//Connect menu events
	Connect(wxEVT_CLOSE_WINDOW, wcCloseEventHandler(MainFrame::OnExit));
	Connect(Menu_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(Menu_Exit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnExit));

	ScenFile = "";
	ScriptFile = "";
}


