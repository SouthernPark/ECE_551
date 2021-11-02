#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(2);
    //not connect head to it
    assert(il.head != NULL);
    //not connect tail to it
    assert(il.tail != NULL);
    //tail and head not point to the same thing
    assert(il.head == il.tail);
    //forget to add size
    assert(il.getSize() == 1);
    //forget set the prev and next to NULL if there is only one element
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    //data is not set to 2
    assert(il.head->data == 2);

    /* Add another element */
    il.addFront(3);
    //lose the head and tail pointer
    assert(il.head != NULL);
    assert(il.tail != NULL);
    //put the new front node to the wrong position
    assert(il.head->data == 3);
    //forget to add the size
    assert(il.getSize() == 2);
    //tail is still point at the previous front
    assert(il.tail->data == 2);
    //did not connect the second node with the first node correctly through next
    assert(il.head->next != NULL);
    assert(il.head->next->data == 2);
    //did not connect the second node with the first node correctly through prev
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 3);
    //the last node's next point to null
    assert(il.tail->next == NULL);

    /* Add the third node */

    il.addFront(4);
    //lost head or tail
    assert(il.head != NULL);
    assert(il.tail != NULL);
    //the size should increase by one
    assert(il.getSize() == 3);
    //tail should always points to the same node
    assert(il.tail->data == 2);
    //the front element should be 4
    assert(il.head->data == 4);
    //the element after front should not lost
    assert(il.head->next != NULL);
    assert(il.head->next->data == 3);
  }
  // many more tester methods

  void testAddBack() {
    IntList il;
    il.addBack(2);

    //not connect head to it
    assert(il.head != NULL);
    //not connect tail to it
    assert(il.tail != NULL);
    //tail and head not point to the same thing
    assert(il.head == il.tail);
    //forget to add size
    assert(il.getSize() == 1);
    //forget set the prev and next to NULL if there is only one element
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    //data is not set to 2
    assert(il.head->data == 2);

    /*add another elements at back*/
    il.addBack(3);
    //head or tail should not be changed
    assert(il.head != NULL);
    assert(il.tail != NULL);
    //the tail should now point to 3
    assert(il.tail->data == 3);
    //the next of first elem shoud change
    assert(il.head->next != NULL && il.head->next->data == 3 && il.head->prev == NULL);
    //the prev of the tial should be chaneg
    assert(il.tail->prev != NULL && il.tail->prev->data == 2 && il.tail->next == NULL);
  }

  void testCopyConstructor() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    IntList il_copy(il);
    //check elements in il_copy
    assert(il_copy.head != NULL && il_copy.tail != NULL);
    //check first element
    assert(il_copy.head->data == 1 && il_copy.head->prev == NULL &&
           il_copy.head->next != NULL);

    //check the second element
    assert(il_copy.tail->data == 2 && il_copy.tail->prev != NULL &&
           il_copy.tail->prev != NULL);

    //chekc the size
    assert(il_copy.getSize() == 2);

    //chekc if we can get access to the second ele through first
    assert(il_copy.head->next->data == 2);

    //check if we get access to the first ele through last
    assert(il_copy.tail->prev->data == 1);

    //if ther first ele in il changes, il_copy should not change
    il.head->data = 3;
    assert(il_copy.head->data == 1);

    //if the second element changes in il, il_copy should not change
    il.tail->data = 4;
    assert(il_copy.tail->data == 2);
  }

  void testAssignmentConstructor() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    IntList il_copy;
    il_copy.addBack(3);
    il_copy.addBack(4);
    il_copy.addBack(5);

    il_copy = il;
    assert(il_copy.getSize() == 2);
    assert(il_copy.head != NULL && il_copy.tail != NULL);
    assert(il_copy.head->data == 1);
    assert(il_copy.tail->data == 2);
    assert(il_copy.tail->next == NULL);
    //when original changes, the copy will not change
    il.head->data = 100;
    assert(il_copy.head->data == 1);

    il.tail->data = 100;
    assert(il_copy.tail->data == 2);
  }

  void testDestructor() {
    IntList * il = new IntList();
    assert(il != NULL);
    il->addBack(1);
    il->addBack(2);
    il->addBack(3);
    IntList::Node * temp_head = il->head;
    IntList::Node * temp_middle = il->head->next;
    IntList::Node * temp_tail = il->tail;
    delete il;
    //assert(il == NULL);
    //assert(temp_head == NULL && temp_middle == NULL && temp_tail == NULL);
  }

  void testRemove() {
    IntList il;
    //add one and remove one
    il.addBack(1);
    assert(il.remove(1) == true);
    assert(il.head == NULL && il.tail == NULL);
    assert(il.remove(1) == false);  //remvoe one that does not exist
    assert(il.getSize() == 0);

    //remove from many
    il.addBack(1);
    il.addBack(2);
    //il.addBack(2);
    il.addBack(3);

    assert(il.remove(4) == false);
    assert(il.remove(2) == true);
    //check the pointer is connected correctly
    assert(il.head->next->data == 3);
    assert(il.tail->prev->data == 1);
    assert(il.getSize() == 2);

    //remove the last element
    assert(il.remove(3) == true);
    assert(il.head->next == NULL);
    assert(il.getSize() == 1);
    il.addBack(2);
    il.addBack(3);
    //remove the first ele
    assert(il.remove(1) == true);
    assert(il.head->prev == NULL);
    assert(il.head->data == 2);
    assert(il.head->next->data == 3);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopyConstructor();

  t.testAssignmentConstructor();
  t.testDestructor();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
