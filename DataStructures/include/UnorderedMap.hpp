#pragma once

template<class Key, class T, class Hash, class KeyEqual, class Allocator = std::allocator<std::pair<const Key, T>>>
class UnorderedMap
{
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    // TODO as iterators get implemented
    //using iterator = 
    //using const_iterator = 
    //using local_iterator = 
    //using const_local_iterator = 
    //using node_type = 
    //using insert_return_type = 

    UnorderedMap() {}

    explicit UnorderedMap(size_type bucket_count, const Hash& hash = Hash(), const key_equal& equal = key_equal()) {}
    UnorderedMap(size_type bucket_count) : UnorderedMap(bucket_count, Hash(), key_equal()) {}
    UnorderedMap(size_type bucket_count, const hash& hash) : UnorderedMap(bucket_count, hash, key_equal()) {}

    template<std::input_iterator InputIt>
    UnorderedMap(InputIt first, InputIt last, size_type bucket_count = /*implementation-defined*/0, const Hash& hash = Hash(), const key_equal& equal = key_equal()) {}

    template<std::input_iterator InputIt>
    UnorderedMap(InputIt first, InputIt last, size_type bucket_count) : UnorderedMap(first, last, bucket_count, Hash(), key_equal()) {}

    template<std::input_iterator InputIt>
    UnorderedMap(InputIt first, InputIt last, size_type bucket_count, const Hash& hash) : UnorderedMap(first, last, bucket_count, hash, key_equal()) {}

    UnorderedMap(const UnorderedMap& other) {}
    UnorderedMap(UnorderedMap&& other) {}
    UnorderedMap(std::initializer_list<value_type> init, size_type bucket_count = /*implementation-defined*/0, const Hash& hash = Hash(), const key_equal& equal = key_equal()) {}
    UnorderedMap(std::initializer_list<value_type> init, size_type bucket_count) : UnorderedMap(init, bucket_count, Hash(), key_equal()) {}
    UnorderedMap(std::initializer_list<value_type> init, size_type bucket_count, const Hash& hash) : UnorderedMap(init bucket_count, hash, key_equal()) {}

    ~UnorderedMap() {}

    UnorderedMap& operator=(const UnorderedMap& other)
    {

    }
};