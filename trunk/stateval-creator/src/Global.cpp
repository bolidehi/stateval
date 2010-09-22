#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include "Global.h"

using namespace std;

Global& Global::instance()
{
  static Global g;
  return g;
}

void Global::init ()
{
  //m_appProgressBar = NULL;
  mUMLDrawer = NULL;
}
