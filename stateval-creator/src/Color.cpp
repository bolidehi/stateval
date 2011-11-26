#include "Color.h"

//using namespace Gen3D;

//namespace Gen3D {
/* ========================================================================== */
/**
 */
/* ========================================================================== */
Color::Color(const Color &inColor)
  : r(inColor.r), g(inColor.g), b(inColor.b), a(inColor.a)
{
}

/* ========================================================================== */
/**
 */
/* ========================================================================== */
Color &Color::operator=(const Color &inRHS)
{
  r = inRHS.r;
  g = inRHS.g;
  b = inRHS.b;
  a = inRHS.a;

  return *this;
}

//}
