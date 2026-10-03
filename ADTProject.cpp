#include<iostream>
#include<chrono>
#include"ADTStack.h"
using namespace std;
using namespace ADT::ADTStack;
int main()
{
	SqStack<int> S;
	InitSqStack(S);
	for (int i = 0; i < 10; i++)
		PushStack(S, i);
	TranverseSqStack(S, [](auto i) {std::cout << i << '\n'; });
	int pad = 0;
	for (int i = 0; i < 3; i++)
		PopStack(S, pad);
	TranverseSqStack(S, [](auto i) {std::cout << i << '\n'; });
}