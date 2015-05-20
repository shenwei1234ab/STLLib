#include <iostream>

char * MyStrCpy(char *pDest, const char *pSource)
{
	if(!pDest || !pSource)
	{
		return NULL;
	}
	char *pRet = pDest;
	while (( *pDest = *pSource )!= '\0')
	{
		*pDest++ = *pSource++;
	}
	return pRet;
}


char * MyStrCat(char *strDest, const char *strSrc)
{
	if( !strDest || !strSrc )
	{
		return NULL;
	}
	char *pRet = strDest;
	while (*strDest != '\0')
	{
		++strDest;
	}
	MyStrCpy(strDest, strSrc);
	return pRet;
}


int MyStrCmp(const char *pStr1, const char *pStr2)
{
	if(!pStr1 || !pStr2)
	{
		return -2;
	}
	//从操作数1开始找结尾
	while (*pStr1 != '\0')
	{
		if (*pStr2 == '\0')
		{
			return 1;
		}
		if (*pStr1 > *pStr2)
		{
			return 1;
		}
		if (*pStr1 < *pStr2)
		{
			return -1;
		}
		++pStr1;
		++pStr2;
	}
	return  *pStr2 == '\0' ? 0:-1;
}

char * MyStrChr(const char *serach, char value)
{
	if( !serach )
	{
		return NULL;
	}
	while (*serach != '\0')
	{
		if (*serach == value)
		{
			char *pRet = const_cast<char *>(serach);
			return pRet;
		}
		++serach;
	}
	if ( value == '\0')
	{
		char *pRet = const_cast<char *>(serach);
		return pRet;
	}
	return  NULL;
}

int MyStrLen(const char *pStr)
{
	int count = 0;
	if(!pStr)
	{
		return -1;
	}
	while(*pStr  != '\0')
	{
		++pStr;
		++count;  
	}
	return ++count;
}