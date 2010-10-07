#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* STD */
#include <iostream>
#include <cassert>

/* pluxx */
#include <pluxx/PluginLoader.h>

/* Project */
#include "stateval/Loader.h"
#include "stateval/CompoundState.h"
#include "stateval/HistoryState.h"
#include "stateval/DecisionState.h"
#include "stateval/ViewState.h"
#include "stringUtil.h"
#include "ViewPluginLoader.h"

using namespace std;

Loader::Loader () :
  eventCounter (0)
{
}

Loader::~Loader ()
{
}

void Loader::addEvent (const std::string &event)
{
  mEventList[event] = eventCounter;
    
  ++eventCounter;
}

void Loader::addState (State *state)
{
  mStateList.push_back (state);
}

void Loader::addView (View *view)
{
  mViewList.push_back (view);
}

State *Loader::getInitialState ()
{
  return *mStateList.begin ();
}

int Loader::findMapingEvent (const std::string &event)
{
  map <string,int>::iterator iter = mEventList.find(event);
  if (iter != mEventList.end())
  {
    int &mapEvent = iter->second;
    //cout << "map event: " << iter->first << " : " << iter->second << endl;
    return mapEvent;
  }

  cerr << "StateMachine::findMapingEvent: try to find not existing event: " << event << endl;

  return -1;
}

View *Loader::loadView (const std::string &viewPlugin, const std::list <std::string> &params)
{
  string pluginFile ("/home/andreas/src/svn/stateval/stateval/src/plugins/views/text/.libs/stateval_view_text.so");  
  View *view = NULL;
  
  try
  {
    view = (View*) ViewPluginLoader::loadFactory (pluginFile, "View", 1,
                                                  params);

    // TODO: correct exception handling!
    
    cout << "Type: " <<  view->getType () << endl;
    cout << "Major Version: " << view->getMajorVersion () << endl;
    cout << "Minor Version: " << view->getMinorVersion () << endl;
  }
  catch (pluxx::PluginTypeMismatchException typeEx)
  {
    cout << "catched an PluginTypeMismatchException exception..." << endl;
    cout << "Loader Type: " << typeEx.getLoaderType () << endl;
    cout << "Plugin Type: " << typeEx.getPluginType () << endl;
  }
  catch (pluxx::PluginMajorVersionMismatchException verEx)
  {
    cout << "catched an PluginMajorVersionMismatchException exception..." << endl;
    cout << "Loader Major Version: " << verEx.getLoaderMajorVersion () << endl;
    cout << "Plugin Major Version: " << verEx.getPluginMajorVersion () << endl;
  }

  return view;
}
