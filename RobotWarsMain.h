/***************************************************************
 * Name:      RobotWarsMain.h
 * Purpose:   Defines Application Frame
 * Author:    Gabriel Velasco (gvela024@fiu.edu)
 * Created:   2014-04-10
 * Copyright: Gabriel Velasco (NA)
 * License:
 **************************************************************/

#ifndef ROBOTWARSMAIN_H
#define ROBOTWARSMAIN_H

//(*Headers(RobotWarsFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "Arena.h"
#include "tinyxml2.h"

class RobotWarsFrame: public wxFrame
{
    public:

        RobotWarsFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~RobotWarsFrame();

    private:

        //(*Handlers(RobotWarsFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonStartClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(RobotWarsFrame)
        static const long ID_PANEL2;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON1;
        static const long ID_PANEL3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(RobotWarsFrame)
        wxTextCtrl* TextCtrl_prcntRobots;
        wxStaticText* StaticText2;
        wxTextCtrl* TextCtrl_obstacles;
        wxStaticText* StaticText6;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxTextCtrl* TextCtrl_numOfCycles;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxButton* ButtonStart;
        wxPanel* PanelArena;
        wxPanel* PanelUserOptions;
        wxStaticText* StaticText4;
        //*)

        Arena* arena;

        wxTimer refreshTimer;
        void OnTimer(wxTimerEvent& event);
        static const long REFRESH_TIMER_ID;

        void DrawBoard();

        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* robotsElement;
        tinyxml2::XMLElement* obsticleElement;

        DECLARE_EVENT_TABLE()
};

#endif // ROBOTWARSMAIN_H
