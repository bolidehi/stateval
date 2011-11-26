#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include <map>
#include <gtkmm.h>
//#include <AppProgressBar.h>

using std::map;
using std::string;

/* forward declarations */
class UMLDrawer;

/*
 * Singleton
 */
class Global
{
public:
  static Global &instance();

  //void setAppProgressBar (AppProgressBar *appProgressBar) {m_appProgressBar = appProgressBar;}
  //AppProgressBar *getAppProgressBar () {return m_appProgressBar;}

  void setUMLDrawer(UMLDrawer *umlDrawer)
  {
    mUMLDrawer = umlDrawer;
  }
  UMLDrawer *getUMLDrawer()
  {
    return mUMLDrawer;
  }

  void init();

private: // Singleton
  Global() {}
  Global(const Global &);
  //Global(Global&);
  virtual ~Global() {}
  //void operator = (Global&);

  //AppProgressBar *m_appProgressBar;
  UMLDrawer *mUMLDrawer;
};

#endif // GLOBAL_H
