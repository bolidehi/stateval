#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "SCObject.h"

/* STD */
#include <iostream>

using namespace std;

namespace SC
{

// TODO: think about if this constructor should be removed
Object::Object() :
  mSelected(false)
{
}

Object::Object(const Point &pos) :
  mPos(pos),
  mSelected(false)
{
}


Object::~Object()
{
}

void Object::moveTo(const Point &pos)
{
  mPos = pos;
}

const Point Object::getPos() const
{
  return mPos;
}

void Object::setSelected(bool state)
{
  mSelected = state;
}

bool Object::isSelected()
{
  return mSelected;
}

} // end namespace SC
