#pragma once

#include <cstdint>
#include <link.h>
#include <string.h>
#include <jni.h>

#include "offsets.h"

class CGameAPI
{
public:
	static uintptr_t GetBase(const char* offsetName = NULL);
	static uintptr_t m_address;
};

const char* jbyteArrayToCharArray(JNIEnv* env, jbyteArray byteArray);
void cp1251_to_utf8(char *out, const char *in, unsigned int len = 0);
