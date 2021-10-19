#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  data = NULL;
  numElements = 0;
}
IntArray::IntArray(int n) {
  data = new int[n];
  numElements = n;
}

//deep copy the array specified in rhs
//used for the this does not eixst
IntArray::IntArray(const IntArray & rhs) {
  //remove the original data
  //delete[] data;
  data = new int[rhs.numElements];
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }
  numElements = rhs.numElements;
}
IntArray::~IntArray() {
  delete[] data;
}

//deep assign
//used for this exist
IntArray & IntArray::operator=(const IntArray & rhs) {
  delete[] data;
  data = new int[rhs.numElements];
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }

  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index < numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }

  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    s << rhs[i] << ", ";
  }
  s << "}";

  return s;
}
