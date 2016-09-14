//============================================================================
// Name        : CppTest.cpp
// Author      : renhui
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "header/open_hui_ren_iofhan_library_JNIEntrance.h"
#include "header/text/pinyinUtil.h"
#include "header/my_jni/my_jni.h"
#include <jni.h>
#include <android/log.h>

using namespace std;


JNIEXPORT jstring JNICALL Java_open_hui_ren_iofhan_library_JNIEntrance_welcom2NdkWorld(
		JNIEnv * env, jclass clz, jint n) {
	if (n == 0) {
		jstring res = stoJstring(env,"0");
		return res;
	} else {
		jstring res = stoJstring(env,"1");
		return res;
	}
}

JNIEXPORT jstring JNICALL Java_open_hui_ren_iofhan_library_JNIEntrance_getStringInitials(
		JNIEnv * env, jclass clz, jstring s) {
	const char *str = env->GetStringUTFChars(s,NULL);
	__android_log_print(ANDROID_LOG_DEBUG,"renhui","原始str=%s",str); // LOG类型:debug
	if (str != NULL) {
		size_t ret_size = env->GetStringLength(s);
		char* str1 = new char[strlen(str)];
		strcpy(str1,str);
		__android_log_print(ANDROID_LOG_DEBUG,"renhui","原始str1=%s%d",str1,strlen(str1)); // LOG类型:debug
		char* gbk = new char[ret_size];
		size_t z = To_gbk(str1,gbk,strlen(str1));
		char* res_gbk = new char[z+1];
		res_gbk[z] = '\0';
		memcpy(res_gbk,gbk,z);
		__android_log_print(ANDROID_LOG_DEBUG,"renhui","原始gbk=%s%d%d",gbk,strlen(gbk),z); // LOG类型:debug
		char* gbkres = getInitals(res_gbk);
		__android_log_print(ANDROID_LOG_DEBUG,"renhui","原始gbkres=%s%d",gbkres,strlen(gbkres)); // LOG类型:debug
		char* utf  = new char[ret_size+1];
		utf[ret_size]='\0';
		To_utf8(gbkres,utf,strlen(gbkres));
		__android_log_print(ANDROID_LOG_DEBUG,"renhui","原始utf=%s%d",utf,strlen(utf)); // LOG类型:debug
		jstring res = stoJstring(env,utf);
		env->ReleaseStringUTFChars(s,str);
		return res;
	}
}
