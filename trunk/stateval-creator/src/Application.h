#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <gtkmm.h>
#include <iostream>
#include "AppToolBar.h"
#include "AppMenuBar.h"

/* forward declarations */
class UMLDrawer;

class Application : public Gtk::Window
{
public:
  Application (BaseObjectType* cobject,
               const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~Application ();
    

protected:
  void getGladeWidgets ();
  void connectSignalHandlers ();

  // signal callback functions
  void on_application_hide ();
  
private:
  Glib::RefPtr<Gtk::Builder> mXMLGlade;
  AppToolBar *mAppToolBar;
  /*AppNotebook *m_appNotebook;
  AppMenuBar *m_appMenubar;
  AppProgressBar *m_appProgressBar;*/

  UMLDrawer *mUMLDrawer;
};

#endif  // APPLICATION_H
