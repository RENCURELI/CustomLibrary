// For all Non-Modifying Sequence Operations -> https://en.cppreference.com/w/cpp/algorithm#Non-modifying_sequence_operations

// ======================================
// ==============   FIND   ==============
// ======================================

template<std::input_iterator InputIt, class T>
constexpr InputIt Find(InputIt first, InputIt last, const T& value)
{
	// We have a contiguous block of memory, we can optimize search
// 	if constexpr (_Vector_alg_in_find_is_safe<_InIt, _Ty>)
// 	{
// 
// 	}

	// We don't have contiguous memory, just brute force the search
	for (; first != last; ++first)
	{
		if (*first == value)
		{
			return first;
		}

		return last;
	}
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

		return last;
	}
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

		return last;
	}
}