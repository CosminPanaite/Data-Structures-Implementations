#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m),current{multime.head}
{
	first();
}
//theta(1)


void SortedSetIterator::first() {
	current = multime.head;
}
//theta(1)

void SortedSetIterator::next() {
	if (!valid()) {
		throw std::exception("invalid iterator");
	}
	current = current->next;
}
//theta(1)

TElem SortedSetIterator::getCurrent()
{
	if (valid() == false)
		throw std::exception("invalid iterator");
	return current->info;
	
}
// theta(1)
bool SortedSetIterator::valid() const {
	if (current == nullptr)
		return false;
	return true;
}
//theta(1)

