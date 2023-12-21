#include <iostream>

#include "BinaryTree.h"

int main()
{
    my::BinaryTree<int> b{10, 8, 2, 1, 3, 4, 5, 6, 7, 18, 12, 13, 22, 21, 24, 20};
    // b.Remove(10);

    std::cout << b.Search(15) << std::endl;

    /*
    auto in_order  = b.InOrder();
    auto postorder = b.PostOrder();
    auto preorder  = b.PreOrder();
    */

    std::cout << "Max: " << b.FindMax() << "\nMin: " << b.FindMin() << std::endl;

    std::cout << "Height: " << b.Height() << std::endl;

    auto successor_to = 20;
    std::cout << "Successor to " << successor_to << " is: " << b.Successor(successor_to) << std::endl;
    std::cout << "Predecessor to " << successor_to << " is: " << b.Predecessor(successor_to) << std::endl;
    return 0;
}
