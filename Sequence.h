#pragma once
using namespace std;

class Sequence
{
public:
	//--Uncomment and implement all the below functions in your abstract classess--//
	virtual void insert(int) = 0;
	virtual void insert(int, int) = 0;
	virtual void insertFirst(int) = 0;

	virtual void remove(int) = 0;
	virtual void remove(int, int) = 0;
	virtual void removeFirst() = 0;

	virtual void sort() = 0;

	//--Optional you may or may not use this--//
	const int SUCCESS = 1;
	const int ERROR = 0;

};