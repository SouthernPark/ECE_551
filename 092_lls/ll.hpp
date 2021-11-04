#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

class Tester;

class not_exist : public std::exception {
  const char * what() const throw() { return "required item does not exist"; }
};

template<typename T>
class LinkedList {
 public:
  //inner class Node
  class Node {
   public:
    T data;
    Node * prev;
    Node * next;
    Node(T val) : data(val), prev(NULL), next(NULL) {}
    Node(T val, Node * pre, Node * nxt) : data(val), prev(pre), next(nxt) {}
  };
  //set the head and tail for the ll
  Node * head;
  Node * tail;
  int size;

 public:
  //constructor
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  //copy constructor
  LinkedList(const LinkedList & item) : head(NULL), tail(NULL), size(0) {
    //loop through item and add at the back of other list
    Node * cur = item.head;
    while (cur != NULL) {
      //add the data at the end of the ll
      this->addBack(cur->data);
      //this->addBack() has already add up the size, do not need to add again size++;
      cur = cur->next;
    }
  }
  //assignment copy
  LinkedList & operator=(const LinkedList & item) {
    if (&item != this) {
      LinkedList res;
      Node * cur = item.head;
      while (cur != NULL) {
        res.addBack(cur->data);
        cur = cur->next;
      }
      //assert(temp.head->data == item.head->data);
      //delete
      Node * temp_head = head;
      while (temp_head != NULL) {
        Node * tmp = temp_head;
        temp_head = temp_head->next;
        delete tmp;
      }

      head = res.head;
      tail = res.tail;
      size = item.size;
      //prevent destructor destruct
      res.head = NULL;
      res.tail = NULL;
    }

    return *this;
  }
  ~LinkedList() {
    //remove all the nodes
    Node * cur = head;
    while (cur != NULL) {
      Node * temp = cur;
      cur = cur->next;
      delete temp;
    }
  }

  int getSize() const { return size; }

  void addFront(const T & item) {
    //check whether thel ll is empty
    if (head == NULL) {
      Node * temp = new Node(item);
      //set the head and tail
      head = temp;
      tail = temp;
      size++;
    }
    else {
      Node * temp = new Node(item, NULL, head);
      head->prev = temp;
      head = temp;
      size++;
      //no need to change the tail
    }
  }

  void addBack(const T & item) {
    //check if the ll is empty
    if (head == NULL) {
      Node * temp = new Node(item);
      //set the head and tail
      head = temp;
      tail = temp;
      size++;
    }
    else {
      Node * temp = new Node(item, tail, NULL);
      tail->next = temp;
      tail = temp;
      size++;
    }
  }

  //only remove the first element in the list
  bool remove(const T & item) {
    //check if there is an element in the list
    if (head == NULL) {
      return false;
    }

    //check in the ll if we can find an occurence
    Node * cur = head;
    while (cur != NULL) {
      if (cur->data == item) {
        break;
      }

      cur = cur->next;
    }

    //check whether we find the item
    if (cur == NULL) {
      return false;
    }
    //else we find the element
    //check whether there is just one element in the list
    if (cur->prev == NULL && cur->next == NULL) {
      delete cur;
      head = NULL;
      tail = NULL;
      size--;
      return true;
    }
    //if remove the first element
    else if (cur->prev == NULL) {
      head = cur->next;
      cur->next->prev = NULL;
      delete cur;
      size--;
      return true;
    }
    //if remove the last element
    else if (cur->next == NULL) {
      tail = cur->prev;
      cur->prev->next = NULL;
      delete cur;
      size--;
      return true;
    }
    //remove elements in the middle
    else {
      //Node * prev = cur->prev;
      cur->prev->next = cur->next;
      cur->next->prev = cur->prev;
      delete cur;
      size--;
      return true;
    }
  }

  T & operator[](int index) {
    Node * cur = head;
    while (cur != NULL && index != 0) {
      cur = cur->next;
      --index;
    }

    if (cur == NULL) {
      throw not_exist();
    }
    else {
      return cur->data;
    }
  }
  const T & operator[](int index) const {
    Node * cur = head;
    while (cur != NULL && index != 0) {
      cur = cur->next;
      --index;
    }

    if (cur == NULL) {
      throw not_exist();
    }
    else {
      const T & res = cur->data;
      return res;
    }
  }

  int find(const T & item) {
    int res = 0;
    Node * cur = head;
    while (cur != NULL) {
      if (cur->data == item) {
        return res;
      }
      cur = cur->next;
      res++;
    }

    return -1;
  }

  friend class Tester;
};

#endif
