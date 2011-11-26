/* Project */
#include "State.h"

/* STD */
#include <iostream>

using namespace std;

/* initialize static members */
//Point State::mTextPosRel (0, 0);
Sized State::mInitialStateSize(100, 50);

State::State()
{
}

State::State(const Point &pos) :
  SC::Object(pos),
  mRect(Rectd(pos, mInitialStateSize)),
  mText(pos + getTextPosition())
{
  mText.setText("Text");
  mText.setFontSize(20);
}

void State::setName(const std::string &name)
{
  mText.setText(name);
}

std::string State::getName() const
{
  return mText.getText();
}

void State::render(Cairo::RefPtr<Cairo::Context> cr)
{
  if (isSelected())
  {
    mRect.setLineColor(Color(1, 0, 0));
  }
  else
  {
    mRect.setLineColor(Color(0, 0, 0));
  }

  mRect.render(cr);
  mText.render(cr);
}

// move at middle point
void State::moveTo(const Point &pos)
{
  // move parent
  SC::Object::moveTo(pos);

  mRect.moveTo(pos);
  mText.moveTo(pos + getTextPosition());
}

void State::resizeTo(const Sized &size)
{
  mRect.resizeTo(size);
}

bool State::isHitBy(HitPosition hit, const Point &pos)
{
  return mRect.isHitBy(hit, pos);
}

const Point State::getTextPosition()
{
  return Point(25, 30);
}
