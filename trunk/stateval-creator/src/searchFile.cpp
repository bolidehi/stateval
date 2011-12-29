#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* STD */
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Project */
#include "searchFile.h"

#ifdef GLADE_HEADER_COMPILE
#include "state_glade.h"
#else
#define GLADE_FILE "stateval-creator.glade"
#endif

using namespace std;

Glib::RefPtr<Gtk::Builder> createGlade(const Glib::ustring &object_id)
{
#ifdef GLADE_HEADER_COMPILE
  /*return Gnome::Glade::Xml::create_from_buffer(
         pogo_glade_data, pogo_glade_data_size,
         root, domain);*/
#else
  return Gtk::Builder::create_from_file(searchGladeFile(GLADE_FILE), object_id);
#endif
}

Glib::RefPtr<Gtk::Builder> createGlade()
{
#ifdef GLADE_HEADER_COMPILE
  /*return Gnome::Glade::Xml::create_from_buffer(
         pogo_glade_data, pogo_glade_data_size,
         root, domain);*/
#else
  return Gtk::Builder::create_from_file(searchGladeFile(GLADE_FILE));
#endif
}

const std::string searchGladeFile(const std::string &glade_file)
{
  vector <string> name_vector;

  name_vector.push_back(string(PACKAGE_SOURCE_DIR) + "/src/" + glade_file);
  name_vector.push_back(string(PACKAGE_DATA_DIR) + "/glade/" + glade_file);

  return searchFile(name_vector);
}

const std::string searchDataDir()
{
  vector <string> name_vector;

  name_vector.push_back(string(PACKAGE_SOURCE_DIR) + "/data/");
  name_vector.push_back(string(PACKAGE_DATA_DIR) + "/data/");

  return searchFile(name_vector);
}

const std::string searchPixmapFile(std::string pixmap_file)
{
  vector <string> name_vector;

  name_vector.push_back(string(PACKAGE_SOURCE_DIR) + "/pixmaps/" + pixmap_file);
  name_vector.push_back(string(PACKAGE_PIXMAPS_DIR) + "/" + pixmap_file);

  return searchFile(name_vector);
}

const std::string searchFile(std::vector <std::string> &name_vector)
{
  struct stat buf;

  for (unsigned int i = 0; i < name_vector.size(); i++)
  {
    string &try_name = name_vector[i];

    bool found = !(stat(try_name.c_str(), &buf));

    if (found)
    {
      return try_name;
    }
  }

  return "";
}
