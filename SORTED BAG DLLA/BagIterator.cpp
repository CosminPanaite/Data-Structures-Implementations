#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = c.head;
}
//Complexity: Theta(1)


void BagIterator::first() {
	this->current = this->bag.head;
}
//Complexity: Theta(1)


void BagIterator::next() {
	if (this->current == -1) {
		throw exception();
	}
	else {
		this->current = this->bag.elements[current].nextAdress;
	}
}
//Complexity: Theta(1)


bool BagIterator::valid() const {
	return this->current != -1;
}
//Complexity: Theta(1)


TElem BagIterator::getCurrent() const
{
	if (current == -1) {
		throw exception();
	}
	else {
		return this->bag.elements[current].info;
	}
}
//Complexity: Theta(1)