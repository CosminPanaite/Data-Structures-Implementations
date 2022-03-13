#include "ShortTest.h"

#include <assert.h>
#include <exception>


#include "IteratedList.h"
#include "ListIterator.h"



using namespace std;

void testAll() {
	IteratedList list = IteratedList();
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	assert(list.size() == 1);
	assert(!list.isEmpty());

	ListIterator it = list.search(1);
	assert(it.valid());
	assert(it.getCurrent() == 1);
	it.next();
	assert(!it.valid());
	it.first();
	assert(it.valid());
	assert(it.getCurrent() == 1);

	assert(list.remove(it) == 1);
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	list.addToEnd(3);
	list.addToEnd(7);
	ListIterator it3 = list.first();
	list.addToPosition(it3, 77);
	list.addToPosition(it3, 44);
	assert(list.size() == 5);
	ListIterator it2 = list.first();
	assert(it2.getCurrent() == 1);
	it2.next();
	assert(it2.getCurrent() == 77);
	it2.next();
	assert(it2.getCurrent() == 44);
	it2.next();
	assert(it2.getCurrent() == 3);
	it2.next();
	assert(it2.getCurrent() == 7);
	it2.next();
	assert(it2.valid() == false);

	IteratedList list2 = IteratedList();
	list2.addToBeginning(4);
	list2.addToEnd(5);
	list2.addToBeginning(3);
	list2.addToEnd(6);
	list2.addToBeginning(2);
	list2.addToEnd(7);
	int i = 2;
	ListIterator it4 = list2.first();
	while (it4.valid()) {
		assert(it4.getCurrent() == i);
		i++;
		it4.next();
	}
/*	//tests for extra operation//b
	ListIterator it5 = list2.first();//2
	ListIterator it6 = list2.first();
	it6.next();//3
	list2.reverseBetween(it5, it6);

	ListIterator it_test_reverse = list2.first();
	assert(it_test_reverse.getCurrent() == 3);
	it_test_reverse.next();
	assert(it_test_reverse.getCurrent() == 2);

	ListIterator it7 = list2.first();
	ListIterator it8 = list2.first();
	it7.next();
	try {
		list2.reverseBetween(it7, it8);
		assert(false);
	}
	catch (exception&) {
		assert(true);

	}
	ListIterator it9 = list2.first();//b
	ListIterator it10 = list2.first();
	int j = 2;
	while (j < i-2)//-1
	{
		it10.next();
		j++;
	}
	list2.reverseBetween(it9, it10);
	
	ListIterator it11 = list2.first();
	ListIterator it12 = list2.first();
	list2.addToEnd(3);
	j = 2;//b
	while (j < i)
	{
		it12.next();
		j++;
	}
	list2.reverseBetween(it11, it12);//b

}

*/
