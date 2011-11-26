/* Project */
#include "Text.h"

using namespace std;

Text::Text()
{
  init();
}

Text::Text(const Point &pos) :
  mPos(pos)
{
  init();
}

Text::Text(const std::string &text) :
  mText(text)
{
  init();
}

void Text::init()
{
  mSize = 0;
}

void Text::setText(const std::string &text)
{
  mText = text;
}

const std::string Text::getText() const
{
  return mText;
}

void Text::moveTo(const Point &pos)
{
  mPos = pos;
}

void Text::setFontSize(double size)
{
  mSize = size;
}

double Text::getFontSize()
{
  return mSize;
}

void Text::render(Cairo::RefPtr<Cairo::Context> cr)
{
  // render text always in black
  cr->set_source_rgba(0, 0, 0, 1);

  cr->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL,
                       Cairo::FONT_WEIGHT_NORMAL);

  cr->set_font_size(mSize);

  cr->move_to(mPos.x, mPos.y);

  cr->show_text(mText);

  //cr->text_path ("Text"); // outline text



  cr->stroke();
}