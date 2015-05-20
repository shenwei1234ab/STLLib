#ifndef _CVECTOR_H_
#define _CVECTOR_H_
#include "CContainer.h"
#include "CIterator.h"
#include <assert.h>
namespace MyLib
{
	template <class T>
	class CVector:public CContainer
	{
	public:
		CVector():m_Data(NULL),m_Size(0),m_Capacity(0)
		{

		}

		~CVector()
		{
			if(m_Data)
			{
				delete []m_Data;
				m_Data = NULL;
			}
		}

		size_t Size()const
		{
			return m_Size;
		}

		size_t Capacity()const
		{
			return m_Capacity;
		}

		//reserve the capacity
		void Reserve(size_t needSize)
		{
			_CheckCapacity(needSize);
		}


		void Push_back(T data)
		{
			_CheckCapacity(m_Size+1);
			if(m_Data)
			{
				m_Data[m_Size++] = data;
			}
		}
		

		void Pop_back()
		{
			if(m_Size>0)
			{
				--m_Size;
			}
		}

		void Insert(unsigned int index,T value)
		{
			_CheckCapacity(m_Size +1);
			if(index > m_Size)
			{
				index = m_Size;
			}
			//  Reverse insert
			for(int i=m_Size;i>=index+1;--i)
			{
				m_Data[i]=m_Data[i-1];
			}
			m_Data[i] = value;
		}

		T CVector::operator [](int nIndex)
		{
			assert(nIndex >= 0);
			assert(nIndex < m_Capacity);
			return m_Data[nIndex];
		}


		T CVector::Get(int nIndex)
		{
			assert(nIndex >= 0);
			assert(nIndex < m_Capacity);
			return m_Data[nIndex];
		}

#pragma region   迭代器 
		class CVectorIterator :public CIterator
		{
		public:
			//一个迭代器对应一个容器
			CVectorIterator(CVector *pVector) :m_Vector(pVector),m_nCurrent(0)
			{

			}
		    //前置++
			CVectorIterator & operator++()
			{
				Next();
				return *this;
			}

			bool operator ==( const CVectorIterator &rOther)
			{
				return m_nCurrent == rOther.m_nCurrent;
			}

			bool operator !=(const CVectorIterator &rOther)
			{
				return !(*this == rOther);
			}

			T operator*()
			{
				return m_Vector->Get(m_nCurrent);
			}


			virtual void First()
			{
				m_nCurrent = 0;
			}
			
			virtual void  Next()
			{
				++m_nCurrent;
			}

			virtual bool IsDone()
			{
				return m_nCurrent >= m_Vector->Size(); 
			}

			virtual int CurrentItem()
			{
				return m_Vector->Get(m_nCurrent);
			}
		protected:
			CVector* m_Vector;
			int m_nCurrent ;
		};
#pragma endregion


#pragma region		迭代器封装（保证迭代器对象能随栈释放）
			//对CVectorIterator的封装，保证释放成功
	class CVectorIteratorPtr
	{
	public:
		CVectorIteratorPtr(CVectorIterator *pVectorIterator) :m_VectorIterator(pVectorIterator)
		{

		}
		bool operator == (const CVectorIteratorPtr &rOther)
		{
			return *m_VectorIterator == *rOther.m_VectorIterator;
		}
		bool operator!=(const CVectorIteratorPtr &rOther)
		{
			return !(*this == rOther);
		}

		//前置++
		CVectorIteratorPtr& operator++()
		{
			++(*m_VectorIterator);
			return *this;
		}

		int operator*()
		{
			return *(*m_VectorIterator);
		}

		~CVectorIteratorPtr()
		{
			delete m_VectorIterator;
			m_VectorIterator = NULL;
		}
	private:
		CVectorIterator * m_VectorIterator;
	};
#pragma endregion




#pragma region 迭代器操作
	private:
		CIterator* Create()
		{
			return new CVectorIterator(this);
		}
	
	public:
		CVectorIteratorPtr Begin()
		{
			//创建子类对象
			CIterator* pBegin = Create();
			pBegin->First();
			//封装子类对象
			return CVectorIteratorPtr((CVectorIterator *)pBegin);
		}

		CVectorIteratorPtr End()
		{
			//创建子类对象
			CIterator *pEnd = Create();
			while (!pEnd->IsDone())
			{
				pEnd->Next();
			}
			//封装子类对象
			return CVectorIteratorPtr((CVectorIterator *)pEnd);
		}


#pragma endregion 

	private:
		size_t m_Size;
		size_t m_Capacity;
		T *m_Data;

	private:
		void _CheckCapacity(size_t needSize)
		{
			if(m_Capacity >= needSize)
			{
				return ;
			}
			else  
			{
				//realloc new space by the twice of the last
				m_Capacity =  needSize;
				T *pNewAlloc = new T[m_Capacity];
				if(m_Data)
				{
					//copy data
					for(int i=0;i<m_Size;++i)
					{
						pNewAlloc[i]=m_Data[i];
					}
					delete []m_Data;
				}
				m_Data = pNewAlloc;
			}
		}
	};
}
#endif