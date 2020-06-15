#include "HKJNI.h"

static jmethodID setMethodID = 0;
static jmethodID getMethodID = 0;

void getNativeObjectID(JNIEnv * _env, jobject nativeObjectAccesser) {
    if (!setMethodID || !getMethodID) {
        jclass accesserClass = _env->GetObjectClass(nativeObjectAccesser);
        setMethodID = _env->GetMethodID(accesserClass, "setNativeObject", "(I)V");
        getMethodID = _env->GetMethodID(accesserClass, "getNativeObject", "()I");
        _env->DeleteLocalRef(accesserClass);
    }
}

void* getNative(JNIEnv * _env, jobject nativeObjectAccesser)
{
	if (nativeObjectAccesser) {
    	getNativeObjectID(_env, nativeObjectAccesser);
    	return (void *)(_env->CallIntMethod(nativeObjectAccesser, getMethodID));
	} else {
		return 0;
	}
}

void setNative(JNIEnv * _env, jobject nativeObjectAccesser, void* object)
{
	if (nativeObjectAccesser && object) {
		getNativeObjectID(_env, nativeObjectAccesser);
    	_env->CallVoidMethod(nativeObjectAccesser, setMethodID, object);
	}
}