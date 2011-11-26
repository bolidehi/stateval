/* Project */
#include "History.h"
#include "MathUtil.h"

/* STD */
#include <iostream>

using namespace std;

/* initialize static members */
Point History::mCirclePosRel(0, 0);
Point History::mTextPosRel(-7, 7);
double History::mRadius(20);
Rectd History::mBoundingBoxPosRel(-History::mRadius, -History::mRadius,
                                  2 * History::mRadius, 2 * History::mRadius);

History::History(const Point &pos) :
  mCircle(mRadius),
  mText("H")
{
  moveTo(pos);
  mText.setFontSize(20.0);
}

void History::moveTo(const Point &pos)
{
  // move parent
  SC::Object::moveTo(pos);

  mCircle.moveTo(pos + mCirclePosRel);
  mText.moveTo(pos + mTextPosRel);
}

void History::resizeTo(const Sized &size)
{
}

void History::render(Cairo::RefPtr<Cairo::Context> cr)
{
  mCircle.render(cr);
  mText.render(cr);
}

bool History::isHitBy(HitPosition hit, const Point &pos)
{
  Rectd currentRect(mBoundingBoxPosRel);
  currentRect.moveBy(mPos);

  return currentRect.isHitBy(pos);
}
