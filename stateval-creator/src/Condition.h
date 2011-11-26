#ifndef CONDITION_H
#define CONDITION_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Circle.h"
#include "Text.h"
#include "SCObject.h"
#include "Types.h"

class Condition : public SC::Object
{
public:
  Condition(const Point &pos);

  void moveTo(const Point &pos);

  void resizeTo(const Sized &size);

  void render(Cairo::RefPtr<Cairo::Context> cr);

  bool isHitBy(HitPosition hit, const Point &pos);

private:
  void init();

  static double mRadius;

  static Point mCirclePosRel;
  Circle mCircle;

  static Point mTextPosRel;
  Text mText;

  static Rectd mBoundingBoxPosRel;
};



#endif // CONDITION_H
