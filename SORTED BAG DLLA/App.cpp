#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include"Bag.h"
#include"BagIterator.h"

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();
	cout << "All test over" << endl;
}