#pragma once
#include"ADTHelper.h"
ADTBEGIN
namespace ADTQueue	//ListQueue
{
#include<memory>

	ADTCLASSBEGIN(ListQueue)
	{
		ElemType data = {};
		std::unique_ptr<ListQueue>next = nullptr;
		ListQueue* near = nullptr;
		ListQueue* rear = nullptr;
	}ADTCLASSEND;

		ADTFUNCBEGIN
		void InitListQueue(ListQueue<ElemType>& Q)
		{
			Q.data = {};
			Q.next = nullptr;
			Q.near = &Q;
			Q.rear = Q.near;
		}

		ADTFUNCBEGIN
		void DestoryListQueue(ListQueue<ElemType>& Q)
		{
			Q.data = {};
			ListQueue<ElemType>* current = &Q;
			while (ListQueue<ElemType>*const pnext=current->next.get())
			{
				auto old_node = std::move(current->next);
				current->next = std::move(old_node->next);
			}
			Q.next.reset();
			Q.near = nullptr;
			Q.rear = Q.near;
		}

		ADTFUNCBEGIN
		void ClearListQueue(ListQueue<ElemType>& Q)
		{
			DestoryListQueue(Q);
			InitListQueue(Q);
		}

		ADTFUNCBEGIN
		bool ListQueueEmpty(ListQueue<ElemType>& Q)
		{
			return Q.near == Q.rear;
		}

		ADTFUNCBEGIN
		size_t ListQueueLength(ListQueue<ElemType>& Q)
		{
			size_t count = 0ull;
			auto current = &Q;
			while (ListQueue<ElemType>*const pnext=current->next.get())
			{
				current = pnext;
				count++;
			}
			return count;
		}

		ADTFUNCBEGIN
		ElemType GetHead(ListQueue<ElemType>& Q)
		{
			if (ListQueueEmpty(Q))return ElemType{};
			return Q->next->data;
		}

		ADTFUNCBEGIN
		bool EnQueue(ListQueue<ElemType>& Q, const ElemType& e)
		{
			std::unique_ptr<ListQueue<ElemType>> new_node = std::make_unique<ListQueue<ElemType>>(e);
			(Q.rear)->next = std::move(new_node);
			Q.rear = Q.rear->next.get();
			return true;
		}

		ADTFUNCBEGIN
		bool DeQueue(ListQueue<ElemType>& Q, ElemType& e) 
		{
			if (ListQueueEmpty(Q))return false;
			std::unique_ptr<ListQueue<ElemType>> old_node = std::move(Q.next);
			Q.near = old_node->next.get();
			Q.next = std::move(old_node->next);
			e = old_node->data;
			return true;
		}

		ADTCALLFUNCBEGIN
		void QueueTraverse(ListQueue<ElemType>& Q, Callable f)
		{
			ListQueue<ElemType>* current = &Q;
			while (ListQueue<ElemType>*const pnext=current->next.get())
			{
				current = pnext;
				f(current->data);
			}
		}
	}
ADTEND
