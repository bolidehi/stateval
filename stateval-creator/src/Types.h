#ifndef TYPES_H
#define TYPES_H

#include "Point.h"
#include "Size.h"
#include "Rect.h"

enum HitPosition
{
  Complete,
  Inset,
  Border
};

typedef Size <double> Sized;
typedef Rect <double> Rectd;

Sized convertPoint2Sized (const Point &pos);

Point convertSized2Point (const Sized &size);

#endif // TYPES_H