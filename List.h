#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* jump; 

    explicit Node(int value);
    friend ostream& operator<<(ostream& os, const Node& node);
};

class LinkedList {
    friend ostream& operator<<(ostream& os, const LinkedList& linkedList);
    
private:
    Node* root;
    vector<void*> nodeAddresses;

public:
    LinkedList();
    LinkedList(const LinkedList& fromLL); 
    ~LinkedList();
    

    void insertAtBeginning(int val);
    void insertAtEnd(int val);
    void deleteNodeNumber(int nodeNumber); 
    

    int getSize() const;
    int getValueAt(int position) const;
    Node* getFirstElement() const;
    Node* getLastElement() const;
    
    bool isPositivePrefixSum() const;  
    bool isNegativePrefixSum() const; 
    void performPointerJumping();    
    
    void copyAllNodesAddresses();
    void printTableNodesNextValue() const;
    void printJumpPointers() const;
};

ostream& operator<<(ostream& os, const LinkedList& linkedList);

#endif