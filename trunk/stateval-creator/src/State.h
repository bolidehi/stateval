#ifndef STATE_H
#define STATE_H

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Rectangle.h"
#include "Text.h"
#include "SCObject.h"

class State : public SC::Object
{
public:
  State();
  State(const Point &pos);

  void setName(const std::string &name);
  std::string getName() const;

  virtual void moveTo(const Point &pos);

  virtual void resizeTo(const Sized &size);

  virtual void render(Cairo::RefPtr<Cairo::Context> cr);

  virtual bool isHitBy(HitPosition hit, const Point &pos);

protected:
  virtual const Point getTextPosition();

private:
  Rectangle mRect;

  static Point mTextPosRel;
  Text mText;

  static Sized mInitialStateSize;
};

#endif // STATE_H
