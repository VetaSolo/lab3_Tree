#pragma once
#include <iostream>
using namespace std;

class NodeTree
{
public:
    int number;
    NodeTree* root;
    NodeTree* left;
    NodeTree* right;
    NodeTree(int newnumber)
    {
        this->root = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->number = newnumber;
    }
};
class Node
{
public:
    int number;
    Node* next;
    NodeTree* tree;
    Node(int newnumber, NodeTree* tree = nullptr, Node* next = nullptr)
    {
        this->next = next;
        this->number = newnumber;
        this->tree = tree;
    }
};
class BST
{
public:
    ~BST()
    {
        while (count)
        {
            remove(head->number);
        }
    }
    bool contains(int number)
    {
        NodeTree* tree = head;
        while (tree)
        {
            if (number < tree->number)
                tree = tree->left;
            else if (number > tree->number)
                tree = tree->right;
            else if (number == tree->number) return true;
        }
        return false;
    }

    void insert(int newnumber)
    {
        if (!head) // exsist head or not
        {
            head = new NodeTree(newnumber);
            count = 1;
        }
        else
        {
            NodeTree* current = head;
            int last = count;
            if (!contains(newnumber))
            {
                while (last == count)
                {
                    if (newnumber < current->number)
                    {
                        if (current->left) current = current->left;
                        else
                        {
                            current->left = new NodeTree(newnumber);
                            current->left->root = current;
                            count++;
                        }
                    }
                    else if (newnumber > current->number)
                    {
                        if (current->right) current = current->right;
                        else
                        {
                            current->right = new NodeTree(newnumber);
                            current->right->root = current;
                            count++;
                        }
                    }
                }
            }
            else throw logic_error("the tree element already exists!");
        }
    }
    void remove(int number)
    {
        if (contains(number))
        {
            NodeTree* current = head;
            int last = count;
            while (number != current->number) // moves to element with number
            {
                if (number < current->number)
                {
                    current = current->left;
                }
                else if (number > current->number)
                {
                    current = current->right;
                }
            }
            NodeTree* remove = current;
            if ((!remove->left) && (!remove->right)) // if there is no left or right element, then the element is a sheet
            {
                current->number = remove->number;
                NodeTree* removeel = remove;
                if (remove->root)
                {
                    if (remove->root->right)
                    {
                        if (remove->root->right->number == current->number)
                            remove->root->right = nullptr;
                        else
                            remove->root->left = nullptr;
                    }
                }
                else remove = nullptr;
                delete removeel;
                removeel = nullptr;
                count--;
            }
            else if (!remove->left && remove->right)
            {
                if (current->root)
                {
                    current = current->root;
                    current->right = remove->right;
                    remove->right->root = current;
                    delete remove;
                    remove = nullptr;
                    count--;
                }
                else
                {
                    head = remove->right;
                    head->root = nullptr;
                    delete remove;
                    remove = nullptr;
                    count--;
                }
            }
            else if (!remove->right && remove->left)
            {
                if (current->root)
                {
                    current = current->root;
                    current->left = remove->left;
                    remove->left->root = current;
                    delete remove;
                    remove = nullptr;
                    count--;
                }
                else
                {
                    head = remove->left;
                    head->root = nullptr;
                    delete remove;
                    remove = nullptr;
                    count--;
                }
            }
            else // if there is both right and left
            {
                remove = remove->right;
                while (remove->left)
                    remove = remove->left;
                current->number = remove->number;
                current = remove->root;
                if (current->right)if (current->right->number == remove->number)
                    current->right = remove->right;
                if (current->left)if (current->left->number == remove->number)
                    current->left = remove->right;
                if (remove->right)
                    remove->right->root = current;
                delete remove;
                remove = nullptr;
                count--;
            }
        }
    }
private:
    size_t count = 0;
    NodeTree* head = nullptr;
};