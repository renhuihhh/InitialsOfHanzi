#include "../header/text/pinyinUtil.h"
#include "../iconv/include/iconv.h"
//汉字转拼音首字母
char* ConvertHZToPY(const char *s) {
	if (s == NULL)
		return NULL;
	static int li_SecPosValue[] = { 1601, 1637, 1833, 2078, 2274, 2302, 2433,
			2594, 2787, 3106, 3212, 3472, 3635, 3722, 3730, 3858, 4027, 4086,
			4390, 4558, 4684, 4925, 5249 };
	static char* lc_FirstLetter[] = { "A", "B", "C", "D", "E", "F", "G", "H",
			"J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "W", "X",
			"Y", "Z" };
	static char ls_SecondSecTable[] =
			"CJWGNSPGCGNE[Y[BTYYZDXYKYGT[JNNJQMBSGZSCYJSYY[PGKBZGY[YWJKGKLJYWKPJQHY[W[DZLSGMRYPYWWCCKZNKYYGTTNJJ\
NYKKZYTCJNMCYLQLYPYQFQRPZSLWBTGKJFYXJWZLTBNCXJJJJTXDTTSQZYCDXXHGCK[PHFFSS[YBGXLPPBYLL[HLXS[ZM[JHSOJNGHDZQYKLGJHSGQZHXQGKEZZWYSCSCJXYEYXADZPMDSSMZJZQJYZC[J[WQJBYZPXGZNZCPWHKXHQKMWFBPBYDTJZZKQHYLYGXFP"
					"TYJYYZPSZLFCHMQSHGMXXSXJ[[DCSBBQBEFSJYHXWGZKPYLQBGLDLCCTNMAYDDKSSNGYCSGXLYZAYBNPTSDKDYLHGYMYLCXPY[JNDQJWXQXFYYFJLEJPZRXCCQWQQSBNKYMGPLBMJRQCFLNYMYQMSQYRBCJTHZTQFRXQHXMJJCJLXQGJMSHZKBSWYEMYLTXFSYDSWL\
YCJQXSJNQBSCTYHBFTDCYZDJWYGHQFRXWCKQKXEBPTLPXJZSRMEBWHJLBJSLYYSMDXLCLQKXLHXJRZJMFQHXHWYWSBHTRXXGLHQHFNM[YKLDYXZPYLGG[MTCFPAJJZYLJTYANJGBJPLQGDZYQYAXBKYSECJSZNSLYZHSXLZCGHPXZHZNYTDSBCJKDLZAYFMYDLEBBG"
					"QYZKXGLDNDNYSKJSHDLYXBCGHXYPKDJMMZNGMMCLGWZSZXZJFZNMLZZTHCSYDBDLLSCDDNLKJYKJSYCJLKWHQASDKNHCSGANHDAASHTCPLCPQYBSDMPJLPZJOQLCDHJJYSPRCHN[NNLHLYYQYHWZPTCZGWWMZFFJQQQQYXACLBHKDJXDGMMYDJXZLLSYGXGKJRYWZW\
YCLZMSSJZLDBYD[FCXYHLXCHYZJQ[[QAGMNYXPFRKSSBJLYXYSYGLNSCMHZWWMNZJJLXXHCHSY[[TTXRYCYXBYHCSMXJSZNPWGPXXTAYBGAJCXLY[DCCWZOCWKCCSBNHCPDYZNFCYYTYCKXKYBSQKKYTQQXFCWCHCYKELZQBSQYJQCCLMTHSYWHMKTLKJLYCXWHEQQ"
					"HTQH[PQ[QSCFYMNDMGBWHWLGSLLYSDLMLXPTHMJHWLJZYHZJXHTXJLHXRSWLWZJCBXMHZQXSDZPMGFCSGLSXYMJSHXPJXWMYQKSMYPLRTHBXFTPMHYXLCHLHLZYLXGSSSSTCLSLDCLRPBHZHXYYFHB[GDMYCNQQWLQHJJ[YWJZYEJJDHPBLQXTQKWHLCHQXAGTLXLJ\
XMSL[HTZKZJECXJCJNMFBY[SFYWYBJZGNYSDZSQYRSLJPCLPWXSDWEJBJCBCNAYTWGMPAPCLYQPCLZXSBNMSGGFNZJJBZSFZYNDXHPLQKZCZWALSBCCJX[YZGWKYPSGXFZFCDKHJGXDLQFSGDSLQWZKXTMHSBGZMJZRGLYJBPMLMSXLZJQQHZYJCZYDJWBMYKLDDPM"
					"JEGXYHYLXHLQYQHKYCWCJMYYXNATJHYCCXZPCQLBZWWYTWBQCMLPMYRJCCCXFPZNZZLJPLXXYZTZLGDLDCKLYRZZGQTGJHHGJLJAXFGFJZSLCFDQZLCLGJDJCSNZLLJPJQDCCLCJXMYZFTSXGCGSBRZXJQQCTZHGYQTJQQLZXJYLYLBCYAMCSTYLPDJBYREGKLZYZH\
LYSZQLZNWCZCLLWJQJJJKDGJZOLBBZPPGLGHTGZXYGHZMYCNQSYCYHBHGXKAMTXYXNBSKYZZGJZLQJDFCJXDYGJQJJPMGWGJJJPKQSBGBMMCJSSCLPQPDXCDYYKY[CJDDYYGYWRHJRTGZNYQLDKLJSZZGZQZJGDYKSHPZMTLCPWNJAFYZDJCNMWESCYGLBTZCGMSSL"
					"LYXQSXSBSJSBBSGGHFJLYPMZJNLYYWDQSHZXTYYWHMZYHYWDBXBTLMSYYYFSXJC[DXXLHJHF[SXZQHFZMZCZTQCXZXRTTDJHNNYZQQMNQDMMG[YDXMJGDHCDYZBFFALLZTDLTFXMXQZDNGWQDBDCZJDXBZGSQQDDJCMBKZFFXMKDMDSYYSZCMLJDSYNSBRSKMKMPCK\
LGDBQTFZSWTFGGLYPLLJZHGJ[GYPZLTCSMCNBTJBQFKTHBYZGKPBBYMTDSSXTBNPDKLEYCJNYDDYKZDDHQHSDZSCTARLLTKZLGECLLKJLQJAQNBDKKGHPJTZQKSECSHALQFMMGJNLYJBBTMLYZXDCJPLDLPCQDHZYCBZSCZBZMSLJFLKRZJSNFRGJHXPDHYJYBZGDL"
					"QCSEZGXLBLGYXTWMABCHECMWYJYZLLJJYHLG[DJLSLYGKDZPZXJYYZLWCXSZFGWYYDLYHCLJSCMBJHBLYZLYCBLYDPDQYSXQZBYTDKYXJY[CNRJMPDJGKLCLJBCTBJDDBBLBLCZQRPPXJCJLZCSHLTOLJNMDDDLNGKAQHQHJGYKHEZNMSHRP[QQJCHGMFPRXHJGDYC\
HGHLYRZQLCYQJNZSQTKQJYMSZSWLCFQQQXYFGGYPTQWLMCRNFKKFSYYLQBMQAMMMYXCTPSHCPTXXZZSMPHPSHMCLMLDQFYQXSZYYDYJZZHQPDSZGLSTJBCKBXYQZJSGPSXQZQZRQTBDKYXZKHHGFLBCSMDLDGDZDBLZYYCXNNCSYBZBFGLZZXSWMSCCMQNJQSBDQSJ"
					"TXXMBLTXZCLZSHZCXRQJGJYLXZFJPHYMZQQYDFQJJLZZNZJCDGZYGCTXMZYSCTLKPHTXHTLBJXJLXSCDQXCBBTJFQZFSLTJBTKQBXXJJLJCHCZDBZJDCZJDCPRNPQCJPFCZLCLZXZDMXMPHJSGZGSZZQLYLWTJPFSYASMCJBTZKYCWMYTCSJJLJCQLWZMALBXYFBPNLSFHTGJWEJJXXGLLJSTGSHJQLZFKCGNNNSZFDEQFHBSAQTGYLBXMMYGSZLDYDQMJJRGBJTKGDHGKBLQKBDMBYLXWCXYTTYBKMRTJZXQJBHLMHMJJZMQASLDCYXYQDLQCAFYWYXQHZ\
";

	int H, L, W;
	unsigned stringlen = strlen(s);
	char* result = (char*) malloc(stringlen + 1);
	memset(result, 0, stringlen + 1);
	int index = 0;
	int i;
	for (i = 0; i < (int) stringlen; i++, index++) {
		H = (unsigned char) (s[i]);
		L = (unsigned char) (s[i + 1]);
		if (H < 0xA1 || L < 0xA1) {
			result[index] = s[i];
			continue;
		} else {
			W = (H - 160) * 100 + L - 160;
		}

		if (W > 1600 && W < 5590) {
			int j;
			for (j = 22; j >= 0; j--) {
				if (W >= li_SecPosValue[j]) {
					result[index] = lc_FirstLetter[j][0];
					i++;
					break;
				}
			}
			continue;
		} else {
			i++;
			W = (H - 160 - 56) * 94 + L - 161;
			if (W >= 0 && W <= 3007)
				result[index] = ls_SecondSecTable[W];
			else {
				result[index] = (char) H;
				result[index] = (char) L;
			}
		}
	}
	return result;
}

