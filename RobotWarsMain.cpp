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
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(1, 2, 0, 0);
    PanelArena = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxSize(900,630), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    PanelArena->SetMinSize(wxSize(900,630));
    PanelArena->SetMaxSize(wxSize(900,630));
    FlexGridSizer2->Add(PanelArena, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelUserOptions = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer3 = new wxFlexGridSizer(10, 1, 0, 0);
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

    short int percentRobot = 20;
    short int percentObstacle = 5;
    short int percentBlackHole = 0;
    short int percentTransportHole = 0;

    arena = new Arena(TOTAL_ROWS, TOTAL_COLUMNS, percentRobot, percentObstacle, percentBlackHole, percentTransportHole);
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
   if(player_max == winner)
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
      Close();
   }

}

void RobotWarsFrame::OnButtonStartClick(wxCommandEvent& event)
{
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
