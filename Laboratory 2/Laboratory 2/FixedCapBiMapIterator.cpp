#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->current = 0;
}
//theta(1)

void FixedCapBiMapIterator::first() {
	//the role of fisrst() is to reset the iterator on the beggining of the container
	this->current = 0;
}

// theta(1)
void FixedCapBiMapIterator::next() {
	if (this->current==this->map.nrPairs){
		throw exception();
	}
	else 
	{
		this->current++;
	}

}
// theta(1)


TElem FixedCapBiMapIterator::getCurrent(){
	if (this->current == this->map.nrPairs){
		throw exception();

	}
	return this->map.elements[this->current]	;
	return NULL_TELEM;
}


bool FixedCapBiMapIterator::valid() const {
	if (this->current < this->map.nrPairs){
		return true;

	}
	else {
		return false;
	}
	return false;
}



