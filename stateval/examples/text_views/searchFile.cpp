#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "searchFile.h"
#include "stateval/private/Exceptions.h"

using namespace std;

const std::string searchEdjeFile (const std::string &theme)
{
  vector <string> name_vector;

  name_vector.push_back (theme);
  name_vector.push_back ("../" + theme);

#ifdef HAVE_CONFIG_H
  name_vector.push_back (string (PACKAGE_SOURCE_DIR) + "/data/" + theme);
  name_vector.push_back (string (PACKAGE_DATA_DIR) + "/" + theme);
#endif
  
  const string &file = searchFile (name_vector);

  if (file.empty ())
  {
    throw FileNotFoundException (theme);
  }

  return file;
}

const std::string searchDataDir ()
{
  vector <string> name_vector;

  name_vector.push_back ("data");
  
#ifdef HAVE_CONFIG_H
  name_vector.push_back (string (PACKAGE_SOURCE_DIR) + "/data");
  name_vector.push_back (PACKAGE_DATA_DIR);
#endif
  
  return searchFile (name_vector);
}

const std::string searchFile (std::vector <std::string> &name_vector)
{
  struct stat buf;

  for (unsigned int i = 0; i < name_vector.size (); i++)
  {
    string &try_name = name_vector[i];

    bool found = !(stat (try_name.c_str (), &buf));
    //cout << "try_name: " << try_name << endl;

    if (found)
    {
      return try_name;
    }
  }

  return "";
}
