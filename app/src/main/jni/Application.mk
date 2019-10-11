# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
APP_STL := c++_shared
#APP_STL := stlport_static

#APP_CFLAGS += -Wno-error=format-security
APP_CFLAGS += -w
LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
# Enable c++11 extentions in source code
APP_CPPFLAGS += -std=c++11

APP_ABI := armeabi-v7a
# armeabi arm64-v8a x86 x86_64 mips armeabi-v7a

# Min SDK level
APP_PLATFORM = android-16