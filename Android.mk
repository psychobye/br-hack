LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libdobby
LOCAL_SRC_FILES := vendor/Dobby/$(TARGET_ARCH_ABI)/libdobby.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_STATIC_LIBRARIES := libdobby
LOCAL_LDLIBS := -llog -lEGL -lGLESv1_CM -lGLESv2 -lGLESv3
LOCAL_CPPFLAGS := -Wno-error=format-security
LOCAL_CPPFLAGS += -std=c++17 -O3 -fvisibility=hidden
LOCAL_MODULE := plugin

FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/gui/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/game/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/game/rw/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/game/math/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/plugin/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/plugin/pools/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/vendor/imgui/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/vendor/imgui/backend/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/vendor/Substrate/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/vendor/Substrate/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/vendor/And64InlineHook/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/vendor/RakNet/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/vendor/RakNet/SAMP/*.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_SHARED_LIBRARY)
