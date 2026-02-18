#include "List.h"

using namespace std;

Node::Node(int value) : data(value), next(this), jump(nullptr) {}

ostream& operator<<(ostream& os, const Node& node) {
    os << node.data;
    return os;
}

LinkedList::LinkedList() : root(nullptr) {}

LinkedList::LinkedList(const LinkedList& fromLL) {
    if (nullptr == fromLL.root) {
        root = nullptr;
        return;
    }
    root = new Node(fromLL.root->data);
    Node* currentOld = fromLL.root;
    Node* newList = root;
    while (currentOld != currentOld->next) {
        newList->next = new Node(currentOld->next->data);
        currentOld = currentOld->next;
        newList = newList->next;
    }
    newList->next = newList; 
}

LinkedList::~LinkedList() {
    Node* current = root;
    if (nullptr != root) {
        while (current != current->next) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        delete current;
    }
    root = nullptr;
}

void LinkedList::insertAtBeginning(int val) {
    if (nullptr == root) {
        root = new Node(val);
    } else {
        Node* newNode = new Node(val);
        newNode->next = root;
        root = newNode;
    }
}

void LinkedList::insertAtEnd(int val) {
    Node* newNode = new Node(val);
    if (!root) {
        root = newNode;
        return;
    }
    Node* current = root;
    while (current != current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void LinkedList::deleteNodeNumber(int nodeNumber) {
    if (!root) return;
    
    if (0 == nodeNumber) {
        Node* temp = root;
        if (root == root->next) {
            root = nullptr;
        } else {
            root = root->next;
        }
        delete temp;
        return;
    }
    
    int count = 0;
    Node* lag = nullptr;
    Node* current = root;
    
    while (current != current->next && count < nodeNumber) {
        count++;
        lag = current;
        current = current->next;
    }
    
    if (count == nodeNumber && lag != nullptr) {
        if (current == current->next) {
            lag->next = lag;
        } else {
            lag->next = current->next;
        }
        delete current;
    }
}

int LinkedList::getSize() const {
    if (!root) return 0;
    
    int size = 0;
    Node* current = root;
    if (current == current->next) {
        return 1;
    }
    
    while (current != current->next) {
        size++;
        current = current->next;
    }
    return size + 1;
}

int LinkedList::getValueAt(int position) const {
    if (!root) return -1;
    
    if (0 == position) {
        return root->data;
    }
    
    int count = 0;
    Node* current = root;
    while (current != current->next && count < position) {
        count++;
        current = current->next;
    }
    
    if (count == position) {
        return current->data;
    }
    return -1; 
}

Node* LinkedList::getFirstElement() const {
    return root;
}

Node* LinkedList::getLastElement() const {
    if (!root) return nullptr;
    
    Node* current = root;
    while (current != current->next) {
        current = current->next;
    }
    return current;
}

bool LinkedList::isPositivePrefixSum() const {
    if (!root) return true; 
    
    int prefixSum = 0;
    Node* current = root;
    
    while (current != current->next) {
        prefixSum += current->data;
        if (prefixSum <= 0) return false;
        current = current->next;
    }

    prefixSum += current->data;
    return prefixSum > 0;
}

bool LinkedList::isNegativePrefixSum() const {
    if (!root) return true; 
    
    int prefixSum = 0;
    Node* current = root;
    
    while (current != current->next) {
        prefixSum += current->data;
        if (prefixSum >= 0) return false;
        current = current->next;
    }

    prefixSum += current->data;
    return prefixSum < 0;
}

void LinkedList::performPointerJumping() {
    if (!root) return;
    
    Node* current = root;
    while (current != current->next) {
        current->jump = current->next;
        current = current->next;
    }
    current->jump = current; 
    
    int size = getSize();
    int iterations = 0;
    while ((1 << iterations) < size) {  
        current = root;
        while (current != current->next) {
            if (current->jump && current->jump != current->jump->next) {
                current->jump = current->jump->jump;
            }
            current = current->next;
        }

        if (current->jump && current->jump != current->jump->next) {
            current->jump = current->jump->jump;
        }
        iterations++;
    }
}

void LinkedList::copyAllNodesAddresses() {
    nodeAddresses.clear();
    int size = getSize();
    if (size > 0) {
        Node* current = root;
        while (current != current->next) {
            nodeAddresses.push_back(static_cast<void*>(current));
            current = current->next;
        }
        nodeAddresses.push_back(static_cast<void*>(current));
    }
}

void LinkedList::printTableNodesNextValue() const {
    if (!root) return;
    
    cout << "Node Address\t\tNext Pointer\t\tJump Pointer\t\tData" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    Node* current = root;
    while (current != current->next) {
        cout << current << "\t" << current->next << "\t" 
             << current->jump << "\t" << current->data << endl;
        current = current->next;
    }

    cout << current << "\t" << current->next << "\t" 
         << current->jump << "\t" << current->data << endl;
}

void LinkedList::printJumpPointers() const {
    if (!root) {
        cout << "Empty list" << endl;
        return;
    }
    
    cout << "Jump pointers: ";
    Node* current = root;
    while (current != current->next) {
        cout << "[" << current->data << "->";
        if (current->jump) cout << current->jump->data;
        else cout << "null";
        cout << "] ";
        current = current->next;
    }

    cout << "[" << current->data << "->";
    if (current->jump) cout << current->jump->data;
    else cout << "null";
    cout << "]" << endl;
}

ostream& operator<<(ostream& os, const LinkedList& linkedList) {
    Node* current = linkedList.root;
    if (nullptr == linkedList.root) {
        return os;
    } else {
        while (current != current->next) {
            os << *current << " ";
            current = current->next;
        }
        os << *current;
    }
    return os;
}