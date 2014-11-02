#include <jni.h>


void func() {

	openni::Device();

}

extern "C" {


	JNIEXPORT jstring JNICALL Java_com_example_nativetest_MainActivity_getMessage(JNIEnv *, jobject, jstring);

	JNIEXPORT jstring JNICALL Java_com_example_nativetest_MainActivity_getMessage(JNIEnv *env, jobject thisObj, jstring javaString) {
		//Get the native string from javaString
		    const char *nativeString = env->GetStringUTFChars(javaString, 0);

		    //Do something with the nativeString

		    //DON'T FORGET THIS LINE!!!
		    env->ReleaseStringUTFChars(javaString, nativeString);

		    return javaString;
	}

}
