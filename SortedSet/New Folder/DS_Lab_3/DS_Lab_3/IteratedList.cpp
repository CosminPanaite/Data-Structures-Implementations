#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

IteratedList::IteratedList() {
	//TODO - Implementation
	this->elements.head = nullptr;
	this->elements.tail = nullptr;
	this->elements.length = 0;
}

//theta(1)

int IteratedList::size() const {
	//TODO - Implementation
	return this->elements.length;
}

//theta(1)

bool IteratedList::isEmpty() const {
	//TODO -  Implementation
	if (this->elements.length == 0)
		return true;
	return false;
}

//theta(1)

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

//theta(1)

TElem IteratedList::getElement(ListIterator pos) const {
	//TODO - Implementation
	int current_position = 0;
	if (!pos.valid())
		throw std::exception();

	return pos.current->info;
}

//theta(1)

TElem IteratedList::remove(ListIterator& pos) {
	//TODO - Implementation
	
	if (pos.valid() == false)
		throw std::exception();

	TElem deleted_element;
	deleted_element = pos.current->info;
	if (pos.current->next == nullptr && pos.current->previous == nullptr)
	{
		this->elements.head = nullptr;
		this->elements.tail = nullptr;
	}
	else if (pos.current->previous == nullptr)
	{
		pos.current->next->previous = nullptr;
		this->elements.head = pos.current->next;
	}
	else if (pos.current->next == nullptr)
	{
		pos.current->previous->next = nullptr;
		this->elements.tail = pos.current->previous;
	}
	else
	{
		pos.current->previous->next = pos.current->next;
		pos.current->next->previous = pos.current->previous;
	}
	this->elements.length--;
	pos.next();
	return deleted_element;
}

//theta(1)

ListIterator IteratedList::search(TElem e) const {
	//TODO - Implementation
	ListIterator current_it= ListIterator(*this);
	
	while (current_it.valid() && current_it.current->info!=e)
	{
		current_it.next();
	}

	return current_it;
}

void IteratedList::reverseBetween(ListIterator& start, ListIterator& end)
{
	if (start.valid() == false || end.valid() == false)
		throw std::exception();

	DLLNode* new_node = new DLLNode;
	new_node->previous = start.current->previous;
	new_node->info = start.current->info;
	new_node->next = start.current->next;

	//new_node->info != end.current->info &&
	int distance=0;
	while (new_node!=end.current && new_node!=nullptr)
	{
		distance++;	
		new_node = new_node->next;
	}
	distance++;

	if (new_node == nullptr)
		throw std::exception();
	
	int i = 1;
	while( i <= distance / 2 )
	{
		int aux = start.current->info;
		start.current->info = end.current->info;
		end.current->info = aux;

		start.next();
		end.current = end.current->previous;
		i++;
	}
}

//Best case theta(1), Worst case theta(length) -> O(length)


TElem IteratedList::setElement(ListIterator pos, TElem e) {
	//TODO - Implementation
	if (pos.valid() == false)
		throw std::exception();
	TElem return_value;
	return_value = pos.current->info;
	pos.current->info = e;
	return return_value;
}

//theta(1)

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	//TODO - Implementation
	if (pos.valid() == false)
		throw std::exception();

	 if (pos.current->next == nullptr)
		this->addToEnd(e);
	else
	{
		//pos.next();
		DLLNode* new_node= new DLLNode;
		new_node->info = e;
		
		new_node->next = pos.current->next; 
		new_node->previous = pos.current;
		
		pos.current->next->previous = new_node;
		pos.current->next = new_node;
		this->elements.length++;
	}
	pos.next();
}

//theta(1)

void IteratedList::addToEnd(TElem e) {
	//TODO - Implementation
	DLLNode* new_node = new DLLNode;
	new_node->info = e;
	new_node->next = nullptr;
	new_node->previous = nullptr;

	if (this->elements.head == nullptr)
	{
		this->elements.head = new_node;
		this->elements.tail = new_node;
	}
	else
	{
		new_node->previous = this->elements.tail;
		this->elements.tail->next = new_node;
		this->elements.tail = new_node;
	}
	this->elements.length++;

}

//theta(1)

void IteratedList::addToBeginning(TElem e)
{
	DLLNode* new_node= new DLLNode;
	new_node->info = e;
	new_node->next = nullptr;
	new_node->previous = nullptr;

	if (this->elements.head == nullptr)
	{
		this->elements.head = new_node;
		this->elements.tail = new_node;
	}
	else
	{
		new_node->next = this->elements.head;
		this->elements.head->previous = new_node;
		this->elements.head = new_node;
	}
	this->elements.length++;

}

//theta(1)

IteratedList::~IteratedList() {
	//TODO - Implementation
	if (this->elements.length != 0)
	{
		/*if (this->elements.length == 1)
			delete this->elements.head;
		else {*/
		DLLNode* current = this->elements.head->next;
		while (current != nullptr)
		{
			delete current->previous;
			current = current->next;
		}
		delete current;
	}
}

//theta(length)

