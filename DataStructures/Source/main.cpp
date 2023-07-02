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
		int** map = new int*[5];
		for (int count{ 0 }; count < 10; ++count)
			map[count] = new int[5]; // these are our columns

		map[0][0] = 2;
		DeQue<int> testDeque;
		//std::deque<int> testDeque;

		for (int i = 0; i < 60; ++i)
		{
			testDeque.push_front(i);
			//testDeque.push_back(i);
		}
		//testDeque.push_back(1);
		testDeque.size();
	}
	catch (std::exception& ex)
	{
		std::cerr << std::endl << ex.what() << std::endl;
	}

	return 0;
}

