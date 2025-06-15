#pragma once

#include <unistd.h>
#include <dlfcn.h>
#include <pthread.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <jni.h>

#include "vendor/RakNet/BitStream.h"

#include "vendor/Dobby/include/dobby.h"
#include "vendor/Substrate/CydiaSubstrate.h"
#include "vendor/And64InlineHook/And64InlineHook.hpp"

#include "vendor/imgui/backend/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_internal.h"

#include "game/rw/rw.h"
#include "game/hooks.h"

#include "app.h"
#include "plugin.h"

void* hack_thread(void* args);
bool inject_eglSwapBuffers();

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);

void (*orig_TouchEvent)(JNIEnv* env, jclass cls, int action, int pointerId, int x1, int y1, int x2, int y2, int x3, int y3);
void hook_TouchEvent(JNIEnv* env, jclass cls, int action, int pointerId, int x1, int y1, int x2, int y2, int x3, int y3);

