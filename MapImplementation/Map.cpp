#include<iostream>

#include<assert.h>
#include<exception>
#include<excpt.h>
#include "Map.h"
#include "MapIterator.h"
using namespace std;

Map::Map()
{
	this->capacity = 40000;
	this->nrPairs = 0;
	this->elements = new TElem[40000]; // the impplicit constructor
}



Map ::~Map() {
	delete[] this->elements; //the destructor
}
//theta(1)


TValue Map::add(TKey c, TValue v) {
	
	if (this->capacity == this->nrPairs-1 )
	{
		this->capacity = this->capacity * 2; //resize 
				
	}
	int index = 0;
	while (index < this->nrPairs)
	{
		if (this->elements[index].first == c)
		{	// if the key exists then i attribute to oldVal the previous value of the key and return it
			TValue value = this->elements[index].second;
			this->elements[index].second = v;
			return value;
		}
		index++;
	}
	this->elements[this->nrPairs].first = c;
	this->elements[this->nrPairs].second = v;
	this->nrPairs++;
	return NULL_TVALUE; //if the key does not exist i simply add the pair at the end and return Null value
	
}


	
//O(n)

TValue Map::search(TKey c) const {
	int index = 0;
	while (index < this->nrPairs) 
	{
		if (this->elements[index].first == c)
		{
			return this->elements[index].second; // i return the the value of pair if it is found on array
		}
		
		index++;

		
	}
	return NULL_TVALUE;


}
//best case Theta (1)
//worst theta (n)
// Final complexity-> O(n)
TValue Map::remove(TKey c) {
	int index = 0;
	int value;
	while (index < this->nrPairs){
		if (this->elements[index].first == c) {
			 value= this->elements[index].second;//value which will be returned after it is deleted
			this->elements[index] = this->elements[this->nrPairs-1];
			this->nrPairs--;
			if (this->capacity >= this->nrPairs * 2)
			{
				this->capacity = this->capacity / 2; //resize after deleting elements

			}

			return value; //here i return the previous value of the the existing key

		}
		
		index++;
		
	}
	
	return NULL_TVALUE;
}

// best case Theta(1) worst case theta (n) The final complexity is O(NrPairs) 
int Map::size() const {
	return this->nrPairs; //return the size of list which is = to nr pairs

	return 0;
}
//theta(1)

bool Map::isEmpty() const {
	if (this->nrPairs == 0) { // if the nr of pairs =0 => the list is empty
		return true;
	}
	else
	{
		return false;
	}

}
//theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}
//theta(1)


