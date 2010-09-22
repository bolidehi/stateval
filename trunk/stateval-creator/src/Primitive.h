#ifndef PRIMITIVE_H
#define PRIMITIVE_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Types.h"

class Primitive
{
public:
  Primitive ();
  
  virtual void moveTo (const Point &pos) = 0;
  
  virtual void render (Cairo::RefPtr<Cairo::Context> cr) = 0;

protected:
  
};



#endif // PRIMITIVE_H
