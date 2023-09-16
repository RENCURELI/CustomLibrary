// For all Non-Modifying Sequence Operations -> https://en.cppreference.com/w/cpp/algorithm#Non-modifying_sequence_operations
#include <iterator>
#include <future>
#include <functional>
#include <xmemory>

// ======================================
// ==============   FIND   ==============
// ======================================

// Used when running async find on contiguous iterator containers
template<std::input_iterator InputIt, class T>
bool FindAsync(InputIt first, InputIt last, const T& value, InputIt& outVal)
{
	for (; first != last; ++first)
	{
		if (*first == value)
		{
			outVal = first;
			return true;
		}
	}

	return false;
}

template<std::input_iterator InputIt, class T>
constexpr InputIt Find(InputIt first, InputIt last, const T& value)
{
	// We have a contiguous block of memory, we can optimize search using threads
	if constexpr (std::_Iterator_is_contiguous<InputIt>)
	{
		// We get the mid point between both iterators
		size_t midPoint = (last - first) / 2;

		InputIt out1 = first; // We copy one of the iterators
		InputIt out2 = first; // We copy one of the iterators
		std::vector<std::future<bool>> results;

		// We open two threads to search on both halves
		results.push_back(std::async(std::launch::async, &FindAsync<InputIt, T>, first, first + midPoint, value, std::ref(out1)));
		results.push_back(std::async(std::launch::async, &FindAsync<InputIt, T>, first + midPoint, last, value, std::ref(out2)));

		for (int i = 0; i < 2; ++i)
		{
			if (results[0].get() == true)
			{
				return out1;
			}
			else if (results[1].get() == true)
			{
				return out2;
			}
			else
			{
				return last;
			}
		}
	}

	// We don't have contiguous memory, just brute force the search
	for (; first != last; ++first)
	{
		if (*first == value)
		{
			return first;
		}
	}

	return last;
}

template<std::input_iterator InputIt, class UnaryPredicate>
InputIt FindIf(InputIt first, InputIt last, UnaryPredicate p)
{
	for (; first != last; ++first)
	{
		if (p(*first) == true)
		{
			return first;
		}
	}

	return last;
}

template<std::input_iterator InputIt, class UnaryPredicate>
InputIt FindIfNot(InputIt first, InputIt last, UnaryPredicate p)
{
	for (; first != last; ++first)
	{
		if (!p(*first) == true)
		{
			return first;
		}
	}

	return last;
}