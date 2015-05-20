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
				//左左：右旋
				pRoot->bf = EH;
				pLChild->bf = EH;
				R_Rotate(pRoot);
				break;	
			case RH:	
				//左右：双旋
				AVLNode *rd = pLChild->pRChild;
				//先修改旋转后的bf值
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
				//右右,左旋
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
				//找到
				if( pRoot->sData.key == sData.key )
				{
					taller = false;
					return false;
				}
				//在左孩子找插入位置
				if( pRoot->sData.key > sData.key )
				{
					//如果找到相同的
					if(!InsertAVL( pRoot->pLChild,sData,taller ))
					{					
						return false;
					}
					//从插入点向父节点返回
					if( taller )
					{
						switch( pRoot->bf)
						{
						//如果父节点原来度是1，那么现在树长高了说明现在度是2,要做旋转调整 
						case LH:
							LeftBalance(pRoot);
							taller = false;
							break;
						//如果父节点原来度是0，那么现在树长高了说明现在度是1
						case EH:
							pRoot->bf = LH;
							taller = true;
							break;
						//如果父节点原来度是-1，那么现在树长高了说明现在度是0
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