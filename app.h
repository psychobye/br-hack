#pragma once

enum eAppInit
{
	APP_INIT_OFFSETS,
	APP_INIT_RW,
	APP_INIT_GUI
};

class CApp
{
public:
	static void Initialise(eAppInit init_type);
	static void Render();
	static void Render2dStuff();
	static void Process();
	static bool OnTouchEvent(int action, int pointer, int x, int y);
	
};
