//
//  HKCBook.cpp
//  HKEPUBC++
//
//  Created by 黄柯 on 16/1/19.
//  Copyright © 2016年 黄柯. All rights reserved.
//

#ifdef __IPHONE_2_0
#define     EDIT_IN_XCODE
#endif

#include "HKCBook.hpp"

using namespace HKPDF;

JNI_Method_Start(getBookCoverBuffer)

//获取函数
/***********************************************/
JNI_CreateGetStringMethod(getFilePath)
JNI_CreateGetStringMethod(getExtenString)
JNI_CreateSetByteArrayMethod(setCoverBuffer)
/***********************************************/

jstring jfilePath;
jstring jextenString;

std::string filePath;
std::string extenString;

jfilePath = (jstring)_env->CallObjectMethod(callBack, getFilePath);
filePath = env.fromJavaString(jfilePath);

jextenString = (jstring)env->CallObjectMethod(callBack, getExtenString);
extenString = env.fromJavaString(jextenString);

HKDebugPrintf("\t filePath %s", filePath.c_str());
HKDebugPrintf("\t extenString %s", extenString.c_str());

JNI_Method_Stop

JNI_Method_Start(openBook)

//获取函数
/***********************************************/
JNI_CreateGetStringMethod(getFilePath)
JNI_CreateGetStringMethod(getExtraPath)
JNI_CreateGetStringMethod(getExtenString)
JNI_CreateGetBooleanMethod(getIsLite)
JNI_CreateSetIntMethod(setPageCount)
/***********************************************/

if (book) {
	delete book;
	book = NULL;
	setNative(env.env, nativeObjectAccesser, 0);
}

jstring jfilePath;
jstring jExtraPath;
jstring jextenString;
bool    isLite;

std::string filePath;
std::string extraPath;
std::string extenString;
std::string bookName;

jfilePath = (jstring)_env->CallObjectMethod(callBack, getFilePath);
filePath = env.fromJavaString(jfilePath);

jExtraPath = (jstring)env->CallObjectMethod(callBack, getExtraPath);
extraPath = env.fromJavaString(jExtraPath);

jextenString = (jstring)env->CallObjectMethod(callBack, getExtenString);
extenString = env.fromJavaString(jextenString);


HKDebugPrintf("\t filePath %s", filePath.c_str());
HKDebugPrintf("\t extraPath %s", extraPath.c_str());
HKDebugPrintf("\t extenString %s", extenString.c_str());

isLite =  env->CallBooleanMethod(callBack, getIsLite);

HKLine_Trace

Param param;
param.input_filename = filePath;

HKLine_Trace
book = new HKPDF::HKPDFProcess(param);
HKLine_Trace
if (book) {
	int pageCount = book->getPageCount();
	env->CallVoidMethod(callBack, setPageCount, pageCount);
	HKDebugPrintf("book: %d",book);
} else {
	HKDebugPrintf("%s open failed",filePath.c_str())
}

HKLine_Trace
setNative(env.env, nativeObjectAccesser, book);
HKLine_Trace
JNI_Method_Stop




JNI_Method_Start(closeBook)
setNative(env.env, nativeObjectAccesser, 0);

if (book) {
	delete book;
	book = NULL;
}
JNI_Method_Stop





JNI_Method_Start(bitmaptAtPageIndex)

//获取函数
/***********************************************/
JNI_CreateGetIntMethod(getPageIndex)
JNI_CreateGetIntMethod(getImageWidth)
JNI_CreateSetByteArrayMethod(setImageBuffer)
/***********************************************/

Param param;
param.pagenum = JNI_CallIntMethod(getPageIndex);
param.fit_width = JNI_CallIntMethod(getImageWidth);
HKLine_Trace

