#pragma once
#include <vector>
#include <utility>
#include <stdlib.h>
//DO NOT INCLUDE BAGITERATOR

using namespace std;

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;

struct Node {
	TElem info;
	int frequency;
	int prevAdress;
	int nextAdress;
};

class BagIterator; 

class Bag {

private:
	//the elements of the array
	Node* elements;

	// the capacity of the arrays
	int capacity;

	// the index of the head of the list
	int head;

	// the index of the tail of the list
	int tail;

	// the first empty position
	int firstEmpty;

	// the size of the array
	int dimension;


	// AUXILIARY FUNCTIONS:
	
	// Allocate an empty position to a new element
	int allocate();

	// Free a position after the element is deleted
	void free(int position);


	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};