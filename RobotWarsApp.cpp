/***************************************************************
 * Name:      RobotWarsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Velasco (gvela024@fiu.edu)
 * Created:   2014-04-10
 * Copyright: Gabriel Velasco (NA)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "RobotWarsApp.h"

//(*AppHeaders
#include "RobotWarsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(RobotWarsApp);

bool RobotWarsApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	RobotWarsFrame* Frame = new RobotWarsFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
