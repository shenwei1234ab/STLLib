#ifndef _CITERATOR_H
#define _CITERATOR_H

//�������ӿ�
class CIterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual int CurrentItem() = 0;
};
#endif