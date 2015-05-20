#ifndef _CBISORT_TREE_H
#define _CBISORT_TREE_H
#include <functional>
namespace MyLib
{
	/*
		Binary Search Tree
		Author by WeiShen At 2015.4.2
	*/
	template<class T>
	class CBiSortTree
	{
	public:
		struct BiTNode
		{
			BiTNode(T data):data(data),pLChild(NULL),pRChild(NULL)
			{

			}
			BiTNode():data(0),pLChild(NULL),pRChild(NULL)
			{

			}
			T data;
			BiTNode *pLChild;
			BiTNode *pRChild;
		};

		enum visitType
		{
			PreVisit,
			MidVisit,
			PosVisit
		};

		CBiSortTree():m_Root(NULL)
		{

		}



		virtual ~CBiSortTree()
		{
			//posvisit and free the space
			if(m_Root)
			{
				//bind the member function
				std::function<void (BiTNode * &)> funDelete=std::bind(&CBiSortTree::_FreeSpace,this,std::placeholders::_1);
				OrderVisit(funDelete,visitType::PosVisit);
			}
		}
	
		
			/*
		function:search the key from the tree
		ret:if found the node having the same key  then return it ,else return NULL;
		*/
		BiTNode * Search(BiTNode *pRoot,T key)
		{
			if(NULL == pRoot)
			{
				return NULL;
			}
			if( pRoot->data == key )
			{
				return pRoot;
			}
			else if (pRoot->data > key)
			{
				return Search(pRoot->pLChild);
			}
			else
			{
				return Search(pRoot->pRChild);
			}
		}



		/*
		function:search the key from the tree(prepare for the insert function)
		ret:if found key then return true,else return false;
		para1:tree's root node
		para2:key 
		para3:always keep the point to the parent of the last searched node(keep the value),initial value is NULL
		para4:outPut parame.
			  if found point to the position of the node.
			  else point to the last serached node 
		*/
		bool Search(BiTNode *pRoot,T key,BiTNode *pParent,BiTNode * &pOut)
		{
			//reache the leaf Node (Not found)
			if( NULL == pRoot)
			{
				//return the last visited node(insert function want it)
				pOut = pParent;
				return false;
			}
			else if ( pRoot->data == key )
			{
				pOut = pRoot;
				return true;
			}
			else if( key < pRoot->data )
			{
				return Search(pRoot->pLChild,key,pRoot,pOut);
			}
			else if (  key > pRoot->data )
			{
				return Search(pRoot->pRChild,key,pRoot,pOut);
			}
		}


		virtual void Insert(BiTNode * &pRoot,T key)
		{
			// found whether a node has the key?
			BiTNode *pInsertPos =NULL;
			//found
			if( Search(pRoot,key,NULL,pInsertPos))
			{
				//change the lase value
				pInsertPos->data = key;
			}
			//not found
			else
			{
				//create a new node
				BiTNode *pNewNode = new BiTNode(key);
				//if pNewNode is a new root node
				if( !pInsertPos)
				{
					//change the point of pRoot(only commit once in creating Tree )
					pRoot = pNewNode;
				}
				else if( pInsertPos->data >  key )
				{
					pInsertPos->pLChild = pNewNode;
				}
				else
				{
					pInsertPos->pRChild = pNewNode;
				}
			}
		}
		
		

		bool DeleteBST(BiTNode * &pRoot,T key)
		{
			if( NULL == pRoot )
			{
				return false;
			}
			else
			{
				//find the value
				if( key == pRoot->data)
				{
					return Delete(pRoot);
				}
				else if( key < pRoot->data )
				{
					return DeleteBST(pRoot->pLChild,key);
				}
				else if (  key > pRoot->data )
				{
					return DeleteBST(pRoot->pRChild,key);
				}
			}
		}

		//para1:pRoot's father's point to the pRoot itself
		bool Delete(BiTNode * &pRoot)
		{
			//only has left child
			if( NULL == pRoot->pRChild)
			{
				BiTNode *pDelete = pRoot;
				pRoot = pRoot->pLChild;
				delete(pDelete);
			}
			else if( NULL == pRoot->pRChild)
			{
				BiTNode *pDelete = pRoot;
				pRoot = pRoot->pRChild;
				delete(pDelete);
			}
			else	//both have left and right child
			{

				//find the node with max value from left subtree(or find the node with min value from right subtree )
				
				BiTNode *pMax = pRoot->pLChild;		//keep the node with max value
				BiTNode *pMaxParent = pRoot;		//keep the parent of pmax		
				//turn left 
				while(pMax->pRChild)
				{
					pMaxParent=pMax;
					pMax=pMax->pRChild;								//find the node with max value
				}
				//s:记录最大的节点
				//q:s的父节点
				pRoot->data = pMax->data;
				if(q!=p)
				{
					//rebuild q's left righttree
					pMaxParent->pRChild = pMax->pLChild;
				}
				else 
				{
					//rebuid q's left subtree
					pMaxParent->pLChild = pMax->pLChild;
				}
				delete pMax;
			}
		}


		void OrderVisit(std::function<void(BiTNode * &)> pFun,visitType vType)
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



		void  Create(T keyArray[],int n)
		{
			for(int i=0;i<n;++i)
			{
				Insert(m_Root,keyArray[i]);
			}
		}

#pragma region	迭代器
	

#pragma endregion
	private:
		BiTNode* m_Root;
		
	private:
		//Intern Function
		void _PreVisit(BiTNode *pRoot,std::function<void(BiTNode * &)> pFun)
		{
			if( NULL == pRoot)
			{
				return ;
			}
			pFun(pRoot);
			_PreVisit(pRoot->pLChild,pFun);
			_PreVisit(pRoot->pRChild,pFun);
		}


		void _MidVisit(BiTNode *pRoot,std::function<void(BiTNode * &)> pFun)
		{
			if( NULL == pRoot)
			{
				return ;
			}
			
			_MidVisit(pRoot->pLChild,pFun);
			pFun(pRoot);
			_MidVisit(pRoot->pRChild,pFun);
		}

		void _PosVisit(BiTNode *pRoot,std::function<void(BiTNode * &)> pFun)
		{
			if( NULL == pRoot)
			{
				return ;
			}
			_PosVisit(pRoot->pLChild,pFun);
			_PosVisit(pRoot->pRChild,pFun);
			pFun(pRoot);
		}


		void _FreeSpace(BiTNode * &pNode)
		{
			if(pNode)
			{
				delete pNode;
				pNode = NULL;
			}
		}
	};
}
    
#endif