#include <iostream>

#include "List.hpp"
#include "FList.hpp"

#include "Array.hpp"
#include "Vector.hpp"

#include "Stack.hpp"

#include <algorithm>
#include <list>
int main()
{
	std::cout << "Hello World! \n";

	try
	{
		// insert block
		List<int> testList = { 1, 2, 3 };
		testList.clear();
		auto testIt = testList.insert(testList.cbegin(), 45, -1);

		std::list<int> otherList = { 1, 2, 3 };
		otherList.clear();
		auto otherIt = otherList.insert(otherList.cbegin(), 45, -1);

		// VECTOR
		Vector<float> vec{ 5.0f, 1.5f, 0.25f, 10.f };

		std::cout << "\n" << vec.capacity() << "\n";

		for (int i = 0; i < 50; i++)
		{
			vec.push_back(-1.0f);
		}
		std::cout << "\n" << vec.capacity() << "\n";

		vec.assign(3, -12.0f);

		vec.PrintVector();
		std::cout << "\n" << vec.capacity() << "\n";

		auto it = vec.begin();
		vec.insert(it + 1, 3.7f);
		//vec.insert(1, 3.7f);
		vec.PrintVector();

		Vector<int> testVec = { 1, 2, 3, 4, 5, 6, 7 };

		testVec.erase(std::next(testVec.begin(), 6));
		testVec.resize(4);
		std::cout << "Test Vector after resize" << "\n";
		testVec.PrintVector();

		// Range based for loop using iterators
		std::cout << "\n Test Vector Ranged based for loop" << "\n";
		for (auto value : testVec)
		{
			std::cout << value << std::endl;
		}

		if (std::find(testVec.begin(), testVec.end(), 3) != testVec.end())
		{
			std::cout << "We found 3" << std::endl;
		}

		std::fill(testVec.begin(), testVec.end(), 1);

		if (!(std::find(testVec.begin(), testVec.end(), 3) != testVec.end()))
		{
			std::cout << "We didn't find 3" << std::endl;
		}
		testVec.PrintVector();

		// Range base for loop using array iterators
		Array<int, 5> testArray{ 1, 2, 3, 4, 5 };
		for (auto val : testArray)
		{
			std::cout << val << std::endl;
		}

		// STACK
		Stack<int> vecStack = Stack<int>(testVec);
		vecStack.push(12);

		Stack<int, List<int>> listStack;
		listStack.push(2);
	}
	catch (std::exception& ex)
	{
		std::cerr << std::endl << ex.what() << std::endl;
	}

	return 0;
}

