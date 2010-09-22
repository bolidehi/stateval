#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtkmm.h>
#include <iostream>

#include "main.h"
#include "Application.h"
#include "searchFile.h"

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

int main (int argc, char *argv[])
{

  return create_gtk_window (argc, argv);
}

int create_gtk_window (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);

  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gtk::Builder> mXMLGlade;
  try
  {
    mXMLGlade = createGlade ();
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  Application* app = NULL;
  mXMLGlade->get_widget_derived ("Application", app);
  if (app)
  {
    kit.run(*app);
  }
  return 0;
}

