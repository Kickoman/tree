#include <iostream>
#include "ATree.h"

using namespace std;

int main()
{
    OrderedTree<int> tree;
    tree.createRoot(5);
    tree.getRoot()->addChild(4);
    tree.getRoot()->addChild(8);

    cout << tree.size();
    return 0;
}
