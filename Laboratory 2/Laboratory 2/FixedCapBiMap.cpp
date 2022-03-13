#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include<exception>
using namespace std;
FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0) {
		throw exception();
	}
	this->capacity = capacity; //this-> is the same with self.
	this->nrPairs = 0;
	this->elements = new TElem[capacity];// here i created a new array which has the number of capacity elements(capacity elements of TElem)
}
// theta(1) / Theta(capacity)

FixedCapBiMap::~FixedCapBiMap() { //tilda is the meaning for destructor when you no longer need it
	delete[] this->elements; //destructor of array; 
}
//theta(1)

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->capacity == this->nrPairs){
		throw exception();

	}
	int index = 0;//the current position we re checking
	int count = 0;
	while (count < 2 && index < nrPairs) {
		if (this->elements[index].first == c) {//c is key as parameter , first for key
			count++;
		}
		index++;
	}
	if (count == 2) {
		return false;

	}
	else {
		this->elements[this->nrPairs].first = c;
		this->elements[this->nrPairs].second = v;
		this->nrPairs++;
		return true;	
	}
	
}
// Best case: Theta(1)
// Worst case:Theta(nrPairs) => Total complexity O(nrPairs)
ValuePair FixedCapBiMap::search(TKey c) const {
	ValuePair returnedValue;
	returnedValue.first = NULL_TVALUE;
	returnedValue.second = NULL_TVALUE;
	int index = 0;//the current position we re checking
	int count = 0;
	while (count < 2 && index < this->nrPairs) {
		if (this->elements[index].first == c) {
			if (count == 0) {
				returnedValue.first = this->elements[index].second;
			}

			else {
				returnedValue.second = this->elements[index].second;
			}
			count++;

		}
		index++;
	}
	 
	return returnedValue;
}
// Best Case : Theta(1)
// Worst case : Theta(n)
//the final complexity O(nrPairs)

bool FixedCapBiMap::remove(TKey c, TValue v) {
	int index = 0;
	bool found = false;
	while (index < this->nrPairs && found == false) {
		if (this->elements[index].first == c && this->elements[index].second == v)
		{
			found = true;
		}

		else {
			index++;
		}
	}
	if (found == false) {
		return false;
		}
	else {
		this->elements[index] = this->elements[this->nrPairs - 1];
		this->nrPairs--;
		return true;
		}
	}

//Best Case Theta(1)
//Worst case Theta(nrPairs)
// Total Complexity : O(nr pairs)
int FixedCapBiMap::size() const {
	return this->nrPairs; 
	
}
//theta(1)

bool FixedCapBiMap::isEmpty() const{
	if (this->nrPairs == 0){
		return true;
	}
	else
	{
		return false;
	}
		
	
}
//theta(1)
bool FixedCapBiMap::isFull() const {
	if(this->nrPairs==this->capacity) {
		return true;
	}
	else
	{
		return false;
	}
	///const the operation does not modify the class
	
}
//theta(1)
/*ValuePair :: removeKey(TKey k)
{
	ValuePair returnedValue;
	returnedValue.first = NULL_TVALUE;
	returnedValue.second = NULL_TVALUE;
	int counter = 0;
	int pos1 = -1;
	int pos2 = -2;
	for (int counter = 0; counter < this->nrpairs && nr<3; counter++)
		if (this->elements[counter].first == k)
		{
			nr++;
			break;
			pos1 = counter;
		}
	if (pos1 == -1)
	{
		returnedValue.first = NULL_TVALUE;
		returnedValue.second = NULL_TVALUE;
	}
	else {
		returnedValue.first = this->elements[pos1].second;
		


	}
	for (int counter = pos1; counter < this->nrpairs && nr<3; counter++)
		{
			nr++;
			break
			pos2 = counter;
		}
	if (pos2 != -2)
	{

		returnedValue.second = this->elements[pos2].second;
	}
	
	return returnedValue;

	}
//Complexity theta(n) in the worst case
// Best theta (1)
// The final complexity O(n)
*/
FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



