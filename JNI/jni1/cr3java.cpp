#include "cr3java.h"
#include <dlfcn.h>

std::string CRJNIEnv::fromJavaString( jstring str )
{
    if ( !str )
        return "";
	jboolean iscopy;
	const char * s = env->GetStringUTFChars( str, &iscopy );
	std::string res(s);
	env->ReleaseStringUTFChars(str, s);
	return res;
}

jstring CRJNIEnv::toJavaString( const std::string & str )
{
	return env->NewStringUTF(str.c_str());
}

jobject CRJNIEnv::enumByNativeId( const char * classname, int id )
{
	jclass cl = env->FindClass(classname);
	if ( cl ) {
		jmethodID method = env->GetStaticMethodID(cl, "byId", "(I)Lorg/coolreader/crengine/DocumentFormat;");
		if ( method ) {
			return env->CallStaticObjectMethod(cl, method, (jint)id);
		}
	}
	return NULL;
} 





