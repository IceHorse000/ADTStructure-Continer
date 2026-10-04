#pragma once
#ifndef LIST
#define LIST
#endif // !LIST

#include"ADTHelper.h"

ADTBEGIN
	ADTSUBBEGIN(DuexList)
	ADTCLASSBEGIN(DuexList) 
	{
		ElemType _data = {};
		ADTWARPPERPOINTER(DuexList) next = nullptr;
		ADTPOINTER(DuexList) prev = nullptr;
	}
	ADTCLASSEND

	ADTFUNCBEGIN
	ASSIGNINIT(DuexList,D)
	{
		D._data = {};
		D.next.reset();
		D.prev = nullptr;
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNDESTORY(DuexList,D)
	{
		ADTPOINTER(DuexList) current = &D;
		while (ADTCONSTPOINTER(DuexList)pnext=current->next.get())
		{
			ADTWARPPERPOINTER(DuexList) old_node = std::move(current->next);
			current->next = std::move(old_node->next);
		}
		current->next.reset();
		current->_data = {};
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNCLEAR(DuexList,D)
	{
		ADTPOINTER(DuexList) current = &D;
		while (ADTCONSTPOINTER(DuexList)pnext = current->next.get())
		{
			current = pnext;
			current->_data = {};
		}
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNEMPTY(DuexList,D)
	{
		return D.next == nullptr;
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNLENGTH(DuexList,D)
	{
		size_t l = 0;
		ADTPOINTER(DuexList) curr = const_cast<ADTPOINTER(DuexList)>(&D);
		ADTPOINTER(DuexList)pnext = nullptr;
		while (pnext=curr->next.get())
		{
			l++;
			curr = pnext;
		}
		return l;
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNGETELEM(DuexList,D,pos,e)
	{
		size_t p = 0;
		ADTPOINTER(DuexList) curr = const_cast<ADTPOINTER(DuexList)>(&D);
		ADTPOINTER(DuexList)pnext = curr->next.get();
		while ((pnext = curr->next.get()) && p < pos)
		{
			p++;
			curr = pnext;
		}
		if(p<pos)
		{
			e = {};
			return false;
		}
		else
		{
			e = curr->_data;
			return true;
		}
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNLOCATE(DuexList,D,e) 
	{
		size_t p = 0;
		ADTPOINTER(DuexList) curr = const_cast<ADTPOINTER(DuexList)>(&D);
		ADTPOINTER(DuexList)pnext = curr->next.get();
		while (pnext = curr->next.get())
		{
			if (curr->_data == e)
			{
				return p;
			}
			else
			{
				p++;
				curr = pnext;
			}
		}
		return 0;
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNPRIORELEM(DuexList, D, ein, eout)
	{
		auto p = LocateElem(D,ein);
		if (p == 0) 
		{
			eout = {};
			return false;
		}
		size_t i = 0;
		ADTPOINTER(DuexList) curr = const_cast<ADTPOINTER(DuexList)>(&D);
		ADTPOINTER(DuexList)pnext = nullptr;
		while ((pnext = curr->next.get()) && i < p)
		{
			i++;
			curr = pnext;
		}
		eout = curr->prev->_data;
		return true;
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNNEXTELEM(DuexList, D, ein, eout)
	{
		auto p = LocateElem(D,ein);
		if (p == 0)
		{
			eout = {};
			return false;
		}
		size_t i = 0;
		ADTPOINTER(DuexList) curr = const_cast<ADTPOINTER(DuexList)>(&D);
		ADTPOINTER(DuexList)pnext = nullptr;
		while ((pnext = curr->next.get()) && i < p)
		{
			i++;
			curr = pnext;
		}
		eout = curr->next->_data;
		return true;
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNINSERT(DuexList, D, pos, ein) 
	{
		size_t i = 0;
		ADTPOINTER(DuexList) curr = &D;
		ADTPOINTER(DuexList) pnext = nullptr;
		while ((pnext = curr->next.get()) && i < pos - 1)
		{
			curr = pnext;
			i++;
		}
		if (i < pos)return false;
		auto new_node = std::make_unique<ADTTYPE(DuexList)>(ein);
		if (curr->next == nullptr)
		{
			new_node->next = nullptr;
			new_node->prev = curr;
		}
		else
		{
			new_node->next = std::move(curr->next);
			new_node->prev = curr;
		}
		curr->next = std::move(new_node);
		if (curr->next->next != nullptr)
			curr->next->next->prev = curr->next.get();
		return true;
	}
	ADTFUNCEND;

	ADTFUNCBEGIN
	ASSIGNDELETE(DuexList, D, pos)
	{
		size_t i = 0;
		ADTPOINTER(DuexList) curr = &D;
		ADTPOINTER(DuexList) pnext = nullptr;
		while ((pnext = curr->next.get()) && i < pos - 1)
		{
			curr = pnext;
			i++;
		}
		if (i < pos - 1)return false;
		auto old_node = std::move(curr->next);
		if (old_node == nullptr)return false;
		curr->next = std::move(old_node->next);
		curr->next->prev = curr;
		return true;
	}
	ADTFUNCEND;

	ADTCALLFUNCBEGIN
		ASSIGNTRANVERSE(DuexList,D,f)
	{
		auto curr = &D;
		while (ADTPOINTER(DuexList)pnext=curr->next.get())
		{
			curr = pnext;
			f(curr->_data);
		}
	}
	ADTFUNCEND;

	ADTSUBEND
ADTEND;