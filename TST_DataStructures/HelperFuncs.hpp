// Used to remove duplicated code from test files

template<class Container, class T>
void ClearAndFill(Container& container, std::initializer_list<T> newVals)
{
	constexpr bool has_clear = requires(const Container & container)
	{
		container.clear();
	};

	if constexpr (has_clear)
	{
		container.clear();
		container = newVals;
	}
	else
	{
		throw std::runtime_error("[ERROR] Method Clear is undefined");
	}
}