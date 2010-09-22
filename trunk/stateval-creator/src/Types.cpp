#include "Types.h"

Sized convertPoint2Sized (const Point &pos)
{
  return Sized (pos.getX (), pos.getY ());
}

Point convertSized2Point (const Sized &size)
{
  return Point (size.getWidth (), size.getHeight ());
}
