#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "List.h"

using namespace std;

TEST_CASE("Test 1: Empty LinkedList creation") {
    LinkedList list;
    CHECK(list.getSize() == 0);
    CHECK(list.getFirstElement() == nullptr);
    CHECK(list.getLastElement() == nullptr);
}

TEST_CASE("Test 2: Insert at beginning") {
    LinkedList list;
    list.insertAtBeginning(10);
    list.insertAtBeginning(20);
    list.insertAtBeginning(30);
    
    CHECK(list.getSize() == 3);
    CHECK(list.getValueAt(0) == 30);
    CHECK(list.getValueAt(1) == 20);
    CHECK(list.getValueAt(2) == 10);
}

TEST_CASE("Test 3: Insert at end") {
    LinkedList list;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    
    CHECK(list.getSize() == 3);
    CHECK(list.getValueAt(0) == 10);
    CHECK(list.getValueAt(1) == 20);
    CHECK(list.getValueAt(2) == 30);
}

TEST_CASE("Test 4: Delete node at various positions") {
    LinkedList list;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.insertAtEnd(50);
    

    list.deleteNodeNumber(2);
    CHECK(list.getSize() == 4);
    CHECK(list.getValueAt(2) == 40);
    
    list.deleteNodeNumber(0);
    CHECK(list.getSize() == 3);
    CHECK(list.getValueAt(0) == 20);
    
    list.deleteNodeNumber(2);
    CHECK(list.getSize() == 2);
    CHECK(list.getValueAt(1) == 40);
}

TEST_CASE("Test 5: Copy constructor") {
    LinkedList list1;
    list1.insertAtEnd(1);
    list1.insertAtEnd(2);
    list1.insertAtEnd(3);
    list1.insertAtEnd(4);
    
    LinkedList list2(list1);
    
    CHECK(list2.getSize() == 4);
    CHECK(list2.getValueAt(0) == 1);
    CHECK(list2.getValueAt(1) == 2);
    CHECK(list2.getValueAt(2) == 3);
    CHECK(list2.getValueAt(3) == 4);
    
    list1.insertAtEnd(5);
    CHECK(list1.getSize() == 5);
    CHECK(list2.getSize() == 4);
}

TEST_CASE("Test 6: Positive prefix sum - all positive") {
    LinkedList list;
    list.insertAtEnd(5);
    list.insertAtEnd(3);
    list.insertAtEnd(2);
    list.insertAtEnd(1);
    
    CHECK(list.isPositivePrefixSum() == true);
    CHECK(list.isNegativePrefixSum() == false);
}

TEST_CASE("Test 7: Positive prefix sum - contains negative leading to non-positive sum") {
    LinkedList list;
    list.insertAtEnd(5);
    list.insertAtEnd(-3);
    list.insertAtEnd(-4);
    
    CHECK(list.isPositivePrefixSum() == false);
}

TEST_CASE("Test 8: Negative prefix sum - all negative") {
    LinkedList list;
    list.insertAtEnd(-5);
    list.insertAtEnd(-3);
    list.insertAtEnd(-2);
    list.insertAtEnd(-1);
    
    CHECK(list.isNegativePrefixSum() == true);
    CHECK(list.isPositivePrefixSum() == false);
}

TEST_CASE("Test 9: Negative prefix sum - contains positive") {
    LinkedList list;
    list.insertAtEnd(-5);
    list.insertAtEnd(3);
    list.insertAtEnd(-1);
    
    CHECK(list.isNegativePrefixSum() == true);
    
    list.insertAtEnd(10);
    CHECK(list.isNegativePrefixSum() == false);
}

TEST_CASE("Test 10: Pointer jumping algorithm") {
    LinkedList list;
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);
    
    list.performPointerJumping();
    
    CHECK(list.getSize() == 5);
    CHECK(list.getValueAt(0) == 1);
    CHECK(list.getValueAt(1) == 2);
    CHECK(list.getValueAt(2) == 3);
    CHECK(list.getValueAt(3) == 4);
    CHECK(list.getValueAt(4) == 5);
    
    Node* first = list.getFirstElement();
    CHECK(first != nullptr);
    CHECK(first->jump != nullptr);
}

TEST_CASE("Test 11: Mixed operations") {
    LinkedList list;
    
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    CHECK(list.getSize() == 3);
    
    list.insertAtBeginning(5);
    CHECK(list.getSize() == 4);
    CHECK(list.getValueAt(0) == 5);
    
    list.deleteNodeNumber(1);
    CHECK(list.getSize() == 3);
    CHECK(list.getValueAt(1) == 20);

    CHECK(list.isPositivePrefixSum() == true);
}

TEST_CASE("Test 12: Edge cases and boundary conditions") {
    LinkedList list;
    
    SUBCASE("Empty list operations") {
        CHECK(list.getSize() == 0);
        CHECK(list.getValueAt(0) == -1);
        CHECK(list.isPositivePrefixSum() == true);
        CHECK(list.isNegativePrefixSum() == true);
        list.deleteNodeNumber(0); 
        CHECK(list.getSize() == 0);
    }
    
    SUBCASE("Single element list") {
        list.insertAtEnd(42);
        CHECK(list.getSize() == 1);
        CHECK(list.getValueAt(0) == 42);
        CHECK(list.getFirstElement() == list.getLastElement());
        
        list.deleteNodeNumber(0);
        CHECK(list.getSize() == 0);
    }
    
    SUBCASE("Out of bounds access") {
        list.insertAtEnd(1);
        list.insertAtEnd(2);
        CHECK(list.getValueAt(10) == -1);
        CHECK(list.getValueAt(-1) == -1);
    }
    
    SUBCASE("Delete out of bounds") {
        list.insertAtEnd(1);
        list.insertAtEnd(2);
        int sizeBefore = list.getSize();
        list.deleteNodeNumber(10); 
        CHECK(list.getSize() == sizeBefore); 
    }
}
