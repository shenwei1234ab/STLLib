#ifndef _CLIST_H_
#define _CLIST_H_
#include <iostream>
namespace MyLib
{
 template<class T>
    class CList
    {
    public:
		struct node
		{
			node(T data=0):data(data),pNext(NULL),pPrev(NULL)
			{

			}
			
            T data;
            node* pNext;
            node* pPrev;
        };

#pragma region Iterator
		class CIterator
		{
		public:
			friend class CList;
			CIterator(node *pIter):pIter(pIter)
			{

			}
			CIterator & operator ++()
			{
				pIter = pIter->pNext;
				return *this;
			}

			CIterator operator ++(int)
			{
				CIterator iter = *this;
				++(*this);
				return iter;
			}

			CIterator & operator ==(CIterator &it)
			{
				pIter = it.pIter;
				return *this;
			}

			bool operator!=(const CIterator &it)
			{
				return pIter != it.pIter;
			}

			T operator*()
			{
				return pIter->data;
			}
			 
			node * operator ->()
			 {
				 return pIter;
			 }
		private:
			node * pIter;
		};
#pragma endregion

        CList():m_Size(0)
		{
			m_pHead = new node;
			//m_pCurrent = m_pHead;
			m_pEnd = new node;
			//m_pCurrent->pNext = m_pEnd;
			m_pEnd->pPrev = m_pHead;
			m_pHead->pNext = m_pEnd;

		}
        
		virtual ~CList()
		{
			node *pIndex=NULL;
			for( pIndex = m_pHead;pIndex->pNext != NULL;)
			{
				node *pDelete = pIndex;
				pIndex = pIndex->pNext;
				delete pDelete;
			}
			delete pIndex;
		}
        
        T GetFirst()const
		{
			if(!m_Size)
			{
				return 0;
			}
			return m_pHead->pNext->data;
		}
        
        T GetLast()const
		{
			if(!m_Size)
			{
				return 0;
			}
			//return m_pCurrent->data;
			return m_pEnd->pPrev->data;
		}
        
		void Insert(CIterator &iter,T value)
		{
			node* pNewNode = new (std::nothrow)node(value);
			if(pNewNode)
			{
				pNewNode->pNext = iter.pIter;
				pNewNode->pPrev = iter.pIter->pPrev;

				iter.pIter->pPrev->pNext = pNewNode;
				iter.pIter->pPrev = pNewNode;
			}
		}
       
        CIterator Begin()
		{
			return CIterator(m_pHead->pNext);
		}
	
		CIterator End()
		{
			return CIterator(m_pEnd);
		}


		void Push_back(T value)
		{
			node* pNode = new (std::nothrow)node(value);
			if(pNode)
			{
				pNode->data = value;
				pNode->pNext = m_pEnd;
				pNode->pPrev = m_pEnd->pPrev;
				/*m_pCurrent->pNext = pNode;
				pNode->pPrev = m_pCurrent;
				m_pCurrent = pNode;
				m_pCurrent->pNext = m_pEnd;
				m_pEnd->pPrev = m_pCurrent;*/
				m_pEnd->pPrev->pNext = pNode;
				m_pEnd->pPrev = pNode;
				++m_Size;
			}
		}
        
        unsigned int Count()const 
		{
			return m_Size;
		}
        
	private:
		//the size of the node in the list(not include the Head Node)
		unsigned int m_Size;
        node* m_pHead;
		node* m_pEnd;
		//node* m_pCurrent;
	};
}
#endif