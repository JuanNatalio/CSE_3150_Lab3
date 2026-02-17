#ifndef LIST_H
#define LIST_H

#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node* jump;

    explicit Node(int value);
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();
    
    void insert(int value);
    void deleteAtPosition(int position);
    void clear();
    bool isPositivePrefixSum() const;
    bool isNegativePrefixSum() const;
    void performPointerJumping();
    
    Node* getHead() const;
    Node* getTail() const;
    int getSize() const;
};

#endif