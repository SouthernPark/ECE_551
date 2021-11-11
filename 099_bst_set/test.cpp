#include "bstset.h"

int main(void) {
  //create a BstMap
  BstSet<int> bmap;
  //add elements to the bmap
  bmap.add(30);
  bmap.add(20);
  bmap.add(10);
  bmap.add(25);

  bmap.print_tree();
  bmap.remove(30);
  std::cout << "after remove nodes\n";

  std::cout << "test copy constructor\n";
  BstSet<int> b1 = bmap;
  b1.print_tree();

  std::cout << "test assignment operator\n";
  BstSet<int> b2;
  b2 = bmap;
  b2.print_tree();
}
