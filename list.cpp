#include <iostream>

class Node {
public:
    double data;
    Node* prev;
    Node* next;

public:
    Node(double data) {
        this->data = data;
        this->prev = this->next = NULL;
    }

};


class DoubleLinkedList {
public:
    Node* head;
    Node* tail;

public:
    DoubleLinkedList() {
        head = tail = NULL;
    }

    ~DoubleLinkedList() {
        while (head != NULL)
            pop_front();
    }

    // O(1)
    Node* push_front(double data) {
        Node* ptr = new Node(data);

        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;

        if (tail == NULL)
            tail = ptr;

        head = ptr;

        return ptr;
    }

    // O(1)
    Node* push_back(double data) {
        Node* ptr = new Node(data);

        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;

        if (head == NULL)
            head = ptr;

        tail = ptr;

        return ptr;
    }

    // O(1)
    void pop_front() {
        if (head == NULL) return;

        Node* ptr = head->next;
        if (ptr != NULL)
            ptr->prev = NULL;
        else
            tail = NULL;

        delete head;
        head = ptr;
    }

    // O(1)
    void pop_back() {
        if (tail == NULL) return;

        Node* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;

        delete tail;
        tail = ptr;
    }

    // O(n)
    // optimize start head or tail
    Node* getAt(int index) {
        if (index < 0) return NULL;

        Node* ptr = head;
        int n = 0;

        while (n != index) {
            if (ptr == NULL)
                return NULL;

            ptr = ptr->next;
            n++;
        }

        return ptr;
    }

    // O(n)
    Node* operator [] (int index) {
        return getAt(index);
    }

    // O(n)
    Node* insert(int index, double data) {
        Node* right = getAt(index);
        
        if (right == NULL) {
            return push_back(data);
        }

        Node* left = right->prev;

        if (left == NULL) {
            return push_front(data);
        }

        Node* ptr = new Node(data);

        ptr->next = right;
        ptr->prev = left;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    // O(n)
    void erase(int index) {
        Node* ptr = getAt(index);

        if (ptr == NULL) return;

        if (!ptr->prev) {
            pop_front();
            return;
        }

        if (!ptr->next) {
            pop_back();
            return;
        }

        Node* left = ptr->prev;
        Node* right = ptr->next;

        left->next = right;
        right->prev = left;

        delete ptr;
    }
    // if you know the pointer then insert, erase - O(1)
};


int main()
{
    // add except for operator []

    DoubleLinkedList lst;

    lst.push_back(1.0);
    lst.push_back(3.0);
    lst.push_back(4.0);
    lst.push_back(5.0);

    std::cout << lst[1]->data << std::endl;
    std::cout << lst[0]->data << std::endl;

    lst.insert(2, -5.0);
    lst.insert(20, -15.0);
    lst.erase(3);
    lst.erase(30);

    for (Node* ptr = lst.head; ptr != NULL; ptr = ptr->next)
        std::cout << ptr->data << " ";

    std::cout << std::endl;

    for (Node* ptr = lst.tail; ptr != NULL; ptr = ptr->prev)
        std::cout << ptr->data << " ";

    std::cout << std::endl;
    

    return 0;
}

