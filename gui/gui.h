#pragma once

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_internal.h"

class CGUI
{
public:
	static void Initialise();
	static void Render();
	static void Render2dStuff();
	static bool OnTouchEvent(int action, int pointer, int x, int y);
	
	static ImFont* GetFont(const char* font_name = NULL);
	
	static void PushIcons();
	static void PushFont(const char* font_name);
	static void PopFont();
	
	static bool Button(const char* label, ImVec2 size = ImVec2(0, 0), bool* p_toggle = NULL, bool lighting = false, ImGuiCol_ col = ImGuiCol_FrameBg);
	static void CheckSpace();
	
	static char* buffGUI;
private:
	static ImFont* m_pDefaultFont;
	static ImFont* m_pTitleFont;
	static ImFont* m_pTitleLinkFont;
	static ImFont* m_pButtonsFont;
	
	static ImFont* m_pDefaultIconsFont;
	
	static float m_fDefaultFontSize;
	static float m_fTitleFontSize;
	static float m_fTitleLinkFontSize;
	static float m_fButtonsFontSize;
};
