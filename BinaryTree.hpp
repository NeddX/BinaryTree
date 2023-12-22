#ifndef MY_BINARY_TREE_IMPL_H
#define MY_BINARY_TREE_IMPL_H

#include <functional>
#include <type_traits>

namespace my {
    template <typename T>
    BinaryTree<T>::Node::Node() = default;

    template <typename T>
    BinaryTree<T>::Node::Node(const T& val) : val(val)
    {
    }

    template <typename T>
    BinaryTree<T>::BinaryTree() = default;

    template <typename T>
    BinaryTree<T>::BinaryTree(const std::initializer_list<T> list)
    {
        for (const auto& ref : list)
            Insert(ref);
    }

    template <typename T>
    BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
    {
        if (other.m_Root)
        {
            std::function<void(Node*,Node*&)> recv = [&](Node* ptr, Node*& root)
            {
                root = new Node(ptr->val);
                if (ptr->left)
                    recv(ptr->left, root->left);
                if (ptr->right)
                    recv(ptr->right, root->right);
            };
            recv(other.m_Root, m_Root);
            m_Count = other.m_Count;
        }
    }

    template <typename T>
    BinaryTree<T>::BinaryTree(BinaryTree<T>&& other) noexcept
    {
        if (other.m_Root)
        {
            m_Root = other.m_Root;
            m_Count = other.m_Count;
            other.m_Root = nullptr;
            other.m_Count = 0;
        }
    }

    template <typename T>
    BinaryTree<T>::~BinaryTree()
    {
        Drop(true);
    }

