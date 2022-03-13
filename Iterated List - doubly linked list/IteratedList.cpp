
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
#include <iostream>
using namespace std;

IteratedList::IteratedList() {
	this->list = new DLL;
	this->list->head = NULL;
	this->list->tail = NULL;
}
// Theta(1) 


int IteratedList::size() const {
	int count = 0;
	DLLNode* copy = this->list->head;
	while (copy != NULL) {
		count++;
		copy = copy->next;
	}
	delete copy;
	return count;
}
//Best case : Theta(1) -list is empty, Worst case : Theta(n), Overall complexity: O(n);


bool IteratedList::isEmpty() const {
	if (this->list->head == NULL) {
		return true;
	}
	return false;
}
// Theta(1) 


ListIterator IteratedList::first() const {
	return ListIterator(*this);
}
// Theta(1) 


TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid()) {
		throw exception();
	}
	else {
		return pos.current->info;
	}
	
}
// Theta(1) 


TElem IteratedList::remove(ListIterator& pos) {
	if (!pos.valid())
		throw exception();
	TElem removed = pos.current->info;

	DLLNode* currentNode = this->list->head;

	while (currentNode != pos.current)
	{

		currentNode = currentNode->next;
	}

	if (currentNode != NULL) {
		if (currentNode == this->list->head) {
			if (currentNode == this->list->tail) {
				this->list->head = NULL;
				this->list->tail = NULL;
			}
			else {
				this->list->head = this->list->head->next;
				this->list->head->prev = NULL;
			}
		
		}
		else if (currentNode == this->list->tail) {
			this->list->tail = this->list->tail->prev;
			this->list->tail->next = NULL;
		}
		else {
			currentNode->next->prev = currentNode->prev;
			currentNode->prev->next = currentNode->next;
			delete currentNode;
		}
	}
	pos.next();
	
	
	return removed;
	
}
//Best case : Theta(1), Worst case : Theta(n), Overall complexity: O(n);


ListIterator IteratedList::search(TElem e) const{
	ListIterator it = ListIterator(*this);
	it.first();

	while (it.valid()) {
		if (it.current->info == e)
			return it;
		else {
			it.next();
		}
		
	}
	return it;
}
//Best case : Theta(1), Worst case : Theta(n), Overall complexity: O(n);


TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid()) 
		throw exception();
	TElem oldValue = pos.current->info;
	pos.current->info = e;
	
	return oldValue;

}
// Theta(1) 


void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (!pos.valid())
		throw exception();
	DLLNode* newNode = new DLLNode;
	newNode->info = e;
	newNode->next = NULL;
	newNode->prev = NULL;

	DLLNode* currentNode = this->list->head;

	while (currentNode != pos.current)
	{
		currentNode = currentNode->next;
	}

	newNode->prev = currentNode;
	newNode->next = currentNode->next;

	if (currentNode->next != NULL) {
		currentNode->next->prev = newNode;
	}

	currentNode->next = newNode;

	if (this->list->tail == currentNode) {
		this->list->tail = newNode;
	}

	pos.next();


}
//Best case : Theta(1), Worst case : Theta(n), Overall complexity: O(n);


void IteratedList::addToEnd(TElem e) {
	DLLNode* newNode = new DLLNode; 
	newNode->info = e; 
	newNode->next = NULL; 
	newNode->prev = this->list->tail;

	if (isEmpty()) {
		this->list->head = newNode;
		this->list->tail = newNode;
	}
	else {
		this->list->tail->next = newNode;
		this->list->tail = newNode;
	}
}
// Theta(1) 


void IteratedList::addToBeginning(TElem e)
{
	DLLNode* newNode = new DLLNode;
	newNode->info = e;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (isEmpty()) {
		this->list->head = this->list->tail = newNode;
	}
	else {
		newNode->next = this->list->head;
		this->list->head->prev = newNode;
		this->list->head = newNode;
	}

}
// Theta(1) 





IteratedList::~IteratedList()
{
	DLLNode* p = this->list->head;
	while (this->list->head != NULL) {
		p = this->list->head;
		this->list->head = this->list->head->next;
		delete p;
	}

}
//Best case : Theta(1), Worst case : Theta(n), Overall complexity: O(n); 
