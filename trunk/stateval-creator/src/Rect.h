#ifndef RECT_H
#define RECT_H

#include <stdint.h>
#include <iostream>
#include "Point.h"
#include "Size.h"
#include "Types.h"

/*!
 * Trivial class which stores a rectangle (pos, size) in integer notation.
 * This is supposed to be used by the GUI.
 */

template <typename T>
class Rect
{
public:
  Rect();
  Rect(T inX, T inY, T inWidth, T inHeight);
  Rect(const Point &inPoint, const Size<T> &inSize);
  Rect(const Rect<T>& inRect);

  ~Rect<T>();

  Rect &operator=(const Rect<T>& inPoint);

  const Point &getPos() const
  {
    return pos;
  }

  const Size<T>&  getSize() const
  {
    return size;
  }

  int getX() const
  {
    return pos.getX();
  }
  int getY() const
  {
    return pos.getY();
  }

  int getWidth()  const
  {
    return size.getWidth();
  }
  int getHeight() const
  {
    return size.getHeight();
  }

  bool isEmpty() const
  {
    return size.isEmpty();
  }

  bool  operator== (const Rect<T>& inRect) const;

  void moveTo(const Point &inPos);
  void moveBy(const Point &inDeltaPos);

  void resizeTo(const Size<T>& inSize);
  void resizeBy(const Size<T>& inDeltaSize);

  void inset(const Size<T>& inDelta);

  bool isHitBy(const Point &inPoint) const;

private:
  Point  pos;
  Size<T>   size;
};

template <typename T>
inline Rect<T>::Rect()
{
}

template <typename T>
inline Rect<T>::Rect(T inX, T inY, T inWidth, T inHeight)
  : pos(inX, inY), size(inWidth, inHeight)
{
}

template <typename T>
inline Rect<T>::Rect(const Point &inPoint, const Size<T> &inSize)
  : pos(inPoint), size(inSize)
{
}

template <typename T>
inline Rect<T>::Rect(const Rect<T>& inRect)
  : pos(inRect.pos), size(inRect.size)
{
}

template <typename T>
inline Rect<T>::~Rect()
{
}

template <typename T>
inline Rect<T>& Rect<T>::operator=(const Rect<T>& inPoint)
{
  pos = inPoint.pos;
  size = inPoint.size;
  return *this;
}

/**!
 * Check if two rectangles are identical
 */
template <typename T>
inline bool Rect<T>::operator== (const Rect<T>& inRect) const
{
  if (this == &inRect)  // The same object?
    return true;

  return (pos  == inRect.pos &&
          size == inRect.size);
}

template <typename T>
inline void Rect<T>::moveTo(const Point &inPos)
{
  pos = inPos;
}

template <typename T>
inline void Rect<T>::moveBy(const Point &inDeltaPos)
{
  pos += inDeltaPos;
}

template <typename T>
inline void Rect<T>::resizeTo(const Size<T>& inSize)
{
  size = inSize;
}

template <typename T>
inline void Rect<T>::resizeBy(const Size<T>& inDeltaSize)
{
  size.resizeBy(inDeltaSize);
}

template <typename T>
inline void Rect<T>::inset(const Size<T>& inDelta)
{
  moveBy(convertSized2Point(inDelta));
  resizeBy(Size<T> (inDelta.getWidth() * -2, inDelta.getHeight() * -2));
}

/**!
 * Check if a particular point is located in this Rectangle
 */
template <typename T>
inline bool Rect<T>::isHitBy(const Point &inPoint) const
{
  std::cout << inPoint.getX() << "," << inPoint.getY() << "," << getX() << "," << getY() << "," << getWidth() << "," << getHeight() << std::endl;

  return (((inPoint.getX() >= getX()) &&
           (inPoint.getY() >= getY()))
          &&
          ((inPoint.getX() <  getX() + getWidth()) &&
           (inPoint.getY() <  getY() + getHeight())));
}

#endif // RECT_H