debugPrintf("book: %d",book)
debugPrintf("book->getContext(): %d",book->getContext())
debugPrintf("book->getDoc(): %d",book->getDoc())
debugPrintf("param.pagenum: %d",param.pagenum);
std::unique_ptr<HKPDFRender> page = std::unique_ptr<HKPDFRender>(new HKPDFRender(book->getContext(), book->getDoc(), param.pagenum, param));
HKLine_Trace
fz_pixmap* pix = page->pdf2image(param.fit_width, "");
fz_buffer* buffer = fz_new_buffer_from_pixmap_as_png(book->getContext(), pix);
HKLine_Trace
if (buffer) {

	jbyteArray bytearray;
	bytearray = _env->NewByteArray(buffer->len);
	_env->SetByteArrayRegion(bytearray, 0, buffer->len, (const jbyte*)buffer->data);

	JNI_CallVoidMethod1(setImageBuffer, bytearray);

	_env->DeleteLocalRef(bytearray);
	fz_drop_buffer(book->getContext(),buffer);
}


JNI_Method_Stop

                    



// JNI_Method_Start(getRangeFromPageIndex)

// //获取函数
// /***********************************************/
// JNI_CreateGetIntMethod(getPageIndex)
// JNI_CreateSetLocationMethod(setStartLocation)
// JNI_CreateSetStringMethod(setStartLocationAnchor)
// JNI_CreateSetLocationMethod(setStopLocation)
// JNI_CreateSetStringMethod(setStopLocationAnchor)
// JNI_CreateMethod(endSetRange,"()V")
// /***********************************************/

// HKRangePtr range = book->rangeAtPageIndex(JNI_CallIntMethod(getPageIndex));

// if(!range.isValid()){
// 	HKLine_Trace
// }else{

// 	if(range->startLocation.isValid()){
// 		JNI_CallSetLocationMethod(setStartLocation, range->startLocation);
// 		JNI_CallVoidMethodWithString(setStartLocationAnchor, range->startLocation->anchor);
// 	}

// 	if(range->stopLocation.isValid()){
// 		JNI_CallSetLocationMethod(setStopLocation, range->stopLocation);
// 		JNI_CallVoidMethodWithString(setStopLocationAnchor, range->stopLocation->anchor);
// 	}

// 	JNI_CallVoidMethod(endSetRange);
// }

// JNI_Method_Stop



// JNI_Method_Start(hasPrevPage)

// //获取函数
// /***********************************************/
// JNI_CreateGetIntMethod(getPageIndex)
// JNI_CreateSetBoolMethod(setResult)
// /***********************************************/

// HKLine_Trace
// bool hasPrevPage = book->hasPrevPage(JNI_CallIntMethod(getPageIndex));
// HKLine_Trace
// JNI_CallVoidMethod1(setResult, hasPrevPage);
// HKLine_Trace
// JNI_Method_Stop



// JNI_Method_Start(hasNextPage)

// //获取函数
// /***********************************************/
// JNI_CreateGetIntMethod(getPageIndex)
// JNI_CreateSetBoolMethod(setResult)
// /***********************************************/

// HKLine_Trace
// bool hasNextPage = book->hasNextPage(JNI_CallIntMethod(getPageIndex));
// JNI_CallVoidMethod1(setResult, hasNextPage);

// JNI_Method_Stop




// JNI_Method_Start(getFirstPageIndex)
// //获取函数
// /***********************************************/
// JNI_CreateSetIntMethod(setPageIndex)
// /***********************************************/

// int pageIndex = book->getFirstPageIndex();
// JNI_CallVoidMethod1(setPageIndex, pageIndex);
// JNI_Method_Stop;


// JNI_Method_Start(getLastPageIndex)
// //获取函数
// /***********************************************/
// JNI_CreateSetIntMethod(setPageIndex)
// /***********************************************/

// int pageIndex = book->getLastPageIndex();
// JNI_CallVoidMethod1(setPageIndex, pageIndex);

// JNI_Method_Stop



// JNI_Method_Start(locationFromPercent)

// //获取函数
// /***********************************************/
// JNI_CreateGetDoubleMethod(getPercent)
// JNI_CreateSetLocationMethod(setLocation)
// JNI_CreateSetStringMethod(setAnchorString)
// /***********************************************/

// HKLocationPtr location = book->locationFromPercent(JNI_CallDoubleMethod(getPercent));
// JNI_CallSetLocationMethod(setLocation, location);
// JNI_CallVoidMethodWithString(setAnchorString, location->anchor);

// JNI_Method_Stop



// JNI_Method_Start(percentFromLocation)

// //获取函数
// /***********************************************/
// JNI_CreateGetIntMethod(getChapterIndex)
// JNI_CreateGetIntMethod(getParagraphIndex)
// JNI_CreateGetIntMethod(getStringIndex)
// JNI_CreateGetStringMethod(getAnchorString)
// JNI_CreateSetDoubleMethod(setPercent)
// /***********************************************/

// HKLocationPtr location = new HKLocation(JNI_CallIntMethod(getChapterIndex),
// 										JNI_CallIntMethod(getParagraphIndex),
// 										JNI_CallIntMethod(getStringIndex));

// //HKDebugPrintf("\t chapterIndex %d", location->chapterIndex);
// //HKDebugPrintf("\t paragraphIndex %d", location->paragraphIndex);
// //HKDebugPrintf("\t stringIndex %d", location->stringIndex);

// jstring janchor = JNI_CallStringMethod(getAnchorString);
// std::string anchor  = env.fromJavaString(janchor);
// location->anchor = anchor.c_str();
// double percent = book->percentFromLocation(location);
// JNI_CallVoidMethod1(setPercent, percent);

// JNI_Method_Stop




// JNI_Method_Start(titleFromPercent)

// //获取函数
// /***********************************************/
// JNI_CreateGetDoubleMethod(getPercent)
// JNI_CreateSetStringMethod(setTitle)
// /***********************************************/

// lString16  title = book->titleFromPercent(JNI_CallDoubleMethod(getPercent));
// JNI_CallVoidMethodWithString(setTitle, title);

// JNI_Method_Stop




// JNI_Method_Start(titleFromLocation)

// //获取函数
// /***********************************************/
// JNI_CreateGetIntMethod(getChapterIndex)
// JNI_CreateGetIntMethod(getParagraphIndex)
// JNI_CreateGetIntMethod(getStringIndex)
// JNI_CreateGetStringMethod(getAnchorString)
// JNI_CreateSetStringMethod(setTitle)
// /***********************************************/

// HKLocationPtr location = new HKLocation(JNI_CallIntMethod(getChapterIndex),
// 										JNI_CallIntMethod(getParagraphIndex),
// 										JNI_CallIntMethod(getStringIndex));

// jstring janchor = JNI_CallStringMethod(getAnchorString);
// std::string anchor  = env.fromJavaString(janchor);
// location->anchor = anchor.c_str();

// JNI_CallVoidMethodWithString(setTitle, book->titleFromLocation(location));

// JNI_Method_Stop






//return HKDoHKCBook::isSupportDoc(_8([filePath UTF8String]))

//JNI_Method_Start(checkIsSupportDoc)
//
////获取函数
///***********************************************/
//JNI_CreateGetStringMethod(getFilePath)
//JNI_CreateSetBooleanMethod(setIsSupport)
///***********************************************/
//
//		jstring jfilePath;
//		std::string filePath;
//
//		jfilePath = (jstring)_env->CallObjectMethod(callBack, getFilePath);
//		filePath = env.fromJavaString(jfilePath);
//
//		HKDebugPrintf("\t filePath %s", filePath.c_str());
//
//		bool isSupport = HKDoHKCBook::isSupportDoc(filePath);
//
//		HKLine_Trace
//
//		JNI_CallVoidMethod1(setIsSupport, isSupport);
//
//JNI_Method_Stop
