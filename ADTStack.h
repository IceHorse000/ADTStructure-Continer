#pragma once
#ifndef STACK
#define STACK
#endif // !STACK

#include"ADTHelper.h"
ADTBEGIN
	ADTSUBBEGIN(Stack)		//Dynamic Array Based Stack
		ADTCLASSBEGIN(SqStack){
			ADTARRATTYPE base = nullptr;
			ARGTYPE* top = nullptr;
			size_t StackSize = 0;
		};

		ADTFUNCBEGIN
		ASSIGNINIT(SqStack, S)
		{
			S.base = std::make_unique<ElemType[]>(ADTMAXSIZE);
			S.top = S.base.get();
		}ADTFUNCEND;

		ADTFUNCBEGIN
		ASSIGNDESTORY(SqStack, S)
		{
			S.top = nullptr;
			S.base.reset();
			S.StackSize = 0ull;
		}ADTFUNCEND;

		ADTFUNCBEGIN
		ASSIGNCLEAR(SqStack, S)
		{
			DestroySqStack(S);
			InitSqStack(S);
		}ADTFUNCEND;

		ADTFUNCBEGIN
		ASSIGNEMPTY(SqStack, S)
		{
			return S.top == &(S.base[0]);
		}ADTFUNCEND

		ADTFUNCBEGIN
		ASSIGNTOP(SqStack,S)
		{
			return SqStackEmpty(S) ? ElemType{} : *(S.top - 1);
		}

		ADTFUNCBEGIN
		ASSIGNPUSH(SqStack,S,ein)
		{
			if (S.StackSize >= ADTMAXSIZE)return false;
			++S.top;
			S.base[S.StackSize++] = ein;
			return true;
		}

		ADTFUNCBEGIN
		ASSIGNPOP(SqStack,S,e)
		{
			if (SqStackEmpty(S))return false;
			e = *(--S.top);
			S.base[--S.StackSize] = {};
			return true;
		}

		ADTCALLFUNCBEGIN
		ASSIGNTRANVERSE(SqStack, S, f)
		{
			auto p = S.base.get();
			while (p < S.top)
			{
				f(*p); ++p;
			}
		}
ADTSUBEND;
ADTEND
