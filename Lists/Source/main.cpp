#include <iostream>

#include "List.hpp"
#include "FList.hpp"

int main()
{
	std::cout << "Hello World!";
	
	// Ghost scope to cause a destruction
	try
	{
		List<int> intList = { 1, 10, 5, -5 };
		intList.InsertAt(14, 4);
		intList.Remove();
		intList.RemoveAt(3);

		intList.PrintList();

		std::cout << "\n" << intList.GetSize() << "\n";
		std::cout << intList.IsEmpty() << "\n";
	}
	catch (std::exception& ex)
	{
		std::cerr << std::endl << ex.what() << std::endl;
	}

	return 0;
}

