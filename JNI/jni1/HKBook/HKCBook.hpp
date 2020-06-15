//
//  HKCBook.hpp
//  HKEPUBC++
//
//  Created by 黄柯 on 16/1/19.
//  Copyright © 2016年 黄柯. All rights reserved.
//

#ifndef HKCBook_hpp
#define HKCBook_hpp

#include <jni.h>

#include "../cr3java.h"
#include "../HKJNI.h"

#include <HKPDFProcess/HKPDFProcess.hpp>
#include <HKPDFRender/HKPDFRender.hpp>

#ifdef __cplusplus
extern "C" {
#endif
JNI_Method_Declear(getBookCoverBuffer);


JNI_Method_Declear(openBook);
JNI_Method_Declear(closeBook);
    //1. bitmapinfo;
    //2. getBitmap 实例

JNI_Method_Declear(bitmaptAtPageIndex);


#ifdef __cplusplus
}
#endif


#endif /* HKCBook_hpp */


JNIEXPORT void JNICALL Java_HelloJni_setUserList  
  (JNIEnv *env, jobject jthiz, jobject userList){  
        int i;  
        //class ArrayList  
        jclass cls_arraylist = env->GetObjectClass(userList);  
        //method in class ArrayList  
        jmethodID arraylist_get = env->GetMethodID(cls_arraylist,"get","(I)Ljava/lang/Object;");  
        jmethodID arraylist_size = env->GetMethodID(cls_arraylist,"size","()I");  
        jint len = env->CallIntMethod(userList,arraylist_size);  
        printf("get java ArrayList<User> object by C++ , then print it...../n");  
        for(i=0;i<len;i++)
        {  
                jobject obj_user = env->CallObjectMethod(userList,arraylist_get,i);  
                jclass cls_user = env->GetObjectClass(obj_user);  
                jmethodID user_getId = env->GetMethodID(cls_user,"getId","()J");  
                jmethodID user_getUserName = env->GetMethodID(cls_user,"getUserName","()Ljava/lang/String;");  
                jmethodID user_isMan = env->GetMethodID(cls_user,"isMan","()Z");  
                jmethodID user_getAge = env->GetMethodID(cls_user,"getAge","()I");  
                jstring name = (jstring)env->CallObjectMethod(obj_user,user_getUserName);  
                jboolean b = true;  
                const char *namePtr = env->GetStringUTFChars(name,&b);  
                jlong id = env->CallLongMethod(obj_user,user_getId);  
                jboolean sex = env->CallBooleanMethod(obj_user,user_isMan);  
                jint age = env->CallIntMethod(obj_user,user_getAge);  
                printf("Id:%d; ",id);  
                printf("Name:%s; ",namePtr);  
                printf("isMan? %d; ",sex);  
                printf("Age:%d /n ",age);  
        }  
}  
