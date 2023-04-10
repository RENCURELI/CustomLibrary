#include <iostream>

#include "List.hpp"
#include "FList.hpp"

#include "Array.hpp"
#include "Vector.hpp"

#include "Stack.hpp"

int main()
{
	std::cout << "Hello World! \n";

	try
	{
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

		vec.insert(1, 3.7f);
		vec.PrintVector();

		Vector<int> testVec = { 1, 2, 3, 4, 5, 6, 7 };
		testVec.erase(6);
		testVec.resize(4);
		std::cout << "Test Vector after resize" << "\n";
		testVec.PrintVector();

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

