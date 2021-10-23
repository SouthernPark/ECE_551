#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(0){};
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows.resize(r);
    for (int i = 0; i < r; i++) {
      rows[i].resize(c);
    }
  }

  //copy constructor
  Matrix(const Matrix<T> & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = rhs.rows;
  }

  //destructor

  //copy assignment operator
  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      std::vector<std::vector<T> > temp;
      temp = rhs.rows;
      rows = temp;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }

  //getters

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; };

  //[]operator
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  //when index constant object
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  // == operator
  bool operator==(const Matrix<T> & rhs) {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns || rows != rhs.rows) {
      return false;
    }

    return true;
  }

  // + operator

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix<T> ans = Matrix<T>(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans.rows[i][j] = rows[i][j] + rhs.rows[i][j];
      }
    }

    return ans;
  }

  //print
  template<typename X>
  friend std::ostream & operator<<(std::ostream & os, const Matrix<X> & mat);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  typename std::vector<std::vector<T> >::const_iterator it;
  for (it = rhs.rows.begin(); it != rhs.rows.end(); ++it) {
    if (it != rhs.rows.begin()) {
      s << ",\n";
    }
    s << "{";
    typename std::vector<T>::const_iterator it_it;
    for (it_it = (*it).begin(); it_it != (*it).end(); ++it_it) {
      if (it_it != (*it).begin()) {
        s << ", ";
      }
      s << *it_it;
    }
    s << "}";
  }
  s << " ]";
  return s;
}

#endif
