#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r)  {
	Node *head=nullptr;
	this->relation=r;
	this->dim = 0; //dimension
	
}


bool SortedSet::add(TComp elem) {
	
	Node* auxiliar;
	auxiliar = head;
	if (search(elem)==true)
	{
		return false;
	}
	else
	{
		if (size()==0) {
			head = new Node(elem);
			head->next = nullptr;
		}
		
		else {


			if (relation(elem, head->info))
			{
				auxiliar = new Node(elem);
				auxiliar->next = head;
				head = auxiliar;

			}
			else
			{
				auxiliar = head;
				Node* previousNode = head;
				while (!relation(elem, auxiliar->info) && auxiliar->next != nullptr)
				{
					previousNode = auxiliar;

					auxiliar = auxiliar->next;
				}
				if (relation(elem, auxiliar->info)) {
					Node* auxiliar2;
					auxiliar2 = new Node(elem);
					previousNode->next = auxiliar2;
					auxiliar2->next = auxiliar;
				}
				else {
					Node* auxiliar2;
					auxiliar2 = new Node(elem);
					auxiliar->next = auxiliar2;
					auxiliar2->next = nullptr;
				}
			}
		}
	dim++;
	return true;
	}
	
	
}
//best case when we dont add theta(1)
//worst case theta(n)
//final o(n)
bool SortedSet::remove(TComp elem) {
	Node* auxiliar;
	Node* previousNode=head;
	Node* nod=head;
	if (size() == 0)
		return false;
	auto iter = SortedSetIterator(*this);
	int ok = 0;
	while (nod != nullptr)
	{
		if (nod->info == elem)
		{
			ok = 1;
		}
		nod = nod->next;
	}
	if (ok == 0)
	{
		return false;
	}
	else
	{	
		if (head->info==elem)
		{
			auxiliar = head->next;
			delete head;
			head = auxiliar;
		}	
		else
		{
			auxiliar = head->next;
			while (auxiliar->info!=elem)

			{
				previousNode = auxiliar;
				auxiliar = auxiliar->next;
			}
			previousNode->next = auxiliar->next;
			delete auxiliar;
		}
		dim--;
		return true;
	}
}

// 2 loops so constants => O(n)
bool SortedSet::search(TComp elem) const {
	Node* auxiliar = head;
	while (auxiliar != nullptr)
	{
		if (auxiliar->info == elem)
		{
			return true;
		}
	
		auxiliar = auxiliar->next;
	}
	return false;
}
///Best Case Theta(1)
///Worst Case Theta(n)
/// Total Complexity O(n)

int SortedSet::size() const {
	return this->dim;
}
//theta(1)

bool SortedSet::isEmpty() const {
	if (size()==0)
	
		return true;
	return false;
	
		
	
}
//Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

bool SortedSet::isSubsetOf(SortedSet& s) const
{
	Node* auxiliar=head; //for this
	while (auxiliar != nullptr)
	{
		Node* buxiliar = s.head; //for ohter s
		bool ok = false;
		while (buxiliar != nullptr)
		{
			if (buxiliar->info == auxiliar->info)
			{
				ok = true;

			}
			buxiliar = buxiliar->next;

		}
		if (ok == false)
		{
			return false;

		}
		auxiliar = auxiliar->next;

	}
	return true;
}
// worst theta(n*m) 
//best theta(1)
// O(n*m)
SortedSet::~SortedSet() {
	Node* currentNode;
	Node* nextNode;

	currentNode = head;
	while (currentNode != nullptr)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
}
//Complexity Theta(n)


