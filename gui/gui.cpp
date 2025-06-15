#include "gui.h"
#include "xorstr.h"

#include "game/rw/rw.h"

#include "fonts/Lilita.h"
#include "fonts/BoxIcons.h"
#include "fonts/LozungCaps.h"

ImFont* CGUI::m_pDefaultFont;
ImFont* CGUI::m_pTitleFont;
ImFont* CGUI::m_pTitleLinkFont;
ImFont* CGUI::m_pButtonsFont;

ImFont* CGUI::m_pDefaultIconsFont;

float CGUI::m_fDefaultFontSize;
float CGUI::m_fTitleFontSize;
float CGUI::m_fTitleLinkFontSize;
float CGUI::m_fButtonsFontSize;

ImWchar ranges[] = { 0xe900, 0xEF61, 0 };

char* CGUI::buffGUI = new char[4096];

void CGUI::Initialise()
{
	ImGuiIO& io = ImGui::GetIO();
	
	m_fDefaultFontSize = (RsGlobal->maximumHeight / 640.f) * 20.f;
	m_fTitleFontSize = (RsGlobal->maximumHeight / 640.f) * 26.f;
	m_fTitleLinkFontSize = (RsGlobal->maximumHeight / 640.f) * 25.f;
	m_fButtonsFontSize = (RsGlobal->maximumHeight / 640.f) * 22.5f;
	
	m_pDefaultFont = io.Fonts->AddFontFromMemoryTTF(Font::Lilita, sizeof(Font::Lilita), m_fDefaultFontSize, NULL, io.Fonts->GetGlyphRangesCyrillic());
	
	m_pTitleFont = io.Fonts->AddFontFromMemoryTTF(Font::LozungCaps, sizeof(Font::LozungCaps), m_fTitleFontSize, NULL, io.Fonts->GetGlyphRangesCyrillic());
	m_pTitleLinkFont = io.Fonts->AddFontFromMemoryTTF(Font::Lilita, sizeof(Font::Lilita), m_fTitleLinkFontSize, NULL, io.Fonts->GetGlyphRangesCyrillic());
	m_pButtonsFont = io.Fonts->AddFontFromMemoryTTF(Font::Lilita, sizeof(Font::Lilita), m_fButtonsFontSize, NULL, io.Fonts->GetGlyphRangesCyrillic());
	
	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphOffset = ImVec2(0, 4);
	m_pDefaultIconsFont = io.Fonts->AddFontFromMemoryTTF(Font::BoxIcons, sizeof(Font::BoxIcons), m_fDefaultFontSize, &config, ranges);
	
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowRounding = 10.f;
	style.FrameRounding = 10.f;
	style.ChildRounding = 10.f;
   // style.ScrollbarSize = 10.f;
  //  style.ScrollbarRounding = 5.f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    
	style.Colors[ImGuiCol_Text] = ImVec4(0.90, 0.90, 0.90, 1.00);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60, 0.60, 0.60, 1.00);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08, 0.08, 0.08, 1.00);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.10, 0.10, 0.10, 1.00);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08, 0.08, 0.08, 1.00);
    style.Colors[ImGuiCol_Border] = ImVec4(0.70, 0.70, 0.70, 0.40);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00, 0.00, 0.00, 0.00);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.15, 0.15, 0.15, 1.00);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19, 0.19, 0.19, 0.71);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.34, 0.34, 0.34, 0.79);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96, 0.86, 0.42, 0.80);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.96, 0.88, 0.55, 1.00);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.96, 0.88, 0.55, 0.50);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00, 0.80, 0.38, 1.00);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.16, 0.16, 0.16, 1.00);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.96, 0.86, 0.42, 1.00);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.96, 0.88, 0.55, 1.00);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.96, 0.88, 0.55, 1.00);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.96, 0.86, 0.42, 1.00);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.96, 0.86, 0.42, 1.00);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.96, 0.88, 0.55, 1.00);
    style.Colors[ImGuiCol_Button] = ImVec4(0.96, 0.86, 0.42, 1.00);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.96, 0.88, 0.55, 1.00);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.96, 0.886, 0.58, 1.00);
    style.Colors[ImGuiCol_Header] = ImVec4(0.96, 0.86, 0.42, 1.00);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.96, 0.88, 0.55, 0.57);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.96, 0.886, 0.58, 0.89);
    style.Colors[ImGuiCol_Separator] = ImVec4(1.00, 1.00, 1.00, 0.40);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00, 1.00, 1.00, 0.60);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(1.00, 1.00, 1.00, 0.80);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.96, 0.86, 0.42, 1.00);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.96, 0.88, 0.55, 1.00);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.96, 0.886, 0.58, 1.00);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00, 0.69, 0.33, 1.00);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00, 0.74, 0.36, 1.00);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00, 0.69, 0.33, 1.00);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00, 0.80, 0.38, 1.00);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00, 0.69, 0.33, 0.72);
}

#include "plugin/netgame.h"

void CGUI::Render()
{
	CPlayerPool* pool = CNetGame::GetPlayerPool();
	if(pool) {
		CLocalPlayer* player = pool->GetLocalPlayer();
		if(player) {
			CPlayerPed* ped = player->GetPlayerPed();
			if(ped) {
				CVector pos = ped->m_matrix.GetPosition();
				float angle = atan2f(-ped->m_matrix.fx, ped->m_matrix.fy) * (180.f / M_PI);
				if(angle < 0) {
					angle += 360;
				}
				angle = fmod(angle, 360.f);
				char buff[64] = {0};
				sprintf(buff, xorstr("(%.2f) %.2f, %.2f, %.2f"), angle, pos.x, pos.y, pos.z);
				ImVec2 screen_pos;
				screen_pos.x = (RsGlobal->width - ImGui::CalcTextSize(buff).x) / 2.f;
				screen_pos.y = RsGlobal->height - ImGui::GetFontSize();
				screen_pos.y -= 2.f;
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x - 2.f, screen_pos.y), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x + 2.f, screen_pos.y), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x, screen_pos.y - 2.f), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x, screen_pos.y + 2.f), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x - 2.f, screen_pos.y - 2.f), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x - 2.f, screen_pos.y + 2.f), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x + 2.f, screen_pos.y - 2.f), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x + 2.f, screen_pos.y + 2.f), IM_COL32(0, 0, 0, 255), buff);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen_pos.x, screen_pos.y), IM_COL32(255, 255, 255, 255), buff);
			}
		}
	}
}

void CGUI::Render2dStuff()
{
	
}

bool CGUI::OnTouchEvent(int action, int pointer, int x, int y)
{
	ImGuiContext* context = ImGui::GetCurrentContext();
	if(context) {
		bool touchOnWindow = false;
		for(int i = 0; i < context->Windows.size(); i++)
		{
			ImGuiWindow* window = context->Windows[i];
			if(window->Active)
			{
				if(x > window->Pos.x && y > window->Pos.y
				&& x < (window->Pos.x + window->Size.x) && y < (window->Pos.y + window->Size.y))
				{
					touchOnWindow = true;
					break;
				}
			}
		}
		if(touchOnWindow) {
			return true;
		}
	}
	return false;
}

void CGUI::PushFont(const char* font_name)
{
	if(font_name == NULL || !strcasecmp(font_name, xorstr("default"))) {
		ImGui::PushFont(m_pDefaultFont);
	}
	if(!strcasecmp(font_name, xorstr("main_title"))) {
		ImGui::PushFont(m_pTitleFont);
	}
	if(!strcasecmp(font_name, xorstr("title_link"))) {
		ImGui::PushFont(m_pTitleLinkFont);
	}
	if(!strcasecmp(font_name, xorstr("buttons"))) {
		ImGui::PushFont(m_pButtonsFont);
	}
	if(!strcasecmp(font_name, xorstr("icons"))) {
		PushIcons();
	}
}

void CGUI::PushIcons()
{
	ImGui::PushFont(m_pDefaultIconsFont);
}

void CGUI::PopFont()
{
	ImGui::PopFont();
}

ImFont* CGUI::GetFont(const char* font_name)
{
	if(font_name == NULL || !strcasecmp(font_name, xorstr("default"))) {
		return m_pDefaultFont;
	}
	if(!strcasecmp(font_name, xorstr("title"))) {
		return m_pTitleFont;
	}
}

bool CGUI::Button(const char* label, ImVec2 size, bool* p_toggle, bool lighting, ImGuiCol_ col)
{
	ImGuiStyle& style = ImGui::GetStyle();
	bool result = false;
	if(p_toggle == NULL) {
		if(lighting) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0,0,0,1.f));
			result = ImGui::Button(label, size);
			ImGui::PopStyleColor();
		} else {
			ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[col]);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style.Colors[col]);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, style.Colors[col]);
			result = ImGui::Button(label, size);
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
	} else {
		if(*p_toggle) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0,0,0,1.f));
			result = ImGui::Button(label, size);
			ImGui::PopStyleColor();
		} else {
			ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[col]);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style.Colors[col]);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, style.Colors[col]);
			result = ImGui::Button(label, size);
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		if(result) {
			*p_toggle =! *p_toggle;
		}
	}
	return result;
}

void CGUI::CheckSpace()
{
	ImGui::SameLine();
	if(ImGui::GetContentRegionAvail().x < 280)
	{
		ImGui::Spacing();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().ItemSpacing.y);
	}
}


