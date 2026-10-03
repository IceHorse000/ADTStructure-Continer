#pragma once
#include"ADTHelper.h"
ADTBEGIN
namespace ADTList		//Forward List
{
#include<memory>
	ADTCLASSBEGIN(List){
		ElemType data = {};
	std::unique_ptr<List> next = nullptr;
	};

		ADTFUNCBEGIN
		void InitList(List<ElemType>&L) 
		{	
			L.data = {};
			L.next = nullptr;
		};

		ADTFUNCBEGIN
		void DestroyList(List<ElemType>& L)
		{
			auto current = &L;
			while (List<ElemType>* const pnext = current->next.get())
			{
				std::unique_ptr<List<ElemType>> old = std::move(current->next);
				current->next = std::move(old->next);
			}
		}

		ADTFUNCBEGIN
		void ClearList(List<ElemType>& L)
		{
			DestroyList(L);
			InitList(L);
		}

		ADTFUNCBEGIN
		bool ListEmpty(List<ElemType>& L) 
		{
			return L.next == nullptr;
		};

		ADTFUNCBEGIN
		size_t ListLength(List<ElemType> const& L)
		{
			auto current = &L;
			size_t len = 0;
			while (List<ElemType>* const pnext = current->next.get())
			{
				current = pnext; ++len;
			}
			return len;
		}

		ADTFUNCBEGIN
		bool GetElem(List<ElemType> const& L, size_t pos, ElemType& result)
		{
			size_t i = pos, j = 0ull;
			auto current = &L;
			List<ElemType>* pnext = current->next.get();
			while (pnext!=nullptr && j < i)
			{
				current = pnext;
				pnext = current->next.get();
				++j;
			}
			if (j == i)
			{
				result = current->data;
				return true;
			}
			else
			{
				result = {};
				return false;
			}
		}

		ADTFUNCBEGIN
		size_t LocateElem(List<ElemType> const& L, const ElemType& target)
		{
			auto current = &L;
			size_t pos = 0ull;
			while (List<ElemType>* const pnext=current->next.get())
			{
				current = pnext;
				++pos;
				if (current->data == target)
				{
					return pos;
				}
			}
			return 0ull;
		}

		ADTFUNCBEGIN
		bool PriorElem(List<ElemType>& L, const ElemType& cur_e, ElemType& pre_e)
		{
			size_t i = LocateElem(L, cur_e) - 1, j = 0ull;
			auto current = &L;
			List<ElemType>* pnext = current->next.get();
			while (pnext != nullptr && j < i)
			{
				current = pnext;
				pnext = current->next.get();
				++j;
			}
			if (j == i)
			{
				pre_e = current->data;
				return true;
			}
			return false;
		}

		ADTFUNCBEGIN
		bool NextElem(List<ElemType>& L, const ElemType& cur_e, ElemType& next_e)
		{
			auto current = const_cast<ADTPOINTER(List)>(&L);
			auto pnext = current;
			while (pnext = current->next.get())
			{
				current = pnext;
				if (current->data == cur_e)
				{
					next_e = current->next->data;
					return true;
				}
			}
			return false;
		}

		ADTFUNCBEGIN
		void ListInsert(List<ElemType>& L, size_t i, const ElemType& e)
		{
			size_t p = i - 1, j = 0ull;
			auto current = &L;
			List<ElemType>* pnext = current->next.get();
			while (pnext != nullptr && j < p)
			{
				current = pnext;
				pnext = current->next.get();
				++j;
			}
			std::unique_ptr<List<ElemType>> new_node(new List<ElemType>(e,nullptr));
			if (pnext)
			{
				new_node->next = std::move(current->next);
			}
			else
			{
				new_node->next = nullptr;
			}
			current->next = std::move(new_node);
		}

		ADTFUNCBEGIN
		void DeleteList(List<ElemType>& L, size_t pos)
		{
			if (pos > ListLength(L))return;
			size_t p = pos - 1, j = 0ull;
			auto current = &L;
			List<ElemType>* pnext = current->next.get();
			while (pnext != nullptr && j < p)
			{
				current = pnext;
				pnext = current->next.get();
				++j;
			}
			auto old_node = std::move(current->next);
			current->next = std::move(old_node->next);
		}

		template<typename ElemType,typename Callable>
		void TraverseList(List<ElemType>& L, Callable f)
		{
			auto current = &L;
			while (List<ElemType>*const pnext=current->next.get())
			{
				current = pnext; f(current->data);
			}
		}

		template<typename ElemType, typename Predicate = std::less<ElemType>>	
		//Onplace Sort
		void SortList(List<ElemType>& L, Predicate comp = Predicate())
		{
			if (ListEmpty(L) || L.next->next == nullptr)return;
			auto sorted = std::make_unique<List<ElemType>>();
			while (L.next)
			{
				auto node = std::move(L.next);
				auto prev = sorted.get();
				L.next = std::move(node->next);
				while (prev->next!= nullptr && comp(node->data, prev->next->data))
				{
					prev = prev->next.get();
				}
				node->next = std::move(prev->next);
				prev->next = std::move(node);
			}
			L.next = std::move(sorted->next);
		}
	}
ADTEND