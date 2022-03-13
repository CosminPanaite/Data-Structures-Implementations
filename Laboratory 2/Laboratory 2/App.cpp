#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"


#include <iostream>
using namespace std;


int main() {
	testAll(); //short variant of tests
	testAllExtended(); // the detalied variant of tests

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


