#include <iostream>

#include "BinaryTree.h"

int main()
{
    my::BinaryTree<int> b;
    b.Insert(10);
    b.Insert(20);
    b.Insert(1);
    b.Insert(15);
    // b.Remove(10);

    std::cout << b.Search(15) << std::endl;

    auto inorder = b.InOrder();
    /*
    auto postorder = b.PostOrder();
    auto preorder = b.PreOrder();

    std::cout << "Max: " << b.FindMax() << "\nMin: " << b.FindMin() << std::endl;
    */
    return 0;
}
