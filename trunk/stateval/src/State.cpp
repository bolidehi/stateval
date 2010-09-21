#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "../include/stateval/State.h"
#include "localUtil.h"

/* STD */
#include <iostream>

using namespace std;

State::State () :
  mParentState (NULL), // => ROOT
  mID (0)
{ 
}

State::State (State *parentState) :
  mParentState (parentState),
  mID (0)
{
}

State::~State ()
{
  //cout << "clean State" << endl;
  
  // free mLeaveTransitonList
  delete_stl_container <std::list <Transition*>, Transition*> (mLeaveTransitonList);
}

void State::setID (unsigned int id)
{
  mID = id;
}
  
unsigned int State::getID ()
{
  return mID;
}

void State::setName (const std::string name)
{

}

const std::string State::getName ()
{

}

State *State::getParentState () const
{
  return mParentState;
}

void State::addLeaveTransition (Transition &trans)
{
  mLeaveTransitonList.push_back (&trans);
}