#ifndef APPMENUBAR_H
#define APPMENUBAR_H

#include <gtkmm.h>
#include <iostream>

class AppMenuBar : public Gtk::MenuBar
{
public:
  AppMenuBar (BaseObjectType* cobject, 
              const Glib::RefPtr<Gtk::Builder>& refGlade);
  ~AppMenuBar ();
  
protected:
  void getGladeWidgets ();
  void connectSignalHandlers ();
  
  // signal handlers
  /*void onEditPreferencesActivate ();
  void onFileExitActivate ();
  void onHelpInfoActivate ();*/
  
private:
  Glib::RefPtr<Gtk::Builder> xml_glade;
  /*Gtk::MenuItem *m_menuEditPreferences;
  Gtk::MenuItem *m_menuFileExit;
  Gtk::MenuItem *m_menuHelpInfo;*/
};

#endif // APPMENUBAR_H
