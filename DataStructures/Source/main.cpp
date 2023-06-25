#include <iostream>

#include "List.hpp"
#include "FList.hpp"

#include "DeQue.hpp"

#include "Stack.hpp"

#include <algorithm>
#include <deque>
int main()
{
	std::cout << "Hello World! \n";

	try
	{
		DeQue<int> testDeque;
		//std::deque<int> testDeque;

		for (int i = 0; i < 60; ++i)
		{
			testDeque.push_front(i);
		}
		//testDeque.push_back(1);
	}
	catch (std::exception& ex)
	{
		std::cerr << std::endl << ex.what() << std::endl;
	}

	return 0;
}

