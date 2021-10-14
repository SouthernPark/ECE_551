#include "vector.hpp"

#include <cmath>
#include <cstdio>
using std::sqrt;
/* write your class implementation in this file
 */

double Vector2D ::getMagnitude() const {
  return sqrt(x * x + y * y);
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D res;
  res.initVector(x + rhs.x, y + rhs.y);

  return res;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}
