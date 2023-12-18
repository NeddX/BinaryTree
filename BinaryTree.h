#ifndef MY_BINARY_TREE_H
#define MY_BINARY_TREE_H

#include <initializer_list>
#include <cstdint>

using u8 = std::uint8_t;
using i8 = std::int8_t;
using u16 = std::uint16_t;
using i16 = std::int16_t;
using u32 = std::uint32_t;
using i32 = std::int32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using usize = std::size_t;
using intptr = std::intptr_t;
using uintptr = std::uintptr_t;
using ptrdiff = std::ptrdiff_t;

namespace my {
    template<typename T>
    class BinaryTree
    {
	public:
        struct Node
        {
            Node* left = nullptr;
            Node* right = nullptr;
            T val{};

        public:
            Node();
            Node(const T& ref);
        };

    private:
        Node* m_Root = nullptr;


    public:
        BinaryTree();
        BinaryTree(const std::initializer_list<T> list);
        ~BinaryTree();

    private:
        inline void Drop(const bool destructing = false);

    public:
        void Insert(const T& val);
        void Remove(const T& val);
        bool Search(const T& val);
    };
} // namespace my

#include "BinaryTree.hpp"

#endif // MY_BINARY_TREE_H
