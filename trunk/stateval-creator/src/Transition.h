#ifndef TRANSITION_H
#define TRANSITION_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Curve.h"
#include "SCObject.h"

class Transition : public SC::Object
{
public:
  Transition();
  Transition(const SC::Object &fromObj, const SC::Object &toObj);

  void moveTo(const Point &pos);

  void resizeTo(const Sized &size);

  void render(Cairo::RefPtr<Cairo::Context> cr);

  bool isHitBy(HitPosition hit, const Point &pos);

private:
  const SC::Object *mFromObj;
  const SC::Object *mToObj;
  Curve mCurve;
};

#endif // TRANSITION_H
