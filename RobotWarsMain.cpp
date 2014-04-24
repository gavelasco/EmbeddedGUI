/***************************************************************
 * Name:      RobotWarsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Gabriel Velasco (gvela024@fiu.edu)
 * Created:   2014-04-10
 * Copyright: Gabriel Velasco (NA)
 * License:
 **************************************************************/

 /*
 TODO
   Initialize lifetime and mate time with random variables.
 */

#include "wx_pch.h"
#include "RobotWarsMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(RobotWarsFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/dcbuffer.h>

#include "PlayerRobot.h"
#include "CustomTypes.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(RobotWarsFrame)
const long RobotWarsFrame::ID_PANEL2 = wxNewId();
const long RobotWarsFrame::ID_STATICTEXT1 = wxNewId();
const long RobotWarsFrame::ID_TEXTCTRL1 = wxNewId();
const long RobotWarsFrame::ID_STATICTEXT2 = wxNewId();
const long RobotWarsFrame::ID_TEXTCTRL2 = wxNewId();
const long RobotWarsFrame::ID_STATICTEXT3 = wxNewId();
const long RobotWarsFrame::ID_STATICTEXT4 = wxNewId();
const long RobotWarsFrame::ID_STATICTEXT5 = wxNewId();
const long RobotWarsFrame::ID_STATICTEXT6 = wxNewId();
const long RobotWarsFrame::ID_STATICTEXT7 = wxNewId();
const long RobotWarsFrame::ID_TEXTCTRL3 = wxNewId();
const long RobotWarsFrame::ID_BUTTON1 = wxNewId();
const long RobotWarsFrame::ID_PANEL3 = wxNewId();
const long RobotWarsFrame::ID_PANEL1 = wxNewId();
const long RobotWarsFrame::idMenuQuit = wxNewId();
const long RobotWarsFrame::idMenuAbout = wxNewId();
const long RobotWarsFrame::ID_STATUSBAR1 = wxNewId();
//*)

const long RobotWarsFrame::REFRESH_TIMER_ID = wxNewId();

BEGIN_EVENT_TABLE(RobotWarsFrame,wxFrame)
    //(*EventTable(RobotWarsFrame)
    //*)
    EVT_TIMER(REFRESH_TIMER_ID, RobotWarsFrame::OnTimer)
END_EVENT_TABLE()

