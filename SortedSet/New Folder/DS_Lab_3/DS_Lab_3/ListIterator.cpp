#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

ListIterator::ListIterator(const IteratedList& list) : list(list) {
	//TODO - Implementation
	this->current = this->list.elements.head;
}

//theta(1)

void ListIterator::first() {
	//TODO - Implementation
	this->current = this->list.elements.head;
}

//theta(1)

void ListIterator::next() {
	//TODO - Implementation
	if (this->current == nullptr)
		throw std::exception();
	else
		this->current = this->current->next;

}

//theta(1)

bool ListIterator::valid() const {
	//TODO - Implementation
	if (this->current == nullptr)
		return  false;
	else
		return true;
}

//theta(1)

TElem ListIterator::getCurrent() const {
	//TODO - Implementation
	if (this->current == nullptr)
		throw std::exception();
	else
		return this->current->info;
}

//theta(1)



