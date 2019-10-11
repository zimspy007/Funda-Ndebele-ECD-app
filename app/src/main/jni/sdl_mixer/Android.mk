LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sdl_mixer

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/../sdl-$(SDL_VERSION)/include $(LOCAL_PATH)/include \
					$(LOCAL_PATH)/../mad/include $(LOCAL_PATH)/../flac/include $(LOCAL_PATH)/../ogg/include \
					$(LOCAL_PATH)/../vorbis/include $(LOCAL_PATH)/../tremor/include $(LOCAL_PATH)/../mikmod/include \
					$(LOCAL_PATH)/timidity 
LOCAL_CFLAGS := -O3 -DWAV_MUSIC -DOGG_MUSIC -DMID_MUSIC

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES := $(notdir $(wildcard $(LOCAL_PATH)/*.c))

LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_STATIC_LIBRARIES := 

LOCAL_LDLIBS := -llog

LOCAL_STATIC_LIBRARIES += vorbis
LOCAL_STATIC_LIBRARIES += ogg

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

# Separate timidity, so it won't get rebuilt too often
LOCAL_MODULE := timidity_sdl_mixer
LOCAL_C_INCLUDES := $(LOCAL_PATH)/timidity $(LOCAL_PATH)/../sdl-$(SDL_VERSION)/include
LOCAL_CFLAGS := -O3
LOCAL_SRC_FILES := $(addprefix timidity/, $(notdir $(wildcard $(LOCAL_PATH)/timidity/*.c)))
#LOCAL_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)
