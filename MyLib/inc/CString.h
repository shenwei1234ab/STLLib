#ifndef _CSTRING_H_
#define _CSTRING_H_
#include <iostream>
namespace MyLib
{
	class CString
    {
    public:
        CString();
		CString(const char* pChar);
        CString(const CString& rString);
        
        virtual ~CString();
        unsigned int  Length()const;
        
        CString& operator=(const CString& rStr);

		char * c_Str()const;
		CString operator+(const CString& rStr);

		/*
		usage:find char from the string then return the first Pos the char appear
		ret:  if not find then return -1
			  if para1 is NULL then return -2
			  other error -3;
		*/
		unsigned int Find(const char *pFind)const ;
		unsigned int Find(const CString &rFind)const ;

		/*
		usage:Compare Two String Object by Comparing the Ascii of the each char
		ret:if this longer than other then return -1;
			if this short than other then return -2;
			if equal return 0;
			other error -3;
		*/
		int Compare(const CString &rOther)const ;
    private:
        int m_nLen;
        char* m_pAry;
	private:
		//intern function
		char * StrCpy(char *pDest, const char *pSource);
		char * StrCat(char *strDest, const char *strSrc);
		int StrCmp(const char *pStr1, const char *pStr2);
		int StrLen(const char *pStr);
		char * StrChr(const char *pSerach, char value);
    };
}
extern std::ostream & operator <<(std::ostream &out,const MyLib::CString &rString);
#endif