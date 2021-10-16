#include "circle.hpp"

#include <cmath>
using std::abs;
using std::acos;
using std::sqrt;
void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double r = radius;
  double R = otherCircle.radius;

  //calculate the distance between the two circle
  double d = center.distanceFrom(otherCircle.center);
  if (d >= radius + otherCircle.radius) {
    return 0;
  }

  if (d <= abs(R - r)) {
    double small = r;
    if (R < small) {
      small = R;
    }

    return M_PI * small * small;
  }

  //calculate the area of intersetion using circular segment formula
  //https://mathworld.wolfram.com/Circle-CircleIntersection.html
  double r1 = r;
  double r2 = R;
  double d1 = ((r1) * (r1) - (r2) * (r2) + d * d) / (2 * d);
  double d2 = d - d1;
  return (r1) * (r1)*acos(d1 / r1) - d1 * sqrt(r1 * r1 - d1 * d1) +
         r2 * r2 * acos(d2 / r2) - d2 * sqrt(r2 * r2 - d2 * d2);
}