    template <typename T>
    BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) const
    {
        if (this == &other)
            return *this;

        if (m_Root)
            Drop();

        if (other.m_Root)
        {
            std::function<void(Node*,Node*&)> recv = [&](Node* ptr, Node*& root)
            {
                root = new Node(ptr->val);
                if (ptr->left)
                    recv(ptr->left, root->left);
                if (ptr->right)
                    recv(ptr->right, root->right);
            };
            recv(other.m_Root, m_Root);
            m_Count = other.m_Count;
        }

        return *this;
    }

    template <typename T>
    BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& other) noexcept
    {
        if (this == &other)
            return *this;

        if (m_Root)
            Drop();

        if (other.m_Root)
        {
            m_Root = other.m_Root;
            m_Count = other.m_Count;
            other.m_Root = nullptr;
            other.m_Count = 0;
        }

        return *this;
    }

    template <typename T>
    inline void BinaryTree<T>::Drop(const bool destructing)
    {
        std::function<void(Node*)> recv = [&](Node* ptr)
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

    template <typename T>
    void BinaryTree<T>::Insert(const T& val)
    {
        if (std::is_arithmetic<T>::value)
            if (val < 0)
                return;

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
                        ++m_Count;
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
                        ++m_Count;
                        break;
                    }
                    else
                        current = current->right;
                }
            }
        }
    }

    template <typename T>
    void BinaryTree<T>::Remove(const T& val)
    {
        bool found = false;
        auto* current = m_Root;
        auto* prev = current;
        while (current)
        {
            prev = current;
            if (current->val == val)
                found = true;
            else if (current->val > val)
                current = current->left;
            else
                current = current->right;
        }

        if (!found) return;

        if (!current->right)
        {
            if (current->left)
            {
                if (prev->left == current)
                    prev->left = current->left;
                else
                    prev->right = current->right;

                delete current;
                return;
            }
            else // Leaf
            {
                if (prev->left == current)
                    prev->left = nullptr;
                else

                    prev->right = nullptr;
                delete current;
                return;
            }
        }
        else
        {
            // The mindblowing logic goes here
            auto* current2 = current->right;
            while (current2->left)
                current2 = current2->left;
            
            if (prev->left == current)
                prev->left = current2;
            else
                prev->right = current2;
        }
    }

    template <typename T>
    bool BinaryTree<T>::Search(const T& val) const noexcept
    {
        auto* ptr = m_Root;
        while (ptr)
        {
            if (ptr->val == val)
                return true;
            else if (ptr->val > val)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        return false;
    }

    template <typename T>
    std::vector<T> BinaryTree<T>::InOrder() const noexcept
    {
        std::vector<T>                    vec;
        std::function<void(Node*)> recv = [&](Node* ptr)
        {
            if (ptr->left)
                recv(ptr->left);

            vec.push_back(ptr->val);

            if (ptr->right)
                recv(ptr->right);
        };

        vec.reserve(m_Count);
        recv(m_Root);
        return vec;
    }

    template <typename T>
    std::vector<T> BinaryTree<T>::PostOrder() const noexcept
    {
        std::vector<T>                    vec;
        std::function<void(Node*)> recv = [&](Node* ptr)
        {
            if (ptr->left)
                recv(ptr->left);

            if (ptr->right)
                recv(ptr->right);

            vec.push_back(ptr->val);
        };

        vec.reserve(m_Count);
        recv(m_Root);
        return vec;
    }

    template <typename T>
    std::vector<T> BinaryTree<T>::PreOrder() const noexcept
    {
        std::vector<T>                    vec;
        std::function<void(Node*)> recv = [&](Node* ptr)
        {
            vec.push_back(ptr->val);

            if (ptr->left)
                recv(ptr->left);

            if (ptr->right)
                recv(ptr->right);
        };

        vec.reserve(m_Count);
        recv(m_Root);
        return vec;
    }

    template <typename T>
    T BinaryTree<T>::FindMax() const noexcept
    {
        auto* current = m_Root;
        while (current->right)
            current = current->right;
        return current->val;
    }

    template <typename T>
    T BinaryTree<T>::FindMin() const noexcept
    {
        auto* current = m_Root;
        while (current->left)
            current = current->left;
        return current->val;
    }

    template <typename T>
    usize BinaryTree<T>::Height() const noexcept
    {
        usize                             height = 0;
	    usize                             max = 0;
        std::function<void(Node*)> recv   = [&](Node* ptr)
        {
	        ++height;	
            if (ptr->left)
                recv(ptr->left);
            if (ptr->right)
                recv(ptr->right);

	        if (max < height)
		        max = height;
            --height;
        };
        recv(m_Root);
        return max;
    }

    template <typename T>
    std::vector<T> BinaryTree<T>::Serialize() const noexcept
    {
        return InOrder();   
    }

    template <typename T>
    const T& BinaryTree<T>::Successor(const T& val) const
    {
        auto* current = m_Root;
        Node* ancestor = nullptr;
        while (current)
        {
            if (current->val == val)
            {
                if (!ancestor && !current->right)
                    return current->val;
                else if (!current->right)
                    return ancestor->val;
                else
                    return current->right->val;
            }
            else if (current->val > val)
                    ancestor = current;

            if (current->val > val)
                current = current->left;
            else
                current = current->right;
        }

        throw std::invalid_argument("Value does not exist.");
    }

    template <typename T>
    const T& BinaryTree<T>::Predecessor(const T& val) const
    {
        auto* current = m_Root;
        Node* ancestor = nullptr;
        while (current)
        {
            if (current->val == val)
            {
                if (!ancestor && !current->left)
                    return current->val;
                else if (!current->left)
                    return ancestor->val;
                else
                    return current->left->val;
            }
            else if (current->val < val)
                    ancestor = current;

            if (current->val > val)
                current = current->left;
            else
                current = current->right;
        }

        throw std::invalid_argument("Value does not exist.");
    }

    template <typename T>
    std::vector<T> BinaryTree<T>::RangeQuery(const T& begin, const T& end) const
    {
        std::vector<T> vec;
        const std::function<void(Node*)> recv = [&](Node* ptr)
        {
            if (ptr->val > begin && ptr->val < end)
            {
                vec.emplace_back(ptr->val);
                if (ptr->left)
                    recv(ptr->left);
                if (ptr->right)
                    recv(ptr->right);
            }
            else
            {
                if (ptr->val < begin)
                {
                    if (ptr->right)
                        recv(ptr->right);
                }
                else if (ptr->val > end)
                {
                    if (ptr->left)
                        recv(ptr->left);
                }
            }
        };
        recv(m_Root);
        return vec;
    }
} // namespace my

#endif // MY_BINARY_TREE_IMPL_H
