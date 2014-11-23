#include <jni.h>
#include <android/log.h>
#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer

#include "logger.h"

extern "C" {
	//JNIEXPORT void JNICALL Java_com_example_nativeopenni_MainActivity_nativeOnStart(JNIEnv* jenv, jobject obj);
	//JNIEXPORT void JNICALL Java_com_example_nativeopenni_MainActivity_nativeSetSurface(JNIEnv* jenv, jobject obj, jobject surface);

	JNIEXPORT jint JNICALL Java_com_example_nativeopenni_MainActivity_init(JNIEnv*, jobject);
	JNIEXPORT jint JNICALL Java_com_example_nativeopenni_MainActivity_calibrate(JNIEnv*, jobject, jlong addrRgba);
	JNIEXPORT jint JNICALL Java_com_example_nativeopenni_MainActivity_recordModel(JNIEnv*, jobject);

}