RobotWarsFrame::RobotWarsFrame(wxWindow* parent,wxWindowID id) : refreshTimer(this, REFRESH_TIMER_ID)
{
    //(*Initialize(RobotWarsFrame)
    wxFlexGridSizer* FlexGridSizer4;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(1, 2, 0, 0);
    PanelArena = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxSize(900,630), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    PanelArena->SetMinSize(wxSize(900,630));
    PanelArena->SetMaxSize(wxSize(900,630));
    FlexGridSizer2->Add(PanelArena, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelUserOptions = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer3 = new wxFlexGridSizer(10, 1, 0, 0);
    FlexGridSizer4 = new wxFlexGridSizer(5, 2, 0, 0);
    StaticText1 = new wxStaticText(PanelUserOptions, ID_STATICTEXT1, _("Percent Robots"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_prcntRobots = new wxTextCtrl(PanelUserOptions, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer4->Add(TextCtrl_prcntRobots, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(PanelUserOptions, ID_STATICTEXT2, _("Percent Obstacles"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_obstacles = new wxTextCtrl(PanelUserOptions, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer4->Add(TextCtrl_obstacles, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(PanelUserOptions, ID_STATICTEXT3, _("Percent Transport Holes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(PanelUserOptions, ID_STATICTEXT4, _("NOT IMPLEMENTED"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText4->SetForegroundColour(wxColour(255,0,0));
    FlexGridSizer4->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(PanelUserOptions, ID_STATICTEXT5, _("Percent Black Holes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer4->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(PanelUserOptions, ID_STATICTEXT6, _("NOT IMPLEMENTED"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText6->SetForegroundColour(wxColour(255,0,0));
    FlexGridSizer4->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(PanelUserOptions, ID_STATICTEXT7, _("Number of Cycles"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer4->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_numOfCycles = new wxTextCtrl(PanelUserOptions, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer4->Add(TextCtrl_numOfCycles, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonStart = new wxButton(PanelUserOptions, ID_BUTTON1, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer3->Add(ButtonStart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelUserOptions->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(PanelUserOptions);
    FlexGridSizer3->SetSizeHints(PanelUserOptions);
    FlexGridSizer2->Add(PanelUserOptions, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1);
    FlexGridSizer2->SetSizeHints(Panel1);
    FlexGridSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RobotWarsFrame::OnButtonStartClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&RobotWarsFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&RobotWarsFrame::OnAbout);
    //*)

   wxPaintDC dc(PanelArena);
   dc.Clear();

    tinyxml2::XMLError error = doc.LoadFile("defaults.xml");
    if (error)
    {
        wxString errorMessage;
        errorMessage.Printf(wxT("File Load Error: %d"), error);
        wxMessageBox(errorMessage);
        exit(EXIT_FAILURE);
    }

    robotsElement = doc.FirstChildElement("UserInput")->FirstChildElement("Robots");
    if (NULL == robotsElement)
    {
        wxString errorMessage;
        errorMessage.Printf(wxT("Couldn't get Robots Element"));
        wxMessageBox(errorMessage);
        exit(EXIT_FAILURE);
    }

    const char* text = robotsElement->FirstChildElement("percent")->GetText();
    wxString value_string = wxString::FromUTF8(text);
    TextCtrl_prcntRobots->SetValue(value_string);

    obsticleElement = doc.FirstChildElement("UserInput")->FirstChildElement("Obsticles");
    if (NULL == obsticleElement)
    {
        wxString errorMessage;
        errorMessage.Printf(wxT("Couldn't get Obsticles Element"));
        wxMessageBox(errorMessage);
        exit(EXIT_FAILURE);
    }

    text = obsticleElement->FirstChildElement("rock")->GetText();
    value_string = wxString::FromUTF8(text);
    TextCtrl_obstacles->SetValue(value_string);

    text = doc.FirstChildElement("UserInput")->FirstChildElement("Lifetime")->FirstChildElement("cycles")->GetText();
    value_string = wxString::FromUTF8(text);
    TextCtrl_numOfCycles->SetValue(value_string);
}

RobotWarsFrame::~RobotWarsFrame()
{
    //(*Destroy(RobotWarsFrame)
    //*)
}

void RobotWarsFrame::OnQuit(wxCommandEvent& event)
{
    delete arena;
    Close();
}

void RobotWarsFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void RobotWarsFrame::OnTimer(wxTimerEvent& event)
{
   Player_Type winner = arena->getWinningTeam();
   if (0 >= numberOfCycles)
   {
      wxMessageBox(wxT("Draw!!"));
      refreshTimer.Stop();

      wxPaintDC dc(PanelArena);
      dc.Clear();
      delete arena;
   }
   if (player_max == winner)
   {
      arena->animate();
      RobotWarsFrame::DrawBoard();
   }
   else
   {
      wxString winnerString;
      if (player_robot_blue_1 == winner) winnerString.Printf(wxT("Blue Team!"));
      if (player_robot_red_1 == winner) winnerString.Printf(wxT("Red Team!"));
      if (player_robot_green_1 == winner) winnerString.Printf(wxT("Green Team!"));
      if (player_robot_yellow_1 == winner) winnerString.Printf(wxT("Yellow Team!"));
      wxMessageBox(winnerString , wxT("Winner!!"), wxOK, this);

      refreshTimer.Stop();

      wxPaintDC dc(PanelArena);
      dc.Clear();
      delete arena;
   }

   numberOfCycles--;
}

void RobotWarsFrame::OnButtonStartClick(wxCommandEvent& event)
{
   wxString temp;
   temp = TextCtrl_prcntRobots->GetValue();
   short int percentRobot = wxAtoi(temp);

   temp = TextCtrl_obstacles->GetValue();
   short int percentObstacle = wxAtoi(temp);
   short int percentBlackHole = 0;
   short int percentTransportHole = 0;

   temp = TextCtrl_numOfCycles->GetValue();
   numberOfCycles = wxAtoi(temp);

   arena = new Arena(TOTAL_ROWS, TOTAL_COLUMNS, percentRobot, percentObstacle, percentBlackHole, percentTransportHole);
   RobotWarsFrame::DrawBoard();
   refreshTimer.Start(1000, wxTIMER_CONTINUOUS);
}

void RobotWarsFrame::DrawBoard()
{
    wxPaintDC dc(PanelArena);

    wxBitmap ground(wxT("Ground.bmp"));
    if(!ground.Ok())
    {
        wxMessageBox(wxT("Failed to load bitmap: ground"));
        Close();
    }

    wxBitmap obstacle(wxT("Obstacle.bmp"));
    if(!ground.Ok())
    {
        wxMessageBox(wxT("Failed to load bitmap: obstacle"));
        Close();
    }

    wxBitmap robot1_blue(wxT("RL1Blue.bmp"));
    if(!robot1_blue.Ok())
    {
        wxMessageBox(wxT("Failed to load bitmap: rl1blue"));
        Close();
    }

    wxBitmap robot1_red(wxT("RL1Red.bmp"));
    if(!robot1_blue.Ok())
    {
        wxMessageBox(wxT("Failed to load bitmap: rl1red"));
        Close();
    }

    wxBitmap robot1_yellow(wxT("RL1Yellow.bmp"));
    if(!robot1_blue.Ok())
    {
        wxMessageBox(wxT("Failed to load bitmap: rl1yellow"));
        Close();
    }

    wxBitmap robot1_green(wxT("RL1Green.bmp"));
    if(!robot1_blue.Ok())
    {
        wxMessageBox(wxT("Failed to load bitmap: rl1green"));
        Close();
    }

    if (!dc.CanDrawBitmap())
    {
        wxMessageBox(wxT("ERROR"), wxT("Cannot draw bitmaps on panel"),wxICON_ERROR);
        Close();
    }

    for (short int row = 0; row < TOTAL_ROWS; row++)
    {
        for (short int column = 0; column < TOTAL_COLUMNS; column++)
        {

            switch(arena->content[row][column])
            {
                case player_ground:
                    dc.DrawBitmap(ground, wxCoord(column * BITMAP_DIMENSIONS), wxCoord(row * BITMAP_DIMENSIONS), false);
                    break;

                case player_obstacle:
                    dc.DrawBitmap(obstacle, wxCoord(column * BITMAP_DIMENSIONS), wxCoord(row * BITMAP_DIMENSIONS), false);
                    break;

                case player_robot_blue_1:
                    dc.DrawBitmap(robot1_blue, wxCoord(column * BITMAP_DIMENSIONS), wxCoord(row * BITMAP_DIMENSIONS), false);
                    break;

                case player_robot_red_1:
                    dc.DrawBitmap(robot1_red, wxCoord(column * BITMAP_DIMENSIONS), wxCoord(row * BITMAP_DIMENSIONS), false);
                    break;

                case player_robot_yellow_1:
                    dc.DrawBitmap(robot1_yellow, wxCoord(column * BITMAP_DIMENSIONS), wxCoord(row * BITMAP_DIMENSIONS), false);
                    break;

                case player_robot_green_1:
                    dc.DrawBitmap(robot1_green, wxCoord(column * BITMAP_DIMENSIONS), wxCoord(row * BITMAP_DIMENSIONS), false);
                    break;
            }

        }
    }
}
