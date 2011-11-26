#include "Circle.h"

using namespace std;

Circle::Circle() :
  mFill(false)
{
}

Circle::Circle(double radius) :
  mRadius(radius),
  mFill(false)
{
}

Circle::Circle(double x, double y, double radius) :
  mRadius(radius),
  mFill(false)
{
}

void Circle::setRadius(double radius)
{
  mRadius = radius;
}

double Circle::getRadius()
{
  return mRadius;
}

void Circle::moveTo(const Point &pos)
{
  mPos = pos;
}

void Circle::setFill(bool fill)
{

}

bool Circle::getFill()
{

}

void Circle::render(Cairo::RefPtr<Cairo::Context> cr)
{
  cr->arc(mPos.x, mPos.y, mRadius, 0, 2 * M_PI);
  cr->set_source_rgb(1, 1, 1);  // background color
  cr->fill_preserve();
  cr->set_source_rgba(0, 0, 0, 1);  // line color

  if (mFill)
  {
    cr->fill();
  }

  cr->stroke();
}
