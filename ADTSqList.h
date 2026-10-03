#pragma once
#include"ADTHelper.h"
ADTBEGIN
	namespace ADTSqList		//Dynamic Array?
	{
#include<memory>
		ADTCLASSBEGIN(SqList) {
			std::unique_ptr<ElemType[]> elem = nullptr;
			size_t Length = 0ull;
		}
		ADTCLASSEND

		ADTFUNCBEGIN
		void InitSqList(SqList<ElemType>& L)
		{
			L.elem = std::make_unique<ElemType[]>(ADTMAXSIZE);
		}

		ADTFUNCBEGIN
		void DestorySqList(SqList<ElemType>& L)
		{
			L.elem.reset();
			L.Length = 0ull;
		}

		ADTFUNCBEGIN
		void ClearSqList(SqList<ElemType>& L)
		{
			L.Length = 0;
		}

		ADTFUNCBEGIN
		bool SqListEmpty(SqList<ElemType>& L)
		{
			return L.Length == 0;
		}

		ADTFUNCBEGIN
		size_t SqListLength(SqList<ElemType> const& L)
		{
			return L.Length;
		}

		ADTFUNCBEGIN
		bool GetSqElem(SqList<ElemType> const& L, size_t i, ElemType& e)
		{
			if (i > L.Length)return false;
			e = L[i - 1];
			return true;
		}

		ADTFUNCBEGIN
		size_t LocateSqElem(SqList<ElemType> const& L, ElemType const& target)
		{
			for (size_t i = 0ull; i < L.Length; i++)
			{
				if (L.elem[i] == target)
					return i + 1;
			}
			return 0ull;
		}

		ADTFUNCBEGIN
		void PriorSqElem(SqList<ElemType> const& L, ElemType const& cur_e, ElemType& pre_e)
		{
			auto cur_p = LocateSqElem(L, cur_e);
			if (!cur_p)return;
			pre_e = L.elem[cur_p - 2];
		}

		ADTFUNCBEGIN
		bool NextSqElem(SqList<ElemType> const& L, ElemType const& cur_e, ElemType& next_e)
		{
			auto cur_p = LocateSqElem(L, cur_e);
			if (!cur_p)return false;
			next_e = L.elem[cur_p];
			return true;
		}

		ADTFUNCBEGIN
		bool SqListInsert(SqList<ElemType>& L, size_t i, ElemType const& e)
		{
			if (i > L.Length && i < ADTMAXSIZE)
			{
				L.elem[L.Length++] = e;
				return true;
			}
			else if (i >= ADTMAXSIZE)return false;
			else if (L.Length + 1 >= ADTMAXSIZE)return false;
			for (size_t p = L.Length; p >=i; p--)
			{
				L.elem[p] = L.elem[p - 1];
			}
			L.Length++;
			L.elem[i - 1] = e;
			return true;
		}

		ADTFUNCBEGIN
		void DeleteSqElem(SqList<ElemType>& L, size_t i) 
		{
			if (i > L.Length || i >= ADTMAXSIZE)return;
			for (size_t p = i - 1; p < L.Length; p++)
			{
				L.elem[p] = L.elem[p + 1];
			}
			L.elem[--L.Length] = {};
		};

		ADTCALLFUNCBEGIN
		void TraverseSqList(SqList<ElemType>& L, Callable f)
		{
			for (size_t i = 0; i < L.Length; i++)
			{
				f(L.elem[i]);
			}
		}

		ADTSORTBEGIN
		void SortSqList(SqList<ElemType>& L, size_t begin, size_t end,
			Predicate comp = Predicate())
		{
			if (begin == end || end - begin == 1) return;
			size_t i = begin;
			size_t j = end;
			size_t mid = (begin + end) / 2;
			ElemType poviet = L.elem[mid];
			while (i < j)
			{
				while (comp(L.elem[i], poviet))i++;
				while (comp(poviet, L.elem[j]))j--;
				if (i == j)
					break;
				ElemType temp = L.elem[i];
				L.elem[i] = L.elem[j];
				L.elem[j] = temp;
			}
			
			SortSqList(L, begin, i, comp);
			SortSqList(L, i + 1, end, comp);
		}
	}
ADTEND

