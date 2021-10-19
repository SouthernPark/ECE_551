#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[r];
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}

//copy constructer
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns) {
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }

  //copy
  for (int i = 0; i < numRows; i++) {
    *rows[i] = *rhs.rows[i];
  }
}
IntMatrix::~IntMatrix() {
  //destructor
  //destruct rows
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  //check if this == rhs
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs.numColumns);
    }

    //copy
    for (int i = 0; i < rhs.numRows; i++) {
      *temp[i] = *rhs.rows[i];
    }

    //remvoe old rows
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;

    //give temp to rows
    rows = temp;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }

  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numColumns != rhs.numColumns || numRows != rhs.numRows) {
    return false;
  }

  for (int i = 0; i < numRows; i++) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numColumns == rhs.numColumns);
  IntMatrix res = IntMatrix(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*res.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
    }
  }

  return res;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
