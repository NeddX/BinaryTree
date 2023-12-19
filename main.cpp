#include <iostream>

#include "BinaryTree.h"

int main()
{
    my::BinaryTree<int> b{ 20, 1, 0, 30, 25, 40, 24 };
    // b.Remove(10);

    std::cout << b.Search(15) << std::endl;

    /*
    auto in_order  = b.InOrder();
    auto postorder = b.PostOrder();
    auto preorder  = b.PreOrder();
    */

    std::cout << "Max: " << b.FindMax() << "\nMin: " << b.FindMin() << std::endl;

    std::cout << "Height: " << b.Height() << std::endl;
    return 0;
}
