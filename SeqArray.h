#pragma once
#include "Sequence.h"
#include <iostream>
#include <cstdlib>
/*
 *You need to complete the implementation of the AST sequence using Arrays. This is an incomplete implementation. 
 */
class SeqArray :  public Sequence
{
private:
	int swap(int i, int j);
	int* array;
	int asize; //acutal size in memory. larger than len to keep buffer.
	int numswaps=0;
	int numcompare=0;
public:
	int len;//len of array to show to users.


	SeqArray();
	SeqArray(int size);
	SeqArray(const SeqArray& rhs);
	~SeqArray();
	void operator = (const SeqArray& rhs);
	void fillrandom();
	void printall();
	void sortbubble();
	void sortselection();
	void sortinsertion();
	//--Getter Functions--//
	/* Don't want the user of this class to access or manipulate numswaps or numcompare. */
	int getswaps();
	int getcompares();

	void insert(int);
	void insert(int, int);
	void insertFirst(int);
	void remove(int);
	void remove(int, int);
	void removeFirst();
	
	void sort();
	void benchmarkBubble(int len, int iterations);
	void benchmarkInsertion(int len, int iterations);
	void benchmarkSelection(int len, int iterations);
};
