#include <iostream>
#include "Tree.h"
using namespace std;

int main()
{
    BST tree;

    tree.insert(1);
    cout <<"1 - elem exsist, 0 - not exsist" << endl;
    cout <<"Elem 1 - " << tree.contains(1) << endl;
    tree.insert(3);
    cout << "Elem 3 - " << tree.contains(3) << endl;
    tree.insert(2);
    cout << "Elem 2 - " << tree.contains(2) << endl;
    tree.insert(0);
    cout << "Elem 0 - " << tree.contains(0) << endl;
    tree.insert(90);
    cout << "Elem 545533 - " << tree.contains(54553) << endl;
    return 0;
}