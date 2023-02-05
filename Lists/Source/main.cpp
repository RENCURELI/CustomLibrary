#include <iostream>

// Currently functionnal Lists -> Singly Linked List && Forward List
#include "SList.hpp"
#include "FList.hpp"

int main()
{
	std::cout << "Hello World!";
	
	// Ghost scope to cause a destruction
	{
		SList<int> intList = { 1, 10, 5, -5 };
		intList.InsertAt(14, 4);
		intList.Remove();
		intList.RemoveAt(3);

		intList.PrintList();

		std::cout << "\n" << intList.GetSize() << "\n";
		std::cout << intList.IsEmpty() << "\n";
	}
	std::cout << "I hope this worked";

	return 0;
}

