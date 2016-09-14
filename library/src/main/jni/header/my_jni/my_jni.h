/*
 * my_jni.h
 *
 *  Created on: 2014年1月8日
 *      Author: renhui
 */
#include <jni.h>
#include <string.h>
#ifndef MY_JNI_H_
#define MY_JNI_H_

//char* to jstring
jstring stoJstring(JNIEnv* env, const char* pat);
jstring stoUtf8(JNIEnv* env, char* pat);
#endif /* MY_JNI_H_ */
