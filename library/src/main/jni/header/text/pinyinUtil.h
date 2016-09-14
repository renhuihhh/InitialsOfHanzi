/*
 * pinyinUtil.h
 *
 *  Created on: 2014年1月8日
 *      Author: renhui
 */

#ifndef PINYINUTIL_H_
#define PINYINUTIL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../iconv/include/iconv.h"
#include <string>
#include <iostream>
using namespace std;

char* ConvertHZToPY(const char *s); //汉字转拼音首字母
int isChinese(char *c); //判断是否是汉字
char* ToHalfWidthChar(char *s); //转换成半角
char* replaceNoneChinese2Sharp(char* s); //把非汉字的替换成sharp
char* getInitals(char* s);
int To_utf8(char *src,char *ret,int len);
int To_gbk(char *src,char *ret,int len);
#endif /* PINYINUTIL_H_ */
