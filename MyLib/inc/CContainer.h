#ifndef _CCONTAINER_H_
#define _CCONTAINER_H_


class CIterator;
//ÈÝÆ÷ 
class CContainer
{
public:
	virtual ~CContainer()
	{

	}
	virtual CIterator* Create() = 0;
};
#endif