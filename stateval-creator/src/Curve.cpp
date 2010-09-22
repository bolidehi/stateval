/* Project */
#include "Curve.h"

Curve::Curve ()
{
}

Curve::Curve (const Point &pos1, const Point &pos3)
{
  setCoord (pos1, pos3);
}

Curve::Curve (const Point &pos1, const Point &pos2, const Point &pos3) :
  mPos1 (pos1),
  mPos2 (pos2),
  mPos3 (pos3)
{
}

void Curve::moveTo (const Point &pos)
{
  
}

void Curve::setCoord (const Point &pos1, const Point &pos3)
{
  mPos1 = pos1;
  mPos2 = (pos1 + pos3);
  mPos2 /= 3;
  mPos3 = pos3;
}

void Curve::render (Cairo::RefPtr<Cairo::Context> cr)
{
  curveTo (cr, mPos1.x, mPos1.y, mPos2.x, mPos2.y, mPos3.x, mPos3.y);
}

// TODO: draw little arrows at start and end
void Curve::curveTo (Cairo::RefPtr<Cairo::Context> cr, double x1, double y1, double x2, double y2, double x3, double y3)
{
  //cr->move_to (x, y);
  cr->curve_to (x1, y1, x2, y2, x3, y3); //x1/y1->x/y e.g. does something...

  //cr->set_line_width (10.0);
  cr->stroke ();

  //cr->set_source_rgba (1, 0.2, 0.2, 0.6);
  //cr->set_line_width (6.0);
  
  //cr->move_to (x,y);
  //cr->line_to (x1,y1);
  
  //cr->move_to (x2,y2);
  //cr->line_to (x3,y3);

  //cr->stroke ();
}
