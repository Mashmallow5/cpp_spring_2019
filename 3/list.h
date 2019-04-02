#ifndef BIGINT_LinkedList_H
#define BIGINT_LinkedList_H

#include <iostream>

class Node {
public:
    Node *next;
    int data;
};

using namespace std;

class LinkedList {
private:
    size_t length;
    Node *head;
public:
    LinkedList();

    ~LinkedList();

    void add(int);

    void print() const;

    size_t get_length() const;

    const int &operator[](size_t) const;

    int &operator[](size_t);

    void attach_to(const int);

    void insert(size_t, const int);

    void pop();
};

size_t LinkedList::get_length() const {
    return this->length;
}

LinkedList::LinkedList() {
    this->length = 0;
    this->head = nullptr;
}

LinkedList::~LinkedList() = default;

void LinkedList::add(const int new_data) {
    if (get_length() != 0) {
        Node *node = head;
        size_t i;
        for (i = 0; i < get_length() - 1; i++) {
            node = node->next;
        }
        node->next = new Node;
        node->next->data = new_data;
        node->next->next = nullptr;
        length++;
    } else {
        head = new Node;
        head->data = new_data;
        head->next = nullptr;
        length++;
    }
}

const int &LinkedList::operator[](size_t pos) const {
    Node *iter = head;
    size_t i;
    for (i = 0; i < pos; i++) {
        iter = iter->next;
    }
    return iter->data;
}

int &LinkedList::operator[](size_t pos) {
    Node *iter = head;
    size_t i;
    for (i = 0; i < pos; i++) {
        iter = iter->next;
    }
    return iter->data;
}

void LinkedList::pop() {
    Node *node = head;
    size_t i;
    for (i = 0; i < get_length() - 2; i++)
        node = node->next;
    node->next = nullptr;
    this->length -= 1;
}

void LinkedList::attach_to(const int item) {
    length += 1;
    Node *node = new Node;
    node->data = item;
    if (get_length() == 0) {
        this->head = node;
    } else {
        node->next = this->head;
        this->head = node;
    }
}

void LinkedList::insert(size_t index, const int item) {
    Node *node;
    if (index == 0) {
        node = new Node;
        node->data = item;
        node->next = head;
        head = node;
    } else {
        node = head;
        for (size_t i = 1; i < index; i++)
            node = node->next;
        Node *node2;
        node2 = new Node;
        node2->data = item;
        node2->next = node->next;
        node->next = node2;
    }
    length += 1;
}

void LinkedList::print() const {

    if (length == 0)
        std::cout << "Empty" << std::endl;
    else {
        std::cout << "Your number is-->" << std::endl;
        Node *node = head;
        std::cout << node->data << '\t';
        for (size_t i = 0; i < get_length() - 1; i++) {
            node = node->next;
            std::cout << node->data << '\t';
        }
        std::cout << std::endl << std::endl;
    }
}


#endif //BIGINT_LinkedList_H
