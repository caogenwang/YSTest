//
//  HKJNI.h
//  HKEPUBC++
//
//  Created by 黄柯 on 16/1/29.
//  Copyright © 2016年 黄柯. All rights reserved.
//

#ifndef HKJNI_h
#define HKJNI_h

#include <jni.h>
#include <HKDebug.hpp>

void* getNative(JNIEnv * _env, jobject nativeObjectAccesser);
void setNative(JNIEnv * _env, jobject nativeObjectAccesser, void* object);

#define Method_Start            CRJNIEnv env(_env); HKMethod_Trace {/*HKDebugPrintf("\t start")*/}
#define Method_Not_Find(x)      {HKDebugPrintf("not find method:\t") HKDebugPrintf((x))}
#define Method_Stop             {/*HKDebugPrintf("\t stop")*/} return 0;

// com.huangke.HKCBook
#define JNI_Method_Declear(methoName) \
JNIEXPORT jint JNICALL Java_com_huangke_HKCBook_HKCPDF_##methoName \
(JNIEnv *_env, jobject obj, jobject nativeObjectAccesser, jobject callBack)

#define JNI_Method_Start(methoName) \
JNI_Method_Declear(methoName) \
{\
Method_Start \
HKPDF::HKPDFProcess* book = (HKPDF::HKPDFProcess*)getNative(env.env, nativeObjectAccesser); \
jclass accesserClass = env->GetObjectClass(callBack);

#define JNI_Method_Stop \
_env->DeleteLocalRef(accesserClass); \
Method_Stop\
}

#define JNI_CallVoidMethod(method) \
if (method) {\
env->CallVoidMethod(callBack, method);\
} else {\
Method_Not_Find(#method);\
}

#define JNI_CallVoidMethod1(method, param1) \
if (method) {\
env->CallVoidMethod(callBack, method, param1);\
} else {\
Method_Not_Find(#method);\
}

#define JNI_CallVoidMethod2(method, param1, param2) \
if (method) {\
env->CallVoidMethod(callBack, method, param1, param2);\
} else {\
Method_Not_Find(#method);\
}

#define JNI_CallVoidMethod3(method, param1, param2, param3) \
if (method) {\
env->CallVoidMethod(callBack, method, param1, param2, param3);\
} else {\
Method_Not_Find(#method);\
}

#define JNI_CallVoidMethod4(method, param1, param2, param3, param4) \
if (method) {\
env->CallVoidMethod(callBack, method, param1, param2, param3, param4);\
} else {\
Method_Not_Find(#method);\
}

#define JNI_CallVoidMethod5(method, param1, param2, param3, param4, param5) \
if (method) {\
env->CallVoidMethod(callBack, method, param1, param2, param3, param4, param5);\
} else {\
Method_Not_Find(#method);\
}

#define JNI_CallVoidMethod6(method, param1, param2, param3, param4, param5, param6) \
if (method) {\
env->CallVoidMethod(callBack, method, param1, param2, param3, param4, param5, param6);\
} else {\
Method_Not_Find(#method);\
}


#define JNI_CallVoidMethodWithString(method, param1) \
if (param1.length()) { \
\
std::string anchorString = _8(param1.utf8().c_str()); \
jstring janchorString = env.toJavaString(anchorString); \
\
JNI_CallVoidMethod1(method,janchorString) \
	env->DeleteLocalRef(janchorString);\
}

#define JNI_CallVoidMethodWithStringString(method, param1, param2) \
if (param1.length() && param2.length()) { \
\
std::string anchorString = _8(param1.utf8().c_str()); \
jstring janchorString = env.toJavaString(anchorString); \
std::string anchorString2 = _8(param2.utf8().c_str()); \
jstring janchorString2 = env.toJavaString(anchorString2); \
\
JNI_CallVoidMethod2(method,janchorString,janchorString2) \
	env->DeleteLocalRef(janchorString);\
	env->DeleteLocalRef(janchorString2);\
}

#define JNI_CallVoidMethodWithStringStringInt(method, param1, param2, param3) \
if (param1.length() && param2.length()) { \
\
std::string anchorString = _8(param1.utf8().c_str()); \
jstring janchorString = env.toJavaString(anchorString); \
std::string anchorString2 = _8(param2.utf8().c_str()); \
jstring janchorString2 = env.toJavaString(anchorString2); \
\
JNI_CallVoidMethod3(method,janchorString,janchorString2,param3) \
	env->DeleteLocalRef(janchorString);\
	env->DeleteLocalRef(janchorString2);\
}

#define JNI_CallVoidMethodWithStringStringStringIntInt(method, param1, param2, param3, param4, param5) \
if (param1.length() && param2.length()) { \
\
std::string anchorString = _8(param1.utf8().c_str()); \
jstring janchorString = env.toJavaString(anchorString); \
std::string anchorString2 = _8(param2.utf8().c_str()); \
jstring janchorString2 = env.toJavaString(anchorString2); \
std::string anchorString3 = _8(param3.utf8().c_str()); \
jstring janchorString3 = env.toJavaString(anchorString3); \
\
JNI_CallVoidMethod5(method,janchorString,janchorString2,janchorString3,param4,param5) \
env->DeleteLocalRef(janchorString);\
env->DeleteLocalRef(janchorString2);\
env->DeleteLocalRef(janchorString3);\
}

#define JNI_CallVoidMethodWithStringStringStringIntIntInt(method, param1, param2, param3, param4, param5, param6) \
if (param1.length() && param2.length()) { \
\
std::string anchorString = _8(param1.utf8().c_str()); \
jstring janchorString = env.toJavaString(anchorString); \
std::string anchorString2 = _8(param2.utf8().c_str()); \
jstring janchorString2 = env.toJavaString(anchorString2); \
std::string anchorString3 = _8(param3.utf8().c_str()); \
jstring janchorString3 = env.toJavaString(anchorString3); \
\
JNI_CallVoidMethod6(method,janchorString,janchorString2,janchorString3,param4,param5,param6) \
env->DeleteLocalRef(janchorString);\
env->DeleteLocalRef(janchorString2);\
env->DeleteLocalRef(janchorString3);\
}

#define JNI_CallSetLocationMethod(method, location) \
JNI_CallVoidMethod3(method, location->chapterIndex, location->paragraphIndex, location->stringIndex)

#define JNI_CallBooleanMethod(method) \
(method)?(env->CallBooleanMethod(callBack, (method))):((Method_Not_Find(#method)),0)

#define JNI_CallIntMethod(method) \
(method)?(env->CallIntMethod(callBack, (method))):((Method_Not_Find(#method)),0)

#define JNI_CallDoubleMethod(method) \
(method)?(env->CallDoubleMethod(callBack, (method))):((Method_Not_Find(#method)),0.0f)

#define JNI_CallFloatMethod(method) \
(method)?(env->CallFloatMethod(callBack, (method))):((Method_Not_Find(#method)),0.0f)

#define JNI_CallStringMethod(method) \
((jstring)((method)?(env->CallObjectMethod(callBack, (method))):((Method_Not_Find(#method)),(jstring)0)))

#pragma mark -
#pragma mark - createMethod
#pragma mark -

#define JNI_CreateMethod(name,param) \
jmethodID name = env->GetMethodID(accesserClass, #name, param);

#define JNI_CreateVoidMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "()V");

#define JNI_CreateGetIntMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "()I");

#define JNI_CreateGetFloatMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "()F");

#define JNI_CreateGetBooleanMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "()Z");

#define JNI_CreateGetDoubleMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "()D");

#define JNI_CreateGetStringMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "()Ljava/lang/String;");

#define JNI_CreateGetObjectMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "()Ljava/lang/Object;");

#define JNI_CreateGetObjectMethodWithInt(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(I)Ljava/lang/Object;");

#define JNI_CreateSetIntMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(I)V");

#define JNI_CreateSetIntIntMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(II)V");

#define JNI_CreateSetIntIntIntMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(III)V");

#define JNI_CreateSetDoubleMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(D)V");

#define JNI_CreateSetBooleanMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(Z)V");

#define JNI_CreateSetLocationMethod(name) \
JNI_CreateSetIntIntIntMethod(name)

#define JNI_CreateSetStringMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(Ljava/lang/String;)V");

#define JNI_CreateSetStringStringMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(Ljava/lang/String;Ljava/lang/String;)V");

#define JNI_CreateSetStringStringIntMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(Ljava/lang/String;Ljava/lang/String;I)V");

#define JNI_CreateSetStringStringStringIntIntIntMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;III)V");

#define JNI_CreateSetBoolMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "(Z)V");

#define JNI_CreateSetByteArrayMethod(name) \
jmethodID name = env->GetMethodID(accesserClass, #name, "([B)V");


#endif /* HKJNI_h */
