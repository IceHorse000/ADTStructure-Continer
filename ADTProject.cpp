#include<iostream>
#include<chrono>
#include"ADTCircleQueue.h"
using namespace ADT::ADTCircleQueue;
using namespace std;
int main()
{
	CircleQueue<int>Q;
	InitCircleQueue(Q);
	for (int i = 1; i < 15; i++)
		EnQueue(Q, i);
	int pad = 0;
	for (int i = 0; i < 5; i++)
		DeQueue(Q, pad);
	EnQueue(Q, pad);
	TranverseCircleQueue(Q, [](int e) {std::cout << e << '\n'; });
	std::cout << Q.near << " " << Q.rear << " " << Q.QueueSize << '\n';
	DestroyCircleQueue(Q);
}