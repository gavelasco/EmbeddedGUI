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
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "Arena.h"

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
        static const long ID_BUTTON1;
        static const long ID_PANEL3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(RobotWarsFrame)
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        wxButton* ButtonStart;
        wxPanel* PanelArena;
        wxPanel* PanelUserOptions;
        //*)

        Arena* arena;

        wxTimer refreshTimer;
        void OnTimer(wxTimerEvent& event);
        static const long REFRESH_TIMER_ID;

        void DrawBoard();

        DECLARE_EVENT_TABLE()
};

#endif // ROBOTWARSMAIN_H