/**
 * 中文字串转为utf8格式字串
 * src  中文字串
 * ret  utf8字串
 * len  src串的长度
 * 返回转换后的utf8串的长度
 * 说明：ret大小应该是src的1.5倍以上。一个汉字转为了3个字节的utf编码
 **/
int To_utf8(char *src,char *ret,int len){
	iconv_t c_p;
	char *in,*out;
	int i,i_len,o_len;
	unsigned char tmp[1500];
	memset(tmp,0,sizeof(tmp));
	c_p=libiconv_open("UTF-8","GBK"); //GBK 转为 UTF-8
	in=(char *)src;out=(char *)tmp;
	i_len=len;o_len=1500;
	iconv(c_p,&in,(size_t*)&i_len,&out,(size_t*)&o_len);
	i=strlen((char *)tmp);
	memcpy(ret,tmp,i);
	iconv_close(c_p);
	return i;
}

/**
 * utf8格式字串转为中文字串
 * src  utf8字串
 * ret  中文字串
 * len  src串的长度
 * 返回转换后的中文串的长度
 **/
int To_gbk(char *src,char *ret,int len){
	iconv_t c_p;
	char *in,*out;
	int i,i_len,o_len;
	unsigned char tmp[1500];
	memset(tmp,0,sizeof(tmp));
	c_p=libiconv_open("GBK","UTF-8"); //UTF-8转为 GBK
	in=(char *)src;out=(char *)tmp;
	i_len=len;o_len=1500;
	iconv(c_p,&in,(size_t*)&i_len,&out,(size_t*)&o_len);
	i=strlen((char *)tmp);
	memcpy(ret,tmp,i);
	iconv_close(c_p);
	return i;
}



int isChinese(char *c) {
	//判断一个unicode是否是汉字"""
	if (*c == 0)
		return 0;  //如果到字符串尾则说明该字符串没有中文字符
	if (*c & 0x80)         //如果字符高位为1且下一字符高位也是1则有中文字符
			{
		if (*(c + 1) & 0x80)
			return 1;
	} else {
		return 0;
	}
	return 0;
}

char* replaceNoneChinese2Sharp(char* s) {
	char *res = new char[strlen(s) + 1];
	res[strlen(s)] = '\0';
	for (int i = 0; i < strlen(s);) {
		char hz[2] = { *(s + i), *(s + i + 1) };
		int flag = isChinese(hz);
		string ss = flag == 1 ? "是" : "否";
//            cout<<hz<<"isChinese:"<<ss<<endl;

		if (!flag)         //不是汉字，其他半角
		{
//			printf("半角=%c,%d\n", s + i, s[i]);
			if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)) {
				*(res + i) = *(s + i);
			} else {
				*(res + i) = '#';
			}

			i += 1;
		} else         //全角处理
		{
			res[i] = *(s + i);
			res[i + 1] = *(s + i + 1);
			i += 2;
		}

	}
	return res;
}

//全角转半角
char* ToHalfWidthChar(char *s) {
	string str = s;
	string result = "";
	unsigned char tmp;
	unsigned char tmp1;
	for (unsigned int i = 0; i < str.length(); i++) {
		tmp = str[i];
		tmp1 = str[i + 1];
//        cout << "uchar:" << (int) tmp << endl;
		if (tmp == 163)  ///第一个字节是163，标志着是全角字符
				{
			result += (unsigned char) str[i + 1] - 128;
			i++;
			continue;
		} else if (tmp > 163)    //汉字
				{
			result += str.substr(i, 2);
			i++;
			continue;
		} else if (tmp == 161 && tmp1 == 161)    ///处理全角空格
				{
			result += "";
			i++;
		} else {
			result += str.substr(i, 1);
		}
//		free(&tmp);
//		free(&tmp1);
//		free(&str);
	}

	char *a = new char[(result.size() + 1)];
	strcpy(a, result.c_str());
//	free(&result);
	return a;
}

//返回字符串对应的首字母数组
char* getInitals(char* s) {
	if (s == NULL) {
		return NULL;
	}
	s = ToHalfWidthChar(s);    //转半角
	cout << "转半角之后：" << s << endl;
	s = replaceNoneChinese2Sharp(s);    //替换非汉字
	cout << "替换之后：" << s << endl;
	char* pJianPin;
	pJianPin = ConvertHZToPY(s);
	printf("JianPin = [%s]\n", pJianPin);
	free(s);
	return pJianPin;
}

//int main() {
//    const char a[] = "芭比娃娃，鳌是一个生僻字)）中国的英文是China";
//    unsigned size = strlen(a);
//    printf("所转换的字符长度为:%d\n",size);
//    printf("所转换的字符串为:%s\n",a);
//    char* pJianPin;
//    pJianPin = ConvertHZToPY(a);
//    printf("JianPin = [%s]\n", pJianPin);
//    free(pJianPin);
//    char *s="（";
//    printf("++++++++%d\n",isChinese(s));
//
//	char *s = "芭比娃娃，鳌是一个生僻字)）????？中国的英文是China";
//	s = ToHalfWidthChar(s);    //转半角
//	cout << "转半角之后：" << s << endl;
//	s = replaceNoneChinese2Sharp(s);    //替换非汉字
//	cout << "替换之后：" << s << endl;
//
//	char* pJianPin;
//	pJianPin = ConvertHZToPY(s);
//	printf("JianPin = [%s]\n", pJianPin);
//	free(s);
//	free(pJianPin);
//	return 1;
//}
