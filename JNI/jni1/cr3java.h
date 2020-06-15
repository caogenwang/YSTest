/*
 * CoolReader 3 Java Port helpers.
 */

#ifndef CR3_JAVA_H
#define CR3_JAVA_H

#include <jni.h>
#include <android/log.h>
#include <string>

#define  CR_DEBUG

#ifdef CR_DEBUG
#define  LOG_TAG    "CHK"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGASSERTFAILED(cond,...)  __android_log_assert(cond,LOG_TAG,__VA_ARGS__)
#else
#define  LOG_TAG
#define  LOGI(...)
#define  LOGE(...)
#define  LOGV(...)
#define  LOGD(...)
#define  LOGASSERTFAILED(cond,...)  
#endif

class CRJNIEnv {
public:
	JNIEnv * env;
    CRJNIEnv(JNIEnv * pEnv) : env(pEnv) { }
    JNIEnv * operator -> () { return env; }
    std::string fromJavaString( jstring str );
	jstring toJavaString( const std::string & str );
	jobject enumByNativeId( const char * classname, int id ); 
};

class CRClassAccessor : public CRJNIEnv {
protected:
	jclass cls;
public:
	jclass getClass() { return cls; }
    CRClassAccessor(JNIEnv * pEnv, jclass _class) : CRJNIEnv(pEnv)
    {
    	cls = _class;
    }
    CRClassAccessor(JNIEnv * pEnv, const char * className) : CRJNIEnv(pEnv)
    {
    	cls = env->FindClass(className);
    }
};

class CRObjectAccessor : public CRClassAccessor {
	jobject obj;
public:
	jobject getObject() { return obj; }
	CRObjectAccessor(JNIEnv * pEnv, jobject _obj)
    : CRClassAccessor(pEnv, pEnv->GetObjectClass(_obj))
    {
    	obj = _obj;
    }
};

class CRFieldAccessor {
protected:
	CRObjectAccessor & objacc;
	jfieldID fieldid;
public:
	CRFieldAccessor( CRObjectAccessor & acc, const char * fieldName, const char * fieldType )
	: objacc(acc)
	{
		fieldid = objacc->GetFieldID( objacc.getClass(), fieldName, fieldType );
	}
	jobject getObject()
	{
		 return objacc->GetObjectField(objacc.getObject(), fieldid); 
	}
	void setObject( jobject obj )
	{
		 return objacc->SetObjectField(objacc.getObject(), fieldid, obj); 
	}
};

class CRMethodAccessor {
protected:
	CRObjectAccessor & objacc;
	jmethodID methodid;
public:
	CRMethodAccessor( CRObjectAccessor & acc, const char * methodName, const char * signature )
	: objacc(acc)
	{
		methodid = objacc->GetMethodID( objacc.getClass(), methodName, signature );
	}
	jobject callObj()
	{
		return objacc->CallObjectMethod( objacc.getObject(), methodid ); 
	}
	jobject callObj(jobject obj)
	{
		return objacc->CallObjectMethod( objacc.getObject(), methodid, obj ); 
	}
	jobject callObj(jobject obj1, jobject obj2)
	{
		return objacc->CallObjectMethod( objacc.getObject(), methodid, obj1, obj2 ); 
	}
	jboolean callBool()
	{
		return objacc->CallBooleanMethod( objacc.getObject(), methodid ); 
	}
	jint callInt()
	{
		return objacc->CallIntMethod( objacc.getObject(), methodid ); 
	}
};

class CRStringField : public CRFieldAccessor {
public:
	CRStringField( CRObjectAccessor & acc, const char * fieldName )
	: CRFieldAccessor( acc, fieldName, "Ljava/lang/String;" ) 
	{
	}
	std::string get() {
		jstring str = (jstring)objacc->GetObjectField(objacc.getObject(), fieldid);
		std::string res = objacc.fromJavaString(str);
		objacc.env->DeleteLocalRef(str);
		return res;
	}
	void set( const std::string& str) { objacc->SetObjectField(objacc.getObject(), fieldid, objacc.toJavaString(str)); } 
};

class CRIntField : public CRFieldAccessor {
public:
	CRIntField( CRObjectAccessor & acc, const char * fieldName )
	: CRFieldAccessor( acc, fieldName, "I" ) 
	{
	}
	int get() { return objacc->GetIntField(objacc.getObject(), fieldid); } 
	void set(int v) { objacc->SetIntField(objacc.getObject(), fieldid, v); } 
};

class CRLongField : public CRFieldAccessor {
public:
	CRLongField( CRObjectAccessor & acc, const char * fieldName )
	: CRFieldAccessor( acc, fieldName, "J" ) 
	{
	}
	long get() { return objacc->GetLongField(objacc.getObject(), fieldid); } 
	void set(long v) { objacc->SetLongField(objacc.getObject(), fieldid, v); } 
};

#endif
