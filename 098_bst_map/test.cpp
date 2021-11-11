#include "bstmap.h"

int main(void) {
  //create a BstMap
  BstMap<int, int> bmap;
  //add elements to the bmap
  bmap.add(6, 6);
  bmap.add(3, 3);
  bmap.add(2, 2);
  bmap.add(5, 5);
  bmap.add(11, 11);
  bmap.add(10, 10);
  bmap.add(13, 13);

  bmap.print_tree();
  //std::cout << "look up###########\n";

  //look up a key
  //const int x = bmap.lookup(13);

  std::cout << "delete node\n";

  bmap.remove(6);
  bmap.remove(13);
  bmap.remove(10);
  bmap.remove(3);
  bmap.remove(5);
  bmap.remove(2);
  bmap.remove(11);
  bmap.remove(6);
  bmap.print_tree();
}
