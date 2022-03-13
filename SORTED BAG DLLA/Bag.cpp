#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


int Bag::allocate()
{
	int newElement = this->firstEmpty;
	if (newElement != -1) {
		this->firstEmpty = this->elements[this->firstEmpty].nextAdress;
		if (this->firstEmpty != -1) {
			this->elements[this->firstEmpty].prevAdress = -1;
		}
		this->elements[newElement].nextAdress = -1;
		this->elements[newElement].prevAdress = -1;
	}
	return newElement;
}
//Complexity: Theta(1)

void Bag::free(int position)
{
	this->elements[position].nextAdress = this->firstEmpty;
	this->elements[position].prevAdress = -1;
	if (this->firstEmpty != -1) {
		this->elements[this->firstEmpty].prevAdress = position;
	}
	this->firstEmpty = position;
}
//Complexity: Theta(1)


Bag::Bag() {
	this->capacity = 10;
	this->dimension = 0;
	this->head = -1;
	this->tail = -1;
	this->elements = new Node[capacity];
	for (int i = 0; i < capacity - 1; i++) {
		// we write the indexes of the next positions of the elements
		this->elements[i].nextAdress = i + 1;
		this->elements[i].frequency = 0;
	}
	this->elements[capacity - 1].nextAdress = -1;


	for (int i = capacity - 1; i > 0; i--) {
		// we write the indexes of the previous positions of the elements
		this->elements[i].prevAdress = i - 1;
	}
	this->elements[0].prevAdress = -1;
	this->firstEmpty = 0;

}
//Best case = Theta(capacity) = Worst case => Complexity: Theta(capacity)


void Bag::add(TElem elem) {
	int current = this->head;
	int newElem = this->allocate();
	int ok = 0;//make it 1 if we raise the frequency

	if (this->dimension == this->capacity)// the vector is full, so we have to resize
	{
		Node* newArray = new Node[this->capacity * 2];
		for (int i = 0; i < this->capacity; i++) {
			newArray[i] = this->elements[i];
		}

		for (int i = this->capacity; i < this->capacity * 2 - 1; i++) {
			newArray[i].nextAdress = i + 1;
			newArray[i].frequency = 0;
		}
		newArray[this->capacity * 2 - 1].nextAdress = -1;

		for (int i = this->capacity * 2 - 1; i > this->capacity; i--) {
			newArray[i].prevAdress = i - 1;
		}
		newArray[this->capacity].prevAdress = -1;

		this->firstEmpty = this->capacity;
		this->capacity = this->capacity * 2;
		delete[] this->elements;
		this->elements = newArray;

		newElem = this->allocate();
	}
	if (this->head == -1) //Case1: the list is empty 
	// we need to add the element and set it as the head and tail
	{
		this->head = newElem;
		this->tail = newElem;
		this->elements[newElem].nextAdress = -1;
		this->elements[newElem].prevAdress = -1;
		//this->firstEmpty = this->elements[firstEmpty].nextAdress; ->we have allocate for this
		this->dimension++;
		this->elements[newElem].frequency++;
		ok = 1;
	}
	else {
		// Case2: the list contains at least one element
		// we shall add the element at the end and make it the tail
		this->elements[newElem].prevAdress = this->tail;
		this->elements[this->tail].nextAdress = newElem;
		this->tail = newElem;
		this->dimension++;
		this->elements[newElem].frequency++;
		
	}
	// if we get to this point, it means the list has more than one element, and we add the new one at an empty position, which is exactly newElem
	// it was allocated with the special function that tells me where the next empty position is
	this->elements[newElem].info = elem;

}
//Complexity: O(dimension) amortised, because we need to readjust the array a very few times, fewer as the array gets bigger
//Best case is if we just add an element=> Theta(1)
//Worst case(very rare, more unlikely once the array gets bigger) if we do a resize => Theta(dimension)


bool Bag::remove(TElem elem) {
	int current = this->head;

	if (this->head == -1) {
		// the list is empty, we don't have what to remove
		return false;
	}

	while (current != -1 && !(this->elements[current].info==elem)) {
		// unless we reached the end or the elem, we keep going
		current = this->elements[current].nextAdress;
	}
	if (current == -1) {
		// we reached the end and didn't find the element
		return false;
	}
	else {
		// we found elem
		// now, we analyse what role it has in the bag (head, tail or none of these 2) and what the bag looks like
		if (this->dimension == 1 /*or this->head == this->tail*/){
			// the list has only one element
			this->free(current);
			this->head = -1;
			this->tail = -1;
			this->dimension--;
			this->elements[current].frequency--;
			return true;
		}

		else if (current == this->tail) {
			// we must delete the tail
			this->tail = this->elements[current].prevAdress;
			this->elements[this->tail].nextAdress = -1;
			this->free(current);
			this->dimension--;
			this->elements[current].frequency--;
			return true;
		}
		else if (current == this->head) {
			// we  must delete the head
			this->head = this->elements[current].nextAdress;
			this->elements[this->head].prevAdress = -1;
			this->free(current);
			this->dimension--;
			this->elements[current].frequency--;
			return true;
		}
		else {
			// case when there are more elements ->middle 
			// introduce 2 extras: 1 for the prev index, sec for next adress
			int prev = this->elements[current].prevAdress;
			int next = this->elements[current].nextAdress;
			this->elements[prev].nextAdress = next;//we change the next adress of the previous element
			this->elements[next].prevAdress = prev;//we change the previous adress of the next element
			this->free(current);
			this->dimension--;
			this->elements[current].frequency--;
			return true;
		}
	}
	return false;
}
//Best case: Theta(1), Worst case: Theta(dimension) => Complexity: O(dimension)

bool Bag::search(TElem elem) const {
	int current = this->head;
	if(this->head == -1)//The list is empty
		return false;

	while (current != -1) {
		if (this->elements[current].info == elem)
		{
			return true;
		}
		current = this->elements[current].nextAdress;
	}
	return false;
}
//Best case: Theta(1), Worst case: Theta(dimension) => Complexity: O(dimension)

int Bag::nrOccurrences(TElem elem) const {
	//return this->elements[elem].frequency;
	if (this->head == -1)
		return 0;

	int current = this->head;
	int k = 0;
	while (current != -1) 
	{
		if (this->elements[current].info == elem)
		{
			k++;
		}
		current = this->elements[current].nextAdress;
	}
	return k;
}
//Best case: Theta(1), Worst case: Theta(dimension) => Complexity: O(dimension)


int Bag::size() const {
	return this->dimension;
}
//Complexity: Theta(1)

bool Bag::isEmpty() const {
	return this->head == -1;//returns the value of truth of this sentence, if the head is -1 it means that the list is empty
	/*
	or
	return this->dimension == 0;
	*/
}
//Complexity: Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
//Complexity: Theta(1)


Bag::~Bag() {
	delete[] this->elements;
}
//Complexity: Theta(1)

