#include "entry.h"
#include "xorstr.h"

extern "C"
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    // Делаем все, что обычно делается в JNI_Onload
	CApp::Initialise(eAppInit::APP_INIT_OFFSETS);
	
	pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
	
    return JNI_VERSION_1_6;
}

void (*orig_JNILib_step)(JNIEnv* env, jclass cls);
void hook_JNILib_step(JNIEnv* env, jclass cls)
{
	orig_JNILib_step(env, cls);
}

bool inject_eglSwapBuffers()
{
	// Hook eglSwapBuffers
    uintptr_t addr = (uintptr_t)dlsym(RTLD_NEXT, xorstr("eglSwapBuffers"));
	if(addr) {
    	DobbyHook((void *)addr, (void *)hook_eglSwapBuffers, (void **)&orig_eglSwapBuffers);
    	return true;
	}
	return false;
}

void* hack_thread(void* args)
{
	while(!CGameAPI::GetBase()) {}
	while(*(int *)(CGameAPI::GetBase(xorstr("RwInitialised"))) == 0) {}
	
	MSHookFunction((void *)(CGameAPI::GetBase(xorstr("RakClient::RegisterAsRemoteProcedureCall"))), (void *)&hook_RakClient__RegisterAsRemoteProcedureCall, (void **)&orig_RakClient__RegisterAsRemoteProcedureCall);
	CApp::Initialise(eAppInit::APP_INIT_RW);
	
	//if(inject_eglSwapBuffers())
	{
		MSHookFunction((void *)(CGameAPI::GetBase(xorstr("JNILib_step"))), (void *)&hook_JNILib_step, (void **)&orig_JNILib_step);
		//MSHookFunction((void *)(CGameAPI::GetBase(xorstr("TouchEvent"))), (void *)&hook_TouchEvent, (void **)&orig_TouchEvent);
		MSHookFunction((void *)(CGameAPI::GetBase(xorstr("CNetGame::ProcessNetwork"))), (void *)&hook_CNetGame__ProcessNetwork, (void **)&orig_CNetGame__ProcessNetwork);
		// MSHookFunction((void *)(CGameAPI::GetBase(xorstr("CNetTextDrawPool::SetServerLogo"))), (void *)&hook_CNetTextDrawPool__SetServerLogo, (void **)&orig_CNetTextDrawPool__SetServerLogo);
		uintptr_t ng_pRakClient = *(uintptr_t *)(CGameAPI::GetBase(xorstr("CNetGame::m_pRakClient")));
		while(!ng_pRakClient) {
			ng_pRakClient = *(uintptr_t *)(CGameAPI::GetBase(xorstr("CNetGame::m_pRakClient")));
		}
		MSHookFunction((void *)( *(uintptr_t *)(*(uintptr_t *)ng_pRakClient + 8) ), (void *)&hook_RakClient__Connect, (void **)&orig_RakClient__Connect);
		//MSHookFunction((void *)( *(uintptr_t *)(*(uintptr_t *)ng_pRakClient + 32) ), (void *)&hook_RakClient__Send, (void **)&orig_RakClient__Send);
		MSHookFunction((void *)( *(uintptr_t *)(*(uintptr_t *)ng_pRakClient + 108) ), (void *)&hook_RakClient__RPC, (void **)&orig_RakClient__RPC);
		
	}
	
	pthread_exit(nullptr);
    return nullptr;
}

static bool setup = false;
static bool m_bNeedClearMousePos = false;

EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	if(!setup) {
		// Setup Dear ImGui context
    	IMGUI_CHECKVERSION();
    
    	ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2((float)RsGlobal->width, (float)RsGlobal->height);
		
		// Setup Platform/Renderer backends
    	ImGui_ImplOpenGL3_Init(xorstr("#version 300 es"));
    	
    	// We load the default font with increased size to improve readability on many devices with "high" DPI.
    	ImGui::StyleColorsDark();
		// Arbitrary scale-up
    	ImGui::GetStyle().ScaleAllSizes(2.f);
        CApp::Initialise(eAppInit::APP_INIT_GUI);
    	
		setup = true;
    }

    ImGuiIO &io = ImGui::GetIO();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // Render ImGui windows here.
    CApp::Render();

    // Rendering
    ImGui::EndFrame();
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_bNeedClearMousePos) {
        io.MousePos = ImVec2(-1, -1);
        m_bNeedClearMousePos = false;
    }

    return orig_eglSwapBuffers(dpy, surface);
}

void hook_TouchEvent(JNIEnv* env, jclass cls, int action, int pointerId, int x1, int y1, int x2, int y2, int x3, int y3)
{
	ImGuiIO& io = ImGui::GetIO();
	
	if(action == 0) // down
	{
		io.MouseDown[pointerId] = true;
		io.MousePos = ImVec2((pointerId == 0 ? x1 : (pointerId == 1 ? x2 : x3)), (pointerId == 0 ? y1 : (pointerId == 1 ? y2 : y3)));
	}
	if(action == 2) {
		io.MousePos = ImVec2((pointerId == 0 ? x1 : (pointerId == 1 ? x2 : x3)), (pointerId == 0 ? y1 : (pointerId == 1 ? y2 : y3)));
	}
	if(action == 1) {
		io.MouseDown[pointerId] = false;
		m_bNeedClearMousePos = true;
	}
	
	if(!CApp::OnTouchEvent(action, pointerId, (pointerId == 0 ? x1 : (pointerId == 1 ? x2 : x3)), (pointerId == 0 ? y1 : (pointerId == 1 ? y2 : y3)))) {
		orig_TouchEvent(env, cls, action, pointerId, x1, y1, x2, y2, x3, y3);
	}
}


