#include "CString.h"
#include <iostream>
using namespace MyLib;

CString::CString():m_nLen(0),m_pAry(NULL)
{
	m_pAry = new char [1];
	*m_pAry = '\0';
}

CString::CString(const char* pChar)
{
	if(!pChar)
	{
		m_pAry = new char [1] ;
		*m_pAry = '\0';
	}
	else
	{
		m_nLen = StrLen(pChar);
		m_pAry = new char [m_nLen+1];
		StrCpy(m_pAry,pChar);
	}
}

CString::CString(const CString& rString):m_nLen(rString.m_nLen)
{
	m_pAry = new char [m_nLen+1];
	if(m_pAry)
	{
		StrCpy(m_pAry,rString.m_pAry);
	}
}
        
CString::~CString()
{
	if(m_pAry)
	{
		delete m_pAry;
		m_pAry = NULL;
	}
}

unsigned int CString::Length()const 
{
	return m_nLen;
}
        
CString& CString::operator=(const CString& rStr)
{
	//avoid Repeated copy
	if( this == &rStr  )
	{
		return *this;
	}
	else
	{
		//delete myself first
		if(m_pAry)
		{
			delete m_pAry;
		}
		//copy
		m_nLen = rStr.m_nLen;
		m_pAry = new char [m_nLen+1];
		if(m_pAry)
		{
			StrCpy(m_pAry,rStr.m_pAry);
		}
	}
	return *this;
}


int CString::Compare(const CString &rOther)const 
{
	if(NULL == m_pAry)
	{
		return -3;
	}
	char *pStr1 = m_pAry;
	char *pStr2 = rOther.m_pAry;
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

unsigned int CString::Find(const char *pFind)const
{
	if(NULL == pFind )
	{
		return -2;
	}
	if(NULL == m_pAry)
	{
		return -3;
	}
	int index=0;
	while( index <= m_nLen)
	{
		if( m_pAry[index] == *pFind)
		{
			return index;
		}
	}
	return -1;
}
unsigned int CString::Find(const CString &rFind)const
{
	return -1;
}
char * CString::c_Str()const
{
	return m_pAry;
}

CString CString::operator+(const CString& rStr)
{
	char *pNewStr = new char[m_nLen+rStr.m_nLen];
	StrCpy(pNewStr,m_pAry);
	StrCat(pNewStr,rStr.m_pAry);
	CString cRet(pNewStr);
	return cRet;
}

char * CString::StrCpy(char *pDest, const char *pSource)
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


char * CString::StrCat(char *strDest, const char *strSrc)
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
	StrCpy(strDest, strSrc);
	return pRet;
}


int CString::StrCmp(const char *pStr1, const char *pStr2)
{
	if(!pStr1 || !pStr2)
	{
		return -2;
	}
	//find the end from para1
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

char * CString::StrChr(const char *serach, char value)
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




int CString::StrLen(const char *pStr)
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
	return count;
}


std::ostream & operator <<(std::ostream &out,const CString &rString)
{
	out<<rString.c_Str();
	return out;
}