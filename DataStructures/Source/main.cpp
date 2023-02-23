#include <iostream>

#include "List.hpp"
#include "FList.hpp"

#include "Array.hpp"

int main()
{
	std::cout << "Hello World! \n";

	try
	{
		Array<int, 5> test{ 51, -12, 0, 48, 3 };
		int val = test.at(3);
		Array<int, 5> test2{ 3, 21, 98, 4, -1 };

		test.swap(test2);

		List<int> intList = { 1, 10, 5, -5 };
		List<int> newList = { 31, 47 };

		const auto initializerList = { 51, -12, 0 };
		intList.InsertAt(14, 4);
		intList.pop_back();
		intList.RemoveAt(1);

		intList.PrintList();

		newList = intList;

		std::cout << "\n" << intList.GetSize() << "\n";
		std::cout << intList.IsEmpty() << "\n";

		newList.PrintList();

		std::cout << "\n" << newList.GetSize() << "\n";
		std::cout << newList.IsEmpty() << "\n";

		newList = initializerList;

		newList.PrintList();

		std::cout << "\n" << newList.GetSize() << "\n";
		std::cout << newList.IsEmpty() << "\n";
	}
	catch (std::exception& ex)
	{
		std::cerr << std::endl << ex.what() << std::endl;
	}

	return 0;
}

