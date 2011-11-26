#ifndef POINT_H
#define POINT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstdio>
#include <cstring>
#include <stdint.h>
#include <string>
#include "Vector2.h"

/*!
 * Trivial class which stores a point in double notation.
 */
class Point : public Vector2real<double>
{
public:
  Point()                         : Vector2real<double> (0.0, 0.0) {}
  Point(const Point &p)           : Vector2real<double> (p) {}
  Point(double _x, double _y)     : Vector2real<double> (_x, _y) {}
  Point(const Vector2<double> &v) : Vector2real<double> (v) {}

  virtual ~Point() {}

  double getX() const
  {
    return x;
  }
  double getY() const
  {
    return y;
  }

  virtual double getMagnitude() const
  {
    return sqrt(x * x + y * y);
  }

};

#endif // POINT_H
