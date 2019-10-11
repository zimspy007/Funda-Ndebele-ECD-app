LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sdl_ttf
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../SDL2_Image
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sdl_mixer
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sdl_mixer/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c

PROJECT_FILES := $(wildcard $(LOCAL_PATH)/game_code/tinyxml/*.cpp)
PROJECT_FILES += $(wildcard $(LOCAL_PATH)/game_code/*.cpp)
PROJECT_FILES += $(wildcard $(LOCAL_PATH)/*.cpp)

LOCAL_SRC_FILES += $(PROJECT_FILES)

LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_SHARED_LIBRARIES += SDL2_image
LOCAL_SHARED_LIBRARIES += freetype
LOCAL_SHARED_LIBRARIES += sdl_ttf
LOCAL_SHARED_LIBRARIES += flac
LOCAL_SHARED_LIBRARIES += mad
LOCAL_SHARED_LIBRARIES += mikmod
LOCAL_SHARED_LIBRARIES += ogg
LOCAL_SHARED_LIBRARIES += timidity
LOCAL_SHARED_LIBRARIES += tremor
LOCAL_SHARED_LIBRARIES += vorbis
LOCAL_SHARED_LIBRARIES += sdl_mixer

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)