#include <iostream>

#include "List.hpp"
#include "FList.hpp"

#include "Array.hpp"
#include "Vector.hpp"

#include "Stack.hpp"

#include <algorithm>
#include <forward_list>
int main()
{
	std::cout << "Hello World! \n";

	try
	{
		std::forward_list<int> testList;
		std::forward_list<int> otherList = { 1, 2, 3 };

		// This breaks, so I assume can't be called on empty container
		testList.insert_after(testList.cbegin(), otherList.begin(), otherList.end());

	}
	catch (std::exception& ex)
	{
		std::cerr << std::endl << ex.what() << std::endl;
	}

	return 0;
}

