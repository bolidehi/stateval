#ifndef CIRCLE_H
#define CIRCLE_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Primitive.h"

class Circle : public Primitive
{
public:
  Circle ();
  Circle (double radius);
  Circle (double x, double y, double radius);
  
  void setRadius (double radius);
  double getRadius ();
  
  void setFill (bool fill);
  bool getFill ();
  
  void moveTo (const Point &pos);
  
  void render (Cairo::RefPtr<Cairo::Context> cr);
  
protected:
  double mRadius;
  bool mFill;
  Point mPos;
};

#endif // CIRCLE_H
