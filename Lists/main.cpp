#include <iostream>
#include "SList.h"

int main()
{
	std::cout << "Hello World!";

	SList<int> intList = { 1, 10, 5, -5 }; // Empty List created


	intList.PrintList();
}