#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  //1. create a pq
  priority_queue_t pq;
  //2. push the char [0..257] into queue if its frequency > 0 (counts[i] > 0)
  //construct new node Node(i, counts[i])
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      Node * n = new Node(i, counts[i]);
      pq.push(n);
    }
  }

  if (pq.size() == 0) {
    return NULL;
  }

  //3. build the tree by removing two elements from queue
  //construct tree using new Node(left, right)
  //push the tree into queue

  //repeat step 3 until there is just one element in the queue

  while (pq.size() != 1) {
    //pop out two nodes
    Node * n1 = pq.top();
    pq.pop();
    Node * n2 = pq.top();
    pq.pop();

    //construc new tree use n1, n2 as left and right
    Node * tree = new Node(n1, n2);
    //push the tree to pq
    pq.push(tree);
  }

  //then only one node left in the pq which is a pointer to the root

  return pq.top();
}
