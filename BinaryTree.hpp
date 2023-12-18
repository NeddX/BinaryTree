#ifndef MY_BINARY_TREE_IMPL_H
#define MY_BINARY_TREE_IMPL_H

#include <functional>

namespace my {
    template<typename T>
    BinaryTree<T>::Node::Node() = default;

    template<typename T>
    BinaryTree<T>::Node::Node(const T& val) : val(val) {}

    template<typename T>
    BinaryTree<T>::BinaryTree() = default;

    template<typename T>
    BinaryTree<T>::BinaryTree(const std::initializer_list<T> list)
    {
        for (const auto& ref : list)
            Insert(ref);
    }

    template<typename T>
    BinaryTree<T>::~BinaryTree()
    {
        Drop(true);
    }

    template<typename T>
    inline void BinaryTree<T>::Drop(const bool destructing)
    {
		static std::function<void(Node*)> recv = [&](Node* ptr)
		{
			if (ptr->left)
				recv(ptr->left);
			if (ptr->right)
				recv(ptr->right);

			delete ptr;
		};

		recv(m_Root);
		m_Root = nullptr;
    }

    template<typename T>
    void BinaryTree<T>::Insert(const T& val)
    {
		if (!m_Root)
			m_Root = new Node(val);
		else
		{
			auto* current = m_Root;
			while (current && current->val != val)
			{
				if (val < current->val)
				{
					if (!current->left)
					{
						current->left = new Node(val);
						break;
					}
					else
						current = current->left;
				}
				else
				{
					if (!current->right)
					{
						current->right = new Node(val);
						break;
					}
					else
						current = current->right;
				}
			}
		}
    }

    template<typename T>
    void BinaryTree<T>::Remove(const T& val)
    {
			
    }

    template<typename T>
    bool BinaryTree<T>::Search(const T& val)
    {
        return false;
    }
} // namespace my

#endif // MY_BINARY_TREE_IMPL_H
