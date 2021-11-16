#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!

  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    //then the bit string represent the symbol
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
    return;
  }

  assert(left != NULL && right != NULL);

  left->buildMap(b.plusZero(), theMap);
  right->buildMap(b.plusOne(), theMap);
  return;
}
