LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(LOCAL_PATH)/../../libs/OpenCV/OpenCV.mk
include $(LOCAL_PATH)/libs/Android.mk


LOCAL_SHARED_LIBRARIES := OpenNI2

LOCAL_MODULE    := native
LOCAL_SRC_FILES := native.cpp
LOCAL_LDLIBS +=  -llog -ldl -landroid -lEGL -lGLESv1_CM 

include $(BUILD_SHARED_LIBRARY)
