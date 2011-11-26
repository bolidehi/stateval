/* Project */
#include "Transition.h"

using namespace std;

Transition::Transition(const SC::Object &fromObj, const SC::Object &toObj) :
  mFromObj(&fromObj),
  mToObj(&toObj)
{

}

void Transition::moveTo(const Point &pos)
{
  // move parent
  SC::Object::moveTo(pos);
}

void Transition::resizeTo(const Sized &size)
{
}

void Transition::render(Cairo::RefPtr<Cairo::Context> cr)
{
  const Point fromObjPos = mFromObj->getPos();
  const Point toObjPos = mToObj->getPos();

  mCurve.setCoord(fromObjPos, toObjPos);

  mCurve.render(cr);
}

bool Transition::isHitBy(HitPosition hit, const Point &pos)
{
  return false;
}