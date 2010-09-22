#ifndef SIZE_H
#define SIZE_H

#include <stdint.h>

/*!
 * Trivial class which stores a size in integer notation. 
 * This is supposed to be used by the GUI.
 */

// TODO: think about to base Size on Vector2 class!

template <typename T>
class Size
{
public:
  Size ();
  Size (T inWidth, T inHeight);
  Size (const Size& inSize);

  ~Size () {}

  Size& operator= (const Size<T>& inRHS);

  Size& operator *= (int factor);

  Size operator * (int factor);

  bool operator== (const Size<T>& inSize) const;

  bool isEmpty() const { return ((mWidth == 0) && (mHeight == 0));}

  int getWidth ()  const {return mWidth;}
  int getHeight() const {return mHeight;}

  void resizeBy (const Size<T>& inSize);

  /*!
   * Multiply with a value.
   * 
   * @factor The factor to multiply with
   */
  void resizeBy (T factor);

private:
  T mWidth, mHeight;
};

template <typename T>
inline Size<T>::Size ()
    : mWidth (0), mHeight (0)
{
}

template <typename T>
inline Size<T>::Size(T inWidth, T inHeight)
    : mWidth (inWidth), mHeight(inHeight)
{
}

template <typename T>
inline Size<T>::Size(const Size<T>& inSize)
    : mWidth (inSize.mWidth), mHeight(inSize.mHeight)
{
}

template <typename T>
inline Size<T>& Size<T>::operator = (const Size<T>& inRHS)
{
  mWidth  = inRHS.mWidth;
  mHeight = inRHS.mHeight;
  return *this;
}

template <typename T>
inline Size<T>& Size<T>::operator *= (int factor)
{
  mWidth *= factor;
  mHeight *= factor;
  return *this;
}

template <typename T>
inline Size<T> Size<T>::operator * (int factor)
{
  Size<T> size (mWidth * factor, mHeight * factor);
  
  return size;
}

template <typename T>
inline Size<T> operator - (const Size<T>& inSize1, const Size<T>& inSize2)
{
  return Size<T> (inSize1.getWidth () - inSize2.getWidth (), inSize1.getHeight () - inSize2.getHeight ());
}

template <typename T>
inline Size<T> operator + (const Size<T>& inSize1, const Size<T>& inSize2)
{
  return Size<T> (inSize1.getWidth () + inSize2.getWidth (), inSize1.getHeight () + inSize2.getHeight ());
}


template <typename T>
inline bool Size<T>::operator == (const Size<T>& inSize) const
{
  if (this == &inSize)  // The same object?
    return true;

  return (mWidth  == inSize.mWidth &&
          mHeight == inSize.mHeight);
}

template <typename T>
inline void Size<T>::resizeBy (const Size<T>& inSize)
{
  mWidth += inSize.mWidth;
  mHeight += inSize.mHeight;
}

template <typename T>
inline void  Size<T>::resizeBy (T factor)
{
  mWidth *= factor;
  mHeight *= factor;
}

#endif // SIZE_H
