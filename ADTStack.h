#pragma once
#include"ADTHelper.h"
ADTBEGIN
	namespace ADTStack		//Dynamic Array Based Stack
	{
#include<memory>
		ADTCLASSBEGIN(SqStack){
			std::unique_ptr<ElemType[]> base = nullptr;
			ElemType* top = nullptr;
			size_t StackSize = 0;
		};

		ADTFUNCBEGIN
		void InitStack(SqStack<ElemType>& S)
		{
			S.base = std::make_unique<ElemType[]>(ADTMAXSIZE);
			S.top = S.base.get();
		}

		ADTFUNCBEGIN
		void DestoryStack(SqStack<ElemType>& S)
		{
			S.top = nullptr;
			S.base.reset();
			S.StackSize = 0ull;
		}

		ADTFUNCBEGIN
		void ClearStack(SqStack<ElemType>& S)
		{
			DestoryStack(S);
			InitStack(S);
		}

		ADTFUNCBEGIN
		bool StackEmpty(SqStack<ElemType>& S)
		{
			return S.top == &(S.base[0]);
		}

		ADTFUNCBEGIN
		ElemType GetTop(SqStack<ElemType>& S)
		{
			return StackEmpty(S) ? ElemType{} : *(S.top - 1);
		}

		ADTFUNCBEGIN
		void PushStack(SqStack<ElemType>& S, const ElemType& e)
		{
			if (S.StackSize >= ADTMAXSIZE)return;
			++S.top;
			S.base[S.StackSize++] = e;
		}

		ADTFUNCBEGIN
		void PopStack(SqStack<ElemType>& S, ElemType& e)
		{
			if (StackEmpty(S))return;
			e = *(--S.top);
			S.base[--S.StackSize] = {};
		}

		ADTCALLFUNCBEGIN
		void StackTraverse(SqStack<ElemType>& S, Callable f)
		{
			auto p = S.base.get();
			while (p < S.top)
			{
				f(*p); ++p;
			}
		}
	}
ADTEND
