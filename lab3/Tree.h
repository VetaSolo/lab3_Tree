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
class MyIterator
{
public:
    virtual ~MyIterator() {};
    virtual bool has_next() = 0;
    virtual int next() = 0;
};
class List // aka queue
{
public:
    List()
    {
        size = 0;
        head = nullptr;
        last = nullptr;
    }
    ~List()
    {
        clear();
    }
    void clear()
    {
        while (size) pop_front();
    }
    void save_list()
    {
        size = 0;
    }
    int get_elem(size_t index)//get element
    {
        if (size == index + 1)
        {
            return last->number;
        }
        else if (size > index + 1)
        {
            Node* current = head;
            for (size_t i = 0; i < index; i++, current = current->next); // moves the current list to index inclusive
            return current->number; // returns index number
        }
        else
        {
            throw out_of_range("index is entered incorrectly"); // error message
        }
    }
    NodeTree* get_elem_tree(size_t index)
    {
        if (size == index + 1)
        {
            return last->tree;
        }
        else if (size > index + 1)
        {
            Node* current = head;
            for (size_t i = 0; i < index; i++, current = current->next); // moves the current list to index inclusive
            return current->tree; // returns tree
        }
        else
        {
            throw out_of_range("index is entered incorrectly"); // error message
        }
    }
    void pop_front()
    {
        if (head)
        {
            Node* current = head->next;
            delete head;
            head = current;
            size--;
        }
    }
    bool contains(int number)
    {
        Node* current = head;
        while (current)
        {
            if (current->number == number)
                return true;
            current = current->next;
        }
        return false;
    }
    size_t get_size()
    {
        return size;
    }
    void push_back(int newnumber)
    {
        if (!head)
        {
            head = new Node(newnumber); // creates a list with newnumber
            last = head;
        }
        else
        {
            last->next = new Node(newnumber); // adds newnumber to the end of the list
            last = last->next;
        }
        size++;
    }
    void push_back(NodeTree* tree)
    {
        if (!head && tree)
        {
            head = new Node(0);
            last = head;
            head->tree = tree; // creates a list with tree
            size++;
        }
        else if (tree)
        {
            last->next = new Node(0);
            last = last->next;
            last->tree = tree;  // creates a list with tree
            size++;
        }
        else throw out_of_range("the tree does not exist!");
    }
    MyIterator* create_iterator()
    {
        return new My_List_Iterator(head);
    }
    
    class My_List_Iterator : public MyIterator
    {
    public:
        My_List_Iterator(Node* first)
        {
            current = first;
        }
        bool has_next() override
        {
            return current;
        }
        int next() override
        {
            if (current)
            {
                int temp = current->number;
                current = current->next;
                return temp;
            }
            return 0;
        }
    private:
        Node* current;
    };
private:
    Node* head = nullptr;
    Node* last = nullptr;
    size_t size;
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
    bool contains(int key)
    {
        NodeTree* tree = head;
        while (tree)
        {
            if (key < tree->number)
                tree = tree->left;
            else if (key > tree->number)
                tree = tree->right;
            else if (key == tree->number) return true;
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

    MyIterator* create_dft_iterator()
    {
        if (head)
        {
            List list;
            NodeTree* current = head;
            while (count > list.get_size())
            {
                while (current->left) // go left
                {
                    list.push_back(current->number);
                    current = current->left;
                }
                if (current->right)
                {
                    list.push_back(current->number);
                    current = current->right;
                    continue;
                }
                else list.push_back(current->number);
                while (current->root && count > list.get_size())
                {
                    current = current->root; // go to the root
                    if (current->right)
                    {
                        if (!list.contains(current->right->number))
                        {
                            current = current->right;
                            break;
                        }
                    }
                    if (current->left)
                    {
                        if (!list.contains(current->left->number))
                        {
                            current = current->left;
                            break;
                        }
                    }
                }
            }
            list.save_list(); //  prevents the removal of all items
            return list.create_iterator();
        }
        throw out_of_range("the tree does not exist!");
    }

    MyIterator* create_bft_iterator()
    {
        if (head)
        {
            List list1, list2;
            list1.push_back(head); // make head
            for (size_t i = 0; i < count; i++)
            {
                if (list1.get_elem_tree(i)->left)
                    list1.push_back(list1.get_elem_tree(i)->left);
                if (list1.get_elem_tree(i)->right)
                    list1.push_back(list1.get_elem_tree(i)->right);
            }
            for (size_t i = 0; i < list1.get_size(); i++)
                list2.push_back(list1.get_elem_tree(i)->number);
            list2.save_list();
            return list2.create_iterator();
        }
        throw out_of_range("the tree does not exist!");
    }
private:
    size_t count = 0;
    NodeTree* head = nullptr;
};
