#ifndef CURVE_H
#define CURVE_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Primitive.h"

class Curve : public Primitive
{
public:
  Curve ();
  Curve (const Point &pos1, const Point &pos3);
  Curve (const Point &pos1, const Point &pos2, const Point &pos3);
  
  void moveTo (const Point &pos);
  
  void setCoord (const Point &pos1, const Point &pos3);
  
  void render (Cairo::RefPtr<Cairo::Context> cr);
  
protected:
  void curveTo (Cairo::RefPtr<Cairo::Context> cr, double x1, double y1, double x2, double y2);
  void curveTo (Cairo::RefPtr<Cairo::Context> cr, double x1, double y1, double x2, double y2, double x3, double y3);
  
  Point mPos1, mPos2, mPos3;
};

#endif // CURVE_H
