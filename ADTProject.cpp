#include<iostream>
#include<chrono>
#include"ADTDuexList.h"
#include"ADTList.h"
using namespace ADT::ADTDuexList;
using namespace ADT::ADTList;
int main()
{
	DuexList<int> L;
	List<int>L2;
	InitDuexList(L);
	InitList(L2);
	for (int i = 0; i < 10; i++)
	{
		DuexListInsert(L, 0, i);
		ListInsert(L2, 0, i);
	}
	for (int i = 0; i < 3; i++)
	{
		DuexListDelete(L, 1);
		ListDelete(L2, 1);
	}
	TranverseDuexList(L, [](auto v) {std::cout << v << '\n'; });
}