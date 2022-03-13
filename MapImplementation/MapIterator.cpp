#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->current = 0;
}


void MapIterator::first() {
	this->current = 0;
}
//theta(1)

void MapIterator::next() {
	if (this->current == this->map.nrPairs) {
		throw exception();
	}
	
	
	this->current++;
	
}
// theta(1)



TElem MapIterator::getCurrent(){
	if (this->current == this->map.nrPairs) {
		throw exception();

	}
	return this->map.elements[this->current];
}
//theta(1)


bool MapIterator::valid() const {

	if (this->current < this->map.nrPairs)
	{
		return true;
	}
	
	
	return false;
	

	//theta(1)


}