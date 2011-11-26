#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "AppMenuBar.h"
//#include "PreferencesDialog.h"
#include "main.h"

using namespace std;

AppMenuBar::AppMenuBar(BaseObjectType *cobject,
                       const Glib::RefPtr<Gtk::Builder>& refGlade) :
  Gtk::MenuBar(cobject),
  xml_glade(refGlade) //,
/*m_menuEditPreferences (NULL),
m_menuFileExit (NULL),
m_menuHelpInfo (NULL)*/
{
  getGladeWidgets();
  connectSignalHandlers();
}

AppMenuBar::~AppMenuBar()
{
}

void AppMenuBar::getGladeWidgets()
{
  /*xml_glade->get_widget("menuEditPreferences", m_menuEditPreferences);
  xml_glade->get_widget("menuFileExit", m_menuFileExit);
  xml_glade->get_widget("menuHelpInfo",m_menuHelpInfo);*/
}

void AppMenuBar::connectSignalHandlers()
{
  /*m_menuEditPreferences->signal_activate ().connect(sigc::mem_fun (*this,
                  &AppMenubar::onEditPreferencesActivate) );

  m_menuFileExit->signal_activate ().connect(sigc::mem_fun (*this,
                  &AppMenubar::onFileExitActivate) );

  m_menuHelpInfo->signal_activate ().connect(sigc::mem_fun (*this,
                  &AppMenubar::onHelpInfoActivate) );*/
}

/*void AppMenubar::onEditPreferencesActivate ()
{
  PreferencesDialog *preferencesDialog = NULL;

  // Load the Glade file and reference its widgets:
  Glib::RefPtr<Gnome::Glade::Xml> xml_glade;
  try
  {
    xml_glade = createGlade ("PreferencesDialog");
  }
  catch (const Gnome::Glade::XmlError& ex)
  {
    std::cerr << ex.what() << std::endl;
    return;
  }
  // get the application window
  xml_glade->get_widget_derived ("PreferencesDialog", preferencesDialog);

  preferencesDialog->show_all ();
}

void AppMenuBar::onFileExitActivate ()
{
  // hide parent from parent ==> toplevel window
  Container *cont = get_parent ()->get_parent ();
  Gtk::Window *win = static_cast <Gtk::Window*> (cont);

  win->hide ();
}

void AppMenuBar::onHelpInfoActivate ()
{
  Gtk::AboutDialog *aboutDialog = NULL;

  // Load the Glade file and reference its widgets:
  Glib::RefPtr<Gnome::Glade::Xml> xml_glade;
  try
  {
    xml_glade = createGlade ("AboutDialog");
  }
  catch (const Gnome::Glade::XmlError& ex)
  {
    std::cerr << ex.what() << std::endl;
    return;
  }
  // get the application window
  xml_glade->get_widget ("AboutDialog", aboutDialog);

  aboutDialog->run ();
}*/
