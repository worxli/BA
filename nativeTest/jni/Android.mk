LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_INSTALL_MODULES:=on

#include ../../opencv-sdk/native/jni/OpenCV.mk
include ../../openni-sdk/Android.mk

LOCAL_MODULE    := myjni
LOCAL_SRC_FILES := native.cpp
LOCAL_LDLIBS    += -lm -llog -landroid

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,android/native_app_glue)
