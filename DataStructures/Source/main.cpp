#include <iostream>

#include "List.hpp"
#include "FList.hpp"

#include "DeQue.hpp"

#include "Vector.hpp"
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

		testDeque.push_front(0);
		testDeque.pop_front();

		for (int i = 0; i < 60; ++i)
		{
			testDeque.push_front(i);
			testDeque.push_back(i);
		}

		auto it = testDeque.begin();
		it = std::find(it, testDeque.end(), 41);
		for (auto val : testDeque)
		{
			std::cout << val << "\n";
		}

		testDeque.push_back(1);
		std::cout << testDeque.size() << "\n";
		testDeque.pop_back();
		//std::cout << testDeque.at(12);
		std::cout << testDeque[12] << "\n";
		std::cout << testDeque.size() << "\n";

		testDeque.pop_front();
		std::cout << testDeque[12] << "\n";
		std::cout << testDeque.size() << "\n";
	}
	catch (std::exception& ex)
	{
		std::cerr << std::endl << ex.what() << std::endl;
	}

	return 0;
}
