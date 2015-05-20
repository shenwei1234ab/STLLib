#include <iostream>
#include <stdlib.h>
#include "CList.h"
#include "CString.h"
#include "CVector.h"
#include "CBiSortTree.h"
#include "CAVL.h"
#include "CList.h"
#include	<list>
#include <vector>
using namespace MyLib;




void StringTest()
{
	CString s="test";
	std::cout<<s<<std::endl;
}

void Print(CBiSortTree<int >::BiTNode * &node)
{
	std::cout<< node->data<<std::endl;
}



void BiSortTreeTest()
{
	int array[]={50,80,58,47,35,51,99};
	CBiSortTree<int > mySortTree;
	mySortTree.Create(array,7);

	//测试，中续遍历
	mySortTree.OrderVisit(Print,MyLib::CBiSortTree<int>::visitType::MidVisit);
}
//void AVLTest()
//{
//	int array[]={50,80,58,47,35,51,99};
//	CAVL<int > mySortTree;
//	mySortTree.Create(array,7);
//
//	//测试，中续遍历
//	mySortTree.OrderVisit(Print2,MyLib::CAVL<int>::visitType::MidVisit);
//}


void ListTest()
{
	typedef CList<int> ints;
	ints mList;
	mList.Push_back(1);
	mList.Push_back(2);
	mList.Push_back(3);
	ints::CIterator itFirst = mList.Begin();
	//std::cout<<itFirst->data<<std::endl;

	//++itFirst;
	
	mList.Insert(itFirst,4);
	//测试迭代器
	for(ints::CIterator it=mList.Begin();it!=mList.End();++it)
	{
		std::cout<<*it<<std::endl;
	}
	
}




void IteratorTest()
{
	CVector<int > myList;
	myList.Push_back(2);
	myList.Push_back(3);
	myList.Push_back(4);
	for (CVector<int>::CVectorIteratorPtr it = myList.Begin(); it != myList.End(); ++it)
	{
		std::cout << *it << std::endl;
	}

	
	
}

void Print2(CAVL<int >::AVLNode * &node)
{
	std::cout<< node->sData.value<<std::endl;
}
void AVLTest()
{
	CAVL<int>::data dataArray[] = {{13,13},{24,24},{37,37},{90,90},{53,53}};
	CAVL<int> myTree;
	myTree.Create(dataArray,5);

	//mySortTree.OrderVisit(Print,MyLib::CBiSortTree<int>::visitType::MidVisit);
	myTree.OrderVisit(Print2,MyLib::CAVL<int>::visitType::MidVisit);
}
void main()
{
	AVLTest();
	system("pause");
}