/* Project */
#include "Condition.h"
#include "MathUtil.h"

/* STD */
#include <iostream>

using namespace std;

/* initialize static members */
Point Condition::mCirclePosRel(0, 0);
Point Condition::mTextPosRel(-7, 7);
double Condition::mRadius(20);
Rectd Condition::mBoundingBoxPosRel(-Condition::mRadius, -Condition::mRadius,
                                    2 * Condition::mRadius, 2 * Condition::mRadius);

Condition::Condition(const Point &pos) :
  mCircle(mRadius),
  mText("C")
{
  moveTo(pos);
  mText.setFontSize(20.0);
}

void Condition::moveTo(const Point &pos)
{
  // move parent
  SC::Object::moveTo(pos);

  mCircle.moveTo(pos + mCirclePosRel);
  mText.moveTo(pos + mTextPosRel);
}

void Condition::resizeTo(const Sized &size)
{
}

void Condition::render(Cairo::RefPtr<Cairo::Context> cr)
{
  mCircle.render(cr);
  mText.render(cr);
}

bool Condition::isHitBy(HitPosition hit, const Point &pos)
{
  Rectd currentRect(mBoundingBoxPosRel);
  currentRect.moveBy(mPos);

  return currentRect.isHitBy(pos);
}
