#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
	system("color 0B");
	testAll();
	testAllExtended();
	std::cout << "Finished LP Tests!" << std::endl;
	system("pause");
}