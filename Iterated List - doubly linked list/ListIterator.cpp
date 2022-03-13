#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
#include <iostream>
using namespace std;

ListIterator::ListIterator(const IteratedList& list) : list(list) {
	this->current = list.list->head;
	
}
// Theta(1) 


void ListIterator::first() {
	this->current = this->list.list->head;
	
}
// Theta(1) 


void ListIterator::next() {
	if(!this->valid())
		throw exception();
	this->current = this->current->next;
	
}
// Theta(1) 


bool ListIterator::valid() const {
	if (this->current == NULL) {
		return false;
	}
	else {
		return  true;
	}
	
}
// Theta(1) 


TElem ListIterator::getCurrent() const {
	if (!this->valid()) {
		throw exception();
		
	}
	else {
		return this->current->info;
	}
	
}


