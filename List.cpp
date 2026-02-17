#include "List.h"

Node::Node(int value) {
    data = value;
    next = nullptr;
    jump = nullptr;
}

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

LinkedList::LinkedList(const LinkedList& other) {
    head = nullptr;
    tail = nullptr;
    size = 0;
    
    if (other.head == nullptr) return;
    
    // Collect all values in order
    int* values = new int[other.size];
    Node* temp = other.head;
    for (int i = 0; i < other.size; i++) {
        values[i] = temp->data;
        if (i < other.size - 1) {
            temp = temp->next;
        }
    }
    
    for (int i = other.size - 1; i >= 0; i--) {
        insert(values[i]);
    }
    
    delete[] values;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insert(int value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        newNode->next = newNode;
        newNode->jump = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

void LinkedList::deleteAtPosition(int position) {
    if (head == nullptr || position < 0 || position >= size) {
        return;
    }
    
    if (position == 0) {
        Node* temp = head;
        if (size == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
        }
        delete temp;
        size--;
        return;
    }
    
    Node* temp = head;
    for (int i = 0; i < position - 1; i++) {
        temp = temp->next;
    }
    
    Node* nodeToDelete = temp->next;
    if (nodeToDelete == tail) {
        tail = temp;
        temp->next = temp;
    } else {
        temp->next = nodeToDelete->next;
    }
    delete nodeToDelete;
    size--;
}

void LinkedList::clear() {
    if (head == nullptr) return;
    
    Node* temp = head;
    Node* nextNode;
    
    if (tail != nullptr) {
        tail->next = nullptr;
    }
    
    while (temp != nullptr) {
        nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool LinkedList::isPositivePrefixSum() const {
    if (head == nullptr) return true;
    
    int prefixSum = 0;
    Node* temp = head;
    int count = 0;
    
    while (count < size) {
        prefixSum += temp->data;
        if (prefixSum <= 0) {
            return false;
        }
        count++;
        if (count < size) {
            temp = temp->next;
        }
    }
    return true;
}

bool LinkedList::isNegativePrefixSum() const {
    if (head == nullptr) return true;
    
    int prefixSum = 0;
    Node* temp = head;
    int count = 0;
    
    while (count < size) {
        prefixSum += temp->data;
        if (prefixSum >= 0) {
            return false;
        }
        count++;
        if (count < size) {
            temp = temp->next;
        }
    }
    return true;
}

void LinkedList::performPointerJumping() {
    if (head == nullptr || size <= 1) {
        return;
    }
    
    Node* temp = head;
    while (true) {
        temp->jump = temp->next;
        if (temp == tail) break;
        temp = temp->next;
    }
    
    bool changed = true;
    while (changed) {
        changed = false;
        temp = head;
        
        while (true) {
            if (temp->jump != tail) {
                if (temp->jump->jump != nullptr && temp->jump->jump != temp->jump) {
                    temp->jump = temp->jump->jump;
                    changed = true;
                } else {
                    temp->jump = tail;
                }
            }
            if (temp == tail) break;
            temp = temp->next;
        }
    }
}

Node* LinkedList::getHead() const {
    return head;
}

Node* LinkedList::getTail() const {
    return tail;
}

int LinkedList::getSize() const {
    return size;
}
