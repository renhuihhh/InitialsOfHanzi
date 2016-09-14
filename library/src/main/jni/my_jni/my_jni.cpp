#include "../header/my_jni/my_jni.h"
#include <android/log.h>
//char* to jstring
jstring stoJstring(JNIEnv* env, const char* pat) {
	__android_log_print(ANDROID_LOG_DEBUG,"renhui","<stoJstring> pat=%s",pat); // LOG类型:debug
	jclass strClass = env->FindClass("java/lang/String");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>",
			"([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
}

//char* to utf8
jstring stoUtf8(JNIEnv* env, char* pat) {
	/*变量定义*/
	jclass Class_string;
	jmethodID mid_String, mid_getBytes;
	jbyteArray bytes;
	jbyte* log_utf8;
	jstring codetype, jstr;

	Class_string = env->FindClass("java/lang/String"); //获取class

	//先将gbk字符串转为java里的string格式
	mid_String = env->GetMethodID(Class_string, "<init>",
			"([BLjava/lang/String;)V");
	bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
	codetype = env->NewStringUTF("gbk");
	jstr = (jstring) env->NewObject(Class_string, mid_String, bytes,
			codetype);

	env->DeleteLocalRef(bytes);

	//再将string变utf-8字符串。
	mid_getBytes = env->GetMethodID(Class_string, "getBytes",
			"(Ljava/lang/String;)[B");
	codetype = env->NewStringUTF("utf-8");
	bytes = (jbyteArray) env->CallObjectMethod(jstr, mid_getBytes,
			codetype);
	log_utf8 = env->GetByteArrayElements(bytes, JNI_FALSE);

	__android_log_print(ANDROID_LOG_DEBUG,"renhui","%s",pat); // LOG类型:debug
	return jstr;
}
