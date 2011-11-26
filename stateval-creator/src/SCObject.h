#ifndef SC_OBJECT_H
#define SC_OBJECT_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Types.h"

namespace SC
{

class Object
{
public:
  Object();
  Object(const Point &pos);
  virtual ~Object();

  virtual void moveTo(const Point &pos);

  virtual void resizeTo(const Sized &size) = 0;

  virtual const Point getPos() const;

  virtual void render(Cairo::RefPtr<Cairo::Context> cr) = 0;

  virtual bool isHitBy(HitPosition hit, const Point &pos) = 0;

  void setSelected(bool state);

  bool isSelected();

protected:
  Point mPos;
  bool mSelected;
};

} // end namespace SC

#endif // SC_OBJECT_H
