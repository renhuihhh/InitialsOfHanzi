# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

#libjni_entrance.so
include $(CLEAR_VARS)
LOCAL_LDLIBS+= -L$(SYSROOT)/usr/lib -llog
LOCAL_MODULE    := jni_entrance
LOCAL_CFLAGS := \
  -Wno-multichar \
  -DANDROID \
  -DLIBDIR="c" \
  -DBUILDING_LIBICONV \
  -DIN_LIBRARY

LOCAL_SRC_FILES := jni_entrance.cpp \
./text/pinyinUtil.cpp \
./my_jni/my_jni.cpp \
./iconv/libcharset/lib/localcharset.c \
./iconv/lib/iconv.c \
./iconv/lib/relocatable.c

LOCAL_C_INCLUDES += \
  $(LOCAL_PATH)/iconv/include \
  $(LOCAL_PATH)/iconv/libcharset \
  $(LOCAL_PATH)/iconv/lib \
  $(LOCAL_PATH)/iconv/libcharset/include \
  $(LOCAL_PATH)/iconv/srclib

include $(BUILD_SHARED_LIBRARY)


#LOCAL_PATH:= $(call my-dir)

#libiconv.so
include $(CLEAR_VARS)
LOCAL_MODULE := iconv
LOCAL_CFLAGS := \
  -Wno-multichar \
  -DANDROID \
  -DLIBDIR="c" \
  -DBUILDING_LIBICONV \
  -DIN_LIBRARY

LOCAL_SRC_FILES := \
	iconv/libcharset/lib/localcharset.c \
	iconv/lib/iconv.c \
	iconv/lib/relocatable.c

LOCAL_C_INCLUDES += \
  $(LOCAL_PATH)/iconv/include \
  $(LOCAL_PATH)/iconv/libcharset \
  $(LOCAL_PATH)/iconv/lib \
  $(LOCAL_PATH)/iconv/libcharset/include \
  $(LOCAL_PATH)/iconv/srclib
  
include $(BUILD_SHARED_LIBRARY)