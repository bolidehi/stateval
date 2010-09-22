#ifndef HISTORY_H
#define HISTORY_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Circle.h"
#include "Text.h"
#include "SCObject.h"
#include "Types.h"

class History : public SC::Object
{
public:
  History (const Point &pos);
  
  void moveTo (const Point &pos);

  void resizeTo (const Sized &size);
  
  void render (Cairo::RefPtr<Cairo::Context> cr);
  
  bool isHitBy (HitPosition hit, const Point &pos);

private:
  void init ();
  
  static double mRadius;
  
  static Point mCirclePosRel;
  Circle mCircle;
  
  static Point mTextPosRel;
  Text mText;
  
  static Rectd mBoundingBoxPosRel;
};



#endif // HISTORY_H
