#pragma once
#ifndef QUEUE
#define QUEUE
#endif // !QUEUE

#include"ADTHelper.h"

ADTBEGIN
ADTSUBBEGIN(CircleQueue)
ADTCLASSBEGIN(CircleQueue)
{
	ADTARRATTYPE _data;
	size_t rear = 0, near = 0;
	size_t QueueSize = 0;
}ADTCLASSEND;

ADTFUNCBEGIN
ASSIGNINIT(CircleQueue, Q)
{
	Q._data = std::make_unique<ARGTYPE[]>(ADTMAXSIZE);
	Q.rear = 0; Q.near = 0;
	Q.QueueSize = 0;
}ADTFUNCEND;

ADTFUNCBEGIN
ASSIGNDESTORY(CircleQueue, Q)
{
	Q._data.reset();
	Q.rear = 0; Q.near = 0;
	Q.QueueSize = 0;
}ADTFUNCEND

ADTFUNCBEGIN
ASSIGNCLEAR(CircleQueue, Q)
{
	DestroyCircleQueue(Q);
	InitCircleQueue(Q);

}ADTFUNCEND

ADTFUNCBEGIN
ASSIGNEMPTY(CircleQueue, Q)
{
	return Q.QueueSize == 0;
}ADTFUNCEND

ADTFUNCBEGIN
ASSIGNLENGTH(CircleQueue, Q)
{
	return Q.QueueSize;
}ADTFUNCEND

ADTFUNCBEGIN
ASSIGNENQUEUE(CircleQueue, Q, ein)
{
	auto pos = Q.rear;
	if (Q._data[pos] == ARGTYPE{})
	{
		Q._data[pos] = ein;
		++Q.QueueSize;
		Q.rear = ++Q.rear % ADTMAXSIZE;
		return true;
	}
	return false;
}ADTFUNCEND

ADTFUNCBEGIN
ASSIGNDEQUEUE(CircleQueue, Q, eout)
{
	if (CircleQueueEmpty(Q))
		return false;
	auto pos = Q.near;
	--Q.QueueSize;
	eout = Q._data[pos];
	Q._data[pos] = {};
	Q.near = ++Q.near % ADTMAXSIZE;
	return true;
}ADTFUNCEND

ADTCALLFUNCBEGIN
ASSIGNTRANVERSE(CircleQueue, Q, f)
{
	size_t curr = Q.near; size_t count = 0;
	while (count<Q.QueueSize)
	{
		f(Q._data[(curr+count)%ADTMAXSIZE]);
		++count;
	}
}ADTCALLFUNCEND

ADTSUBEND
ADTEND