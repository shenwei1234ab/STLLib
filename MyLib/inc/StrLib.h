/*
	CopyRight : Author By WEISHEN
	            Data at 2015.3.27

*/
#ifndef _STRLIB_H_
#define _STRLIB_H_


//usage:copy source string  to dest string
//para1:dest string address
//para2:source string address
//ret:dest string address  
//    if(para1 don't have enough space )return NULL  
//remark:ensure that the para1 must have enough space 
char * MyStrCpy(char *pDest, const char *pSource);


//usage:connect source string  to dest string
//para1:dest string address
//para2:
//para3:source string address
//ret:return the dest string address
char * MyStrCat(char *strDest,int n, const char *strSrc);



//usage:compare the size between para1 to para2
//para1:
//para2:
//ret:if the lengh of para1 longer than para2  return  1
//   :if the lengh of para2 longer than para1 return  -1
//   :if the lengh of para2 equal  para1 return 0
//   :if  para1 or  para2 is NULL return  -2
int MyStrCmp(const char *pStr1, const char *pStr2);




//usage:find the value from para1
//para1:
//para2:
//ret:the first position which value appear in the para1
//   :if para1 is NULL return NULL
char * MyStrChr(const char *pSerach, char value);


//usage:calculate the length of the Str
//para1:
//ret:if para1 is NULL return -1;
int MyStrLen(const char *pStr);

#endif