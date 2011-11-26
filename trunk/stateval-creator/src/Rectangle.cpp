/* Project */
#include "Rectangle.h"

using namespace std;

Sized Rectangle::mBorder(5, 5);

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(const Rectd &rect) :
  mRect(rect),
  mRectInner(rect),
  mLinecolor(0, 0, 0)
{
  mRectInner.inset(mBorder);
}

void Rectangle::moveTo(const Point &pos)
{
  mRect.moveTo(pos);
  mRectInner.moveTo(pos + convertSized2Point(mBorder));
}

void Rectangle::resizeTo(const Sized &size)
{
  mRect.resizeTo(size);

  mRectInner.resizeTo(size - mBorder * 2);
}

void Rectangle::render(Cairo::RefPtr<Cairo::Context> cr)
{
  curveRectangle(cr, mRect.getX(), mRect.getY(), mRect.getX() + mRect.getWidth(), mRect.getY() + mRect.getHeight());

  // Debug: show inner rectangle
  curveRectangle(cr, mRectInner.getX(), mRectInner.getY(), mRectInner.getX() + mRectInner.getWidth(), mRectInner.getY() + mRectInner.getHeight());
}

bool Rectangle::isHitBy(HitPosition hit, const Point &pos)
{
  bool ret = false;

  switch (hit)
  {
  case Inset:
    ret = mRectInner.isHitBy(pos);
    break;

  case Border:
    ret = mRect.isHitBy(pos) && !mRectInner.isHitBy(pos);
    break;

  case Complete:
    ret = mRect.isHitBy(pos);
    break;
  }

  return ret;
}

void Rectangle::setLineColor(const Color &color)
{
  mLinecolor = color;
}

void Rectangle::curveRectangle(Cairo::RefPtr<Cairo::Context> cr, double x0, double y0, double x1, double y1)
{
  /* a custom shape that could be wrapped in a function */
  double radius = 102.4;   /* and an approximate curvature radius */
  //double x1 = x0 + rect_width;
  //double y1 = y0 + rect_height;
  double rect_width = x1 - x0;
  double rect_height = y1 - y0;

  if (!rect_width || !rect_height)
    return;

  if (rect_width / 2 < radius)
  {
    if (rect_height / 2 < radius)
    {
      cr->move_to(x0, (y0 + y1) / 2);
      cr->curve_to(x0 , y0, x0, y0, (x0 + x1) / 2, y0);
      cr->curve_to(x1, y0, x1, y0, x1, (y0 + y1) / 2);
      cr->curve_to(x1, y1, x1, y1, (x1 + x0) / 2, y1);
      cr->curve_to(x0, y1, x0, y1, x0, (y0 + y1) / 2);
    }
    else
    {
      cr->move_to(x0, y0 + radius);
      cr->curve_to(x0 , y0, x0, y0, (x0 + x1) / 2, y0);
      cr->curve_to(x1, y0, x1, y0, x1, y0 + radius);
      cr->line_to(x1 , y1 - radius);
      cr->curve_to(x1, y1, x1, y1, (x1 + x0) / 2, y1);
      cr->curve_to(x0, y1, x0, y1, x0, y1 - radius);
    }
  }
  else
  {
    if (rect_height / 2 < radius)
    {
      cr->move_to(x0, (y0 + y1) / 2);
      cr->curve_to(x0 , y0, x0 , y0, x0 + radius, y0);
      cr->line_to(x1 - radius, y0);
      cr->curve_to(x1, y0, x1, y0, x1, (y0 + y1) / 2);
      cr->curve_to(x1, y1, x1, y1, x1 - radius, y1);
      cr->line_to(x0 + radius, y1);
      cr->curve_to(x0, y1, x0, y1, x0, (y0 + y1) / 2);
    }
    else
    {
      cr->move_to(x0, y0 + radius);
      cr->curve_to(x0 , y0, x0 , y0, x0 + radius, y0);
      cr->line_to(x1 - radius, y0);
      cr->curve_to(x1, y0, x1, y0, x1, y0 + radius);
      cr->line_to(x1 , y1 - radius);
      cr->curve_to(x1, y1, x1, y1, x1 - radius, y1);
      cr->line_to(x0 + radius, y1);
      cr->curve_to(x0, y1, x0, y1, x0, y1 - radius);
    }
  }
  cr->close_path();

  cr->set_source_rgb(1, 1, 1);  // background color
  cr->fill_preserve();
  cr->set_source_rgba(mLinecolor.red(), mLinecolor. green(),
                      mLinecolor.blue(), mLinecolor.alpha());   // line color

  cr->stroke();
}
