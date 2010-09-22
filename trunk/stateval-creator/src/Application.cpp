#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include "Application.h"
#include "Global.h"
#include "UMLDrawer.h"

#ifdef DEBUG
  #include <StopClock/StopClock.h>
#endif //DEBUG 

using namespace std;

Application::Application (BaseObjectType* cobject,
                          const Glib::RefPtr<Gtk::Builder>& refGlade) :
  Gtk::Window (cobject),
  mXMLGlade (refGlade),
  mUMLDrawer (NULL)/*,
  m_appToolBox (NULL),
  m_appNotebook (NULL),
  m_appProgressBar (NULL)*/
{
  getGladeWidgets ();
  connectSignalHandlers ();

  Global &global = Global::instance ();
  //global.setAppProgressBar (m_appProgressBar);
  global.setUMLDrawer (mUMLDrawer);
  
  //m_loadProgressBar->set_fraction (0.02);
    
  show_all_children();
}

Application::~Application()
{
}

void Application::getGladeWidgets ()
{
  mXMLGlade->get_widget_derived ("drawingareaUML", mUMLDrawer);
  mXMLGlade->get_widget_derived ("appToolBar", mAppToolBar);
  /*mXMLGlade->get_widget_derived ("appNotebook", m_appNotebook);
  mXMLGlade->get_widget_derived ("appMenubar", m_appMenubar);
  mXMLGlade->get_widget_derived ("loadProgressBar", m_appProgressBar);*/
}

void Application::connectSignalHandlers ()
{   
  /*if (target_vbox)
  { 
    target_combo.signal_changed().connect (sigc::mem_fun (*this,
                                           &Application::on_target_combo_changed));
  }*/

  // connect window close signal
  signal_hide().connect (sigc::mem_fun (*this,
                                        &Application::on_application_hide));
}

// signals
void Application::on_application_hide ()
{
  cerr << "window hide" << endl;

  // do here all actions that should happen before save exit!

  Gtk::Main::quit ();
}

