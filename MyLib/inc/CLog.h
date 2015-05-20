#ifndef _CLOG_
#define _CLOG_
#include <iostream>
#define CLOG(Message)  CLOG::PrintLog(__FILE__,__LINE__,__FUNCTION__,Message)
class CLOG
{
public:
	static void PrintLog(const char* pFileName,int Line,const char *pFunName,const char *pMessage)
	{
		printf("%s(%d):in %s %s \n",pFileName,Line,pFunName,pMessage);
	}
};
#endif