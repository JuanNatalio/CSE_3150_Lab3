#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "List.h"

TEST_CASE("Single element list - tail points to itself") {
    LinkedList list;
    list.insert(42);
    
    REQUIRE(list.getHead() != nullptr);
    REQUIRE(list.getTail() != nullptr);
    REQUIRE(list.getHead() == list.getTail());
    REQUIRE(list.getHead()->next == list.getHead());
    REQUIRE(list.getSize() == 1);
}

TEST_CASE("Multiple elements - tail points to itself in circular list") {
    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    REQUIRE(list.getSize() == 3);
    REQUIRE(list.getTail()->next == list.getTail());
    REQUIRE(list.getHead()->data == 3);
    REQUIRE(list.getTail()->data == 1);
}

TEST_CASE("Delete function removes ith node correctly") {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    
    list.deleteAtPosition(1); 
    
    REQUIRE(list.getSize() == 2);
    REQUIRE(list.getHead()->data == 30);
    REQUIRE(list.getHead()->next->data == 10);
    REQUIRE(list.getTail()->data == 10);
}

TEST_CASE("Delete head node") {
    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    list.deleteAtPosition(0);  
    
    REQUIRE(list.getSize() == 2);
    REQUIRE(list.getHead()->data == 2);
    REQUIRE(list.getTail()->data == 1);
}

TEST_CASE("Delete tail node") {
    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    list.deleteAtPosition(2);
    
    REQUIRE(list.getSize() == 2);
    REQUIRE(list.getTail()->data == 2);
    REQUIRE(list.getTail()->next == list.getTail());
}

TEST_CASE("Copy constructor - creates independent list") {
    LinkedList list1;
    list1.insert(10);
    list1.insert(20);
    list1.insert(30);
    
    LinkedList list2 = list1;
    
    REQUIRE(list2.getSize() == list1.getSize());
    REQUIRE(list2.getHead()->data == list1.getHead()->data);
    REQUIRE(list2.getTail()->data == list1.getTail()->data);
    
    list1.deleteAtPosition(0);
    REQUIRE(list2.getSize() == 3);
    REQUIRE(list1.getSize() == 2);
}

TEST_CASE("Positive prefix sum - all running sums are positive") {
    LinkedList list;
    list.insert(5);
    list.insert(3);
    list.insert(2);

    REQUIRE(list.isPositivePrefixSum() == true);
    REQUIRE(list.isNegativePrefixSum() == false);
}

TEST_CASE("Negative prefix sum - all running sums are negative") {
    LinkedList list;
    list.insert(-1);
    list.insert(-2);
    list.insert(-3);
    
    REQUIRE(list.isNegativePrefixSum() == true);
    REQUIRE(list.isPositivePrefixSum() == false);
}

TEST_CASE("Mixed prefix sum - neither all positive nor all negative") {
    LinkedList list;
    list.insert(1);
    list.insert(-3);
    list.insert(2);
    
    REQUIRE(list.isPositivePrefixSum() == false);
    REQUIRE(list.isNegativePrefixSum() == false);
}

TEST_CASE("Pointer jumping algorithm - all elements point to tail") {
    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    
    list.performPointerJumping();
    
    Node* temp = list.getHead();
    while (temp != nullptr) {
        CHECK(temp->jump == list.getTail());
        if (temp == list.getTail()) break;
        temp = temp->next;
    }
}

TEST_CASE("Pointer jumping with two elements") {
    LinkedList list;
    list.insert(1);
    list.insert(2);
    
    list.performPointerJumping();
    
    REQUIRE(list.getHead()->jump == list.getTail());
    REQUIRE(list.getTail()->jump == list.getTail());
}

TEST_CASE("Clear function - deallocates all nodes") {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    
    REQUIRE(list.getSize() == 3);
    
    list.clear();
    
    REQUIRE(list.getSize() == 0);
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
}
