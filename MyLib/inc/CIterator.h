#ifndef _CITERATOR_H
#define _CITERATOR_H

//µü´úÆ÷½Ó¿Ú
class CIterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual int CurrentItem() = 0;
};
#endif