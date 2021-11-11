#include "bstmap.h"

int main(void) {
  //create a BstMap
  BstMap<int, int> bmap;
  //add elements to the bmap
  bmap.add(30, 0);
  bmap.add(20, 0);
  bmap.add(10, 0);
  bmap.add(25, 0);

  bmap.print_tree();
  bmap.remove(30);
  std::cout << "after remove nodes\n";

  BstMap<int, int> b1 = bmap;
  b1.print_tree();
}
