#include <cstdlib>
#include <chrono>
#include<iostream>
#include "SeqArray.h"
#include "Sequence.h"
using namespace chrono;

int SeqArray::swap(int i, int j) {
    numswaps++;
    //if (i >= len || j >= len || i < 0 || j < 0) return -99;
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
    return 1;
}

SeqArray::SeqArray() {
    len = 0; asize = 0;
    array = nullptr;
}

SeqArray::SeqArray(int size) {
    len = size;
    asize = size * size;
    array = new int[asize];
    for (int i = 0; i < asize; i++) {
        array[i] = 0;
    }
}

SeqArray::~SeqArray()
{
    delete[] array;
}

SeqArray::SeqArray(const SeqArray& rhs) {
    len = rhs.len;
    asize = rhs.asize;
    array = new int[asize];
    if(len < asize)
    for (int i = 1; i < len; i++) {
            array[i] = rhs.array[i];
    }
}

void SeqArray::fillrandom() {
    srand(2345154798);
    for (int i = 0; i < len; i++) {
        array[i] = rand() % 10000;
    }
}

void SeqArray::printall() {
    char* buffer = new char[len * 4];
    for (int i = 0; i < len - 1; i++) {
        cout << array[i] << ", ";
    }
    cout << array[len - 1] << ".\n" << endl;
}

void SeqArray::operator=(const SeqArray& rhs) {
    if (asize != rhs.asize) {
        delete array;
        len = rhs.len;
        asize = rhs.asize;
        array = new int[asize];
    }
    for (int i = 1; i < len; i++) {
        array[i] = rhs.array[i];
    }
}

void SeqArray::sortbubble() {
    numswaps = 0; numcompare = 0;
    bool isSorted = false;
    int i = 0, len_1 = len - 1;
    while (!isSorted) {
        isSorted = true; //assume true until disproven
        for (int j = 0; j < len_1 - i; j++) {
            if (array[j] > array[j + 1]) {
                numcompare++;
                isSorted = false;
                swap(j + 1, j);
            }
        }
        ++i;
    }
}

void SeqArray::sortselection() {
    numswaps = 0; numcompare = 0;
    int minIndex = 0;
    for (int j = 0; j < len; j++) {
        for (int i = j; i < len; i++) {
            if (array[minIndex] > array[i]) {
                numcompare++;
                minIndex = i;
            }
        }
        swap(j, minIndex);
    }
}


void SeqArray::sortinsertion() {
    numswaps = 0; numcompare = 0;
    for (int i = 1; i < len; i++) {
        int j = i;
        int key = array[i];
        while (key < array[j - 1] && j>0) {
            numcompare++;
            array[j] = array[j - 1];
            --j;
            numswaps++;
        }
        array[j] = key; numswaps++;
    }
}

int SeqArray::getswaps() {
    return numswaps;
}

int SeqArray::getcompares() {
    return numcompare;
}

void SeqArray::insert(int data){
	static int count = 0;
	if(count != len){
		array[count++] = data;
	}
}

void SeqArray::insert(int index, int data){
	if(index > len){
		cout<<"Wrong entry"<<endl;
		exit(1);			 
	}
	int * arr = new int[len+1];
	for(int i = 0; i < index; i++){
		arr[i] = array[i];
	}
	arr[index] = data;
	int k = index+1;
	for(int i = index; i < len; i++){
		arr[k] = array[i];
        k++;
	}
	len = len+1;
	array = arr;
}
void SeqArray::insertFirst(int a){
    if (len < asize) {
        for (int i = len; i > 0; i--) {
            array[i] = array[i - 1];
        }
        array[0] = a;
        len++;
    } else {
        int * new_array = new int[len+1];
        new_array[0] = a;
        for(int i = 1; i < len+1; i++){
        	new_array[i] = array[i];
		}
		len = len+1; 
    }

}
void SeqArray::remove(int data){
    int indexToRemove = -1;
    
    for (int i = 0; i < len; i++) {
        if (array[i] == data) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        for (int i = indexToRemove; i < len - 1; i++) {
            array[i] = array[i + 1];
        }
        len--;
    } else {
        cout<<"Wrong data provided"<<endl;
        exit(1);
    }

}
void SeqArray::remove(int s_index, int e_index){
    if (s_index < 0 || s_index >= len || e_index < 0 || e_index >= len || s_index > e_index) {
        return;
    }

    int elementsToRemove = e_index - s_index + 1;
    for (int i = s_index; i < len - elementsToRemove; i++) {
        array[i] = array[i + elementsToRemove];
    }

    len -= elementsToRemove;
}
void SeqArray::removeFirst(){
	for(int i = 0; i < len-1; i++){
		array[i] = array[i+1];
	}
	len--;
}
void SeqArray::sort(){
	for(int i = 0; i < len-1; i++){
		for(int j = 0; j < len-1-i; j++){
			if(array[j+1] < array[j]){
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;		  		
			}		
		}
	}
}
void SeqArray::benchmarkBubble(int len, int iterations) {
    for (int i = 0; i < iterations; ++i) {
    	SeqArray s1(len);
    	s1.fillrandom();
        s1.printall();
        auto start = std::chrono::system_clock::now();
        s1.sortbubble();
        s1.printall();
		auto end = std::chrono::system_clock::now();
        std::cout << "Iteration " << i + 1 << " - Bubble Sort - Time taken: " 
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms " 
                  << "Comparisons: " << s1.getcompares() << ", "
                  << "Swaps: " << s1.getswaps() << "\n";
    }
}
void SeqArray::benchmarkInsertion(int len, int iterations) {
    for (int i = 0; i < iterations; ++i) {
    	SeqArray s1(len);
    	s1.fillrandom();
        s1.printall();
        auto start = std::chrono::system_clock::now();
        s1.sortinsertion();
        s1.printall();
		auto end = std::chrono::system_clock::now();
        std::cout << "Iteration " << i + 1 << " - Insertion Sort - Time taken: " 
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms " 
                  << "Comparisons: " << s1.getcompares() << ", "
                  << "Swaps: " << s1.getswaps() << "\n";
    }
}
void SeqArray::benchmarkSelection(int len, int iterations) {
    for (int i = 0; i < iterations; ++i) {
    	SeqArray s1(len);
    	s1.fillrandom();
        s1.printall();
        auto start = std::chrono::system_clock::now();
        s1.sortselection();
        s1.printall();
		auto end = std::chrono::system_clock::now();
        std::cout << "Iteration " << i + 1 << " - Selecction Sort - Time taken: " 
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms " 
                  << "Comparisons: " << s1.getcompares() << ", "
                  << "Swaps: " << s1.getswaps() << "\n";
    }
}


int main(){
	SeqArray s(5);
	/*s.insert(3);
	s.insert(6);
	s.insert(8);
	s.insert(9);           // insertion
	s.insert(10);
	s.printall();*/
	//s.insert(2, 7);
	//s.insertFirst(66);    // insert first
	//s.remove(8);          // remove
	//s.removeFirst();        // remove first
	//s.sort();             // sort
	//s.printall();
	s.benchmarkBubble(10, 2);
	cout<<endl;
	s.benchmarkInsertion(10, 2);
	cout<<endl;
	s.benchmarkSelection(14, 2);
}