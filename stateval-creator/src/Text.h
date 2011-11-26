#ifndef TEXT_H
#define TEXT_H

/* STD */
#include <string>

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "Primitive.h"
#include "Types.h"

class Text : public Primitive
{
public:
  Text();
  Text(const Point &pos);
  Text(const std::string &text);

  void moveTo(const Point &pos);

  void setText(const std::string &text);
  const std::string getText() const;

  void setFontSize(double size);
  double getFontSize();

  void render(Cairo::RefPtr<Cairo::Context> cr);

private:
  // private init for constructors
  void init();

  std::string mText;
  Point mPos;
  double mSize;
};

#endif // TEXT_H
