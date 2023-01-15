#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <exception>
#include <stdexcept>

using namespace std;

template <typename T>
class LinkedList {
public:
    // Constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Pushes new data to the back of the LL
    void push_back(T data);

    // Removes data at the front of the LL
    void remove_front();

    // Get data at the front of the LL
    T peek();

    // Get the size of the LL
    int size();

private:
    struct Node {
        T data;
        Node* next;
        Node(T newData) {
            data = newData;
            next = nullptr;
        }
    };
    Node* head;
    int sz;
};

template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    sz = 0;
}

template <typename T>
LinkedList<T>::~LinkedList(){
    Node* curr = head;
    while (head != nullptr) {
        delete curr;
        head = head->next;
        curr = head;
    }
}

template <typename T>
void LinkedList<T>::push_back(T data) {
    Node* newNode = new Node(data);
    if (head == nullptr)
        head = newNode;
    else {
        Node* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        curr->next = newNode;
    }
    sz++;
}

template <typename T>
void LinkedList<T>::remove_front() {
    if (sz == 0)
        throw out_of_range("Cannot remove from empty list.");
    Node* delNode = head;
    head = head->next;
    delete delNode;
    sz--;
}

template <typename T>
T LinkedList<T>::peek() {
    if (sz == 0)
        throw out_of_range("Cannot peek from empty list");
    return head->data;
}

template <typename T>
int LinkedList<T>::size() {
    return sz;
}

#endif