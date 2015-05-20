#ifndef _CAVL_H_
#define _CAVL_H_
#include "CBiSortTree.h"
#define LH 1
#define EH 0
#define RH -1
namespace MyLib
{
	template<class T>
	class CAVL
	{
	public:

		enum visitType
		{
			PreVisit,
			MidVisit,
			PosVisit
		};
		struct data
		{
			T key;
			T value;
		};
		struct AVLNode
		{
			data sData;
			AVLNode *pLChild;
			AVLNode *pRChild;
			int bf;		//balance factor
		};

		CAVL():m_Root(NULL)
		{

		}


		~CAVL()
		{

		}
		
		void R_Rotate(AVLNode * &pRoot)		//rotate by clockwise
		{
			// point to pRoot's left sub child
			AVLNode *pLChild = pRoot->pLChild;
			
			//L's right child connect to root's left child
			pRoot->pLChild = pLChild->pRChild;


			pLChild->pRChild = pRoot;

			//pRoot point to new root
			pRoot = pLChild;

		}


		void L_Rotate(AVLNode * &pRoot)		//rotate by anti-clockwise
		{
			AVLNode *pRChild =pRoot->pRChild;

			pRoot->pRChild = pRChild->pLChild;

			pRChild->pLChild = pRoot;

			pRoot = pRChild;
		}



		
		void LeftBalance(AVLNode * &pRoot)
		{
			AVLNode *pLChild = pRoot->pLChild;
			switch( pLChild->bf )
			{	
			case LH:
				//��������
				pRoot->bf = EH;
				pLChild->bf = EH;
				R_Rotate(pRoot);
				break;	
			case RH:	
				//���ң�˫��
				AVLNode *rd = pLChild->pRChild;
				//���޸���ת���bfֵ
				switch(rd->bf)
				{
				case LH:
					pRoot->bf = RH;
					pLChild->bf = EH;
					break;
				case EH:
					pRoot->bf = EH;
					pLChild->bf=EH;
					break;
				case RH:
					pRoot->bf = EH;
					pLChild->bf = LH;
					break;
				}
				rd->bf = EH;
				L_Rotate(pRoot->pLChild);
				R_Rotate(pRoot);
			}
		}


		void RightBalance(AVLNode * &pRoot)
		{
			AVLNode *pRChild = pRoot->pRChild;
			switch(pRChild->bf)
			{
			case RH:
				//����,����
				pRoot->bf = EH;
				pRChild->bf = EH;
				L_Rotate(pRoot);
				break;
			case LH:
				AVLNode *ld = pRChild->pLChild;
				switch(ld->bf)
				{
				case LH:
					pRoot->bf = EH;
					pRChild->bf = RH;
					break;
				case EH:
					pRoot->bf = EH;
					pRChild->bf=EH;
					break;
				case RH:
					pRoot->bf = LH;
					pRChild->bf = EH;
					break;
				}
				ld->bf = EH;
				R_Rotate(pRoot->pRChild);
				L_Rotate(pRoot);
			}
		}


		bool InsertAVL(AVLNode * &pRoot,data sData,bool &taller)
		{
			if( NULL == pRoot)
			{
				pRoot = new AVLNode;
				pRoot->sData = sData;
				pRoot->pLChild = NULL;
				pRoot->pRChild = NULL;
				pRoot->bf = EH;
				taller = true;
			}
			else
			{
				//�ҵ�
				if( pRoot->sData.key == sData.key )
				{
					taller = false;
					return false;
				}
				//�������Ҳ���λ��
				if( pRoot->sData.key > sData.key )
				{
					//����ҵ���ͬ��
					if(!InsertAVL( pRoot->pLChild,sData,taller ))
					{					
						return false;
					}
					//�Ӳ�����򸸽ڵ㷵��
					if( taller )
					{
						switch( pRoot->bf)
						{
						//������ڵ�ԭ������1����ô������������˵�����ڶ���2,Ҫ����ת���� 
						case LH:
							LeftBalance(pRoot);
							taller = false;
							break;
						//������ڵ�ԭ������0����ô������������˵�����ڶ���1
						case EH:
							pRoot->bf = LH;
							taller = true;
							break;
						//������ڵ�ԭ������-1����ô������������˵�����ڶ���0
						case RH:
							pRoot->bf = EH;
							taller = false;
							break;
						}
					}
				}
				else//find in the right subchildren
				{
					if(!InsertAVL( pRoot->pRChild,sData,taller ))
					{
						return false;
					}
					//if insert to the right subchild of the pRoot and make the right subtree taller
					if(taller)
					{
						switch( pRoot->bf)
						{
						case LH:
							pRoot->bf = EH;
							taller = false;
							break;
						case EH:
							pRoot->bf = RH;
							taller = true;
							break;
						case RH:
							RightBalance(pRoot);
							taller = false;
							break;
						}
					}
				}
			}
			return true;
		}



		//void  Create(T keyArray[],int n)
		//{
		//	for(int i=0;i<n;++i)
		//	{
		//		bool tailer;
		//		AVLNode avlNode;
		//		avlNode.sData.data = keyArray[i];
		//		InsertAVL(m_Root,avlNode,&tailer);
		//	}
		//}

		void Create(data keyValueArray[],int n)
		{
			for(int i=0;i<n;++i)
			{
				bool taller;
				InsertAVL(m_Root,keyValueArray[i],taller);
			}
		}


		void OrderVisit(std::function<void(AVLNode * &)> pFun,visitType vType)
		{
			if(NULL == m_Root)
			{
				return ;
			}
			switch(vType)
			{
			case visitType::PreVisit:
				_PreVisit(m_Root,pFun);
				break;
			case visitType::MidVisit:
				_MidVisit(m_Root,pFun);
				break;
			case visitType::PosVisit:
				_PosVisit(m_Root,pFun);
				break;
			}
		}
	private:
		AVLNode *m_Root;

		//Intern Function
		void _PreVisit(AVLNode *pRoot,std::function<void(AVLNode * &)> pFun)
		{
			if( NULL == pRoot)
			{
				return ;
			}
			pFun(pRoot);
			_PreVisit(pRoot->pLChild,pFun);
			_PreVisit(pRoot->pRChild,pFun);
		}


		void _MidVisit(AVLNode *pRoot,std::function<void(AVLNode * &)> pFun)
		{
			if( NULL == pRoot)
			{
				return ;
			}
			
			_MidVisit(pRoot->pLChild,pFun);
			pFun(pRoot);
			_MidVisit(pRoot->pRChild,pFun);
		}

		void _PosVisit(AVLNode *pRoot,std::function<void(AVLNode * &)> pFun)
		{
			if( NULL == pRoot)
			{
				return ;
			}
			_PosVisit(pRoot->pLChild,pFun);
			_PosVisit(pRoot->pRChild,pFun);
			pFun(pRoot);
		}
		
	};
}
#endif