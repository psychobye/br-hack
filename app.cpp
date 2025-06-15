#include "app.h"
#include "plugin.h"

#include "game/rw/rw.h"
#include "gui/gui.h"

void CApp::Initialise(eAppInit init_type)
{
	if(init_type == eAppInit::APP_INIT_OFFSETS)
	{
		COffset::Initialise();
	}
	if(init_type == eAppInit::APP_INIT_RW)
	{
		rw::Initialise();
	}
	if(init_type == eAppInit::APP_INIT_GUI)
	{
		CGUI::Initialise();
	}
}

void CApp::Render()
{
	CGUI::Render();
}

void CApp::Render2dStuff()
{
	CGUI::Render2dStuff();
}

void CApp::Process()
{
	
}

bool CApp::OnTouchEvent(int action, int pointer, int x, int y)
{
	if(!CGUI::OnTouchEvent(action, pointer, x, y)) {
		return false;
	}
	return true;
}
