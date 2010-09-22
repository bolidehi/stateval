#ifndef RECTANGLE_H
#define RECTANGLE_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Primitive.h"
#include "Types.h"
#include "Color.h"

class Rectangle : public Primitive
{
public:
  Rectangle ();
  Rectangle (const Rectd &rect);
  
  void moveTo (const Point &pos);

  void resizeTo (const Sized &size);
  
  void render (Cairo::RefPtr<Cairo::Context> cr);
  
  bool isHitBy (HitPosition hit, const Point &pos);

  void setLineColor (const Color &color);
  
protected:
  void curveRectangle (Cairo::RefPtr<Cairo::Context> cr, double x0, double y0, double x1, double y1);

  Rectd mRect;
  Rectd mRectInner;
  Color mLinecolor;

  static Sized mBorder;
};

#endif // RECTANGLE_H
