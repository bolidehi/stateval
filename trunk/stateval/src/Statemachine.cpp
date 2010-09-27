#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "../include/stateval/StateMachine.h"
#include "localUtil.h"

/* STD */
#include <iostream>
#include <cassert>

using namespace std;

StateMachine::StateMachine () :
  mActiveState (NULL), // link to root state
  mSMInit (false)
{
}

StateMachine::~StateMachine ()
{
  cout << "clean up StateMachine" << endl;
}

void StateMachine::init ()
{
  mActiveState = mSMLoader.getInitialState ();
  assert (mActiveState);
  
  mSMInit = true;
}

bool StateMachine::load (const std::string &smDir)
{
  return mSMLoader.load (smDir);
}

void StateMachine::pushEvent (int event)
{
  eventQueue.push (event);
}

void StateMachine::popEvent ()
{
  eventQueue.pop();
}

int StateMachine::findMapingEvent (const std::string &event)
{
  return mSMLoader.findMapingEvent (event);
}

void StateMachine::evaluateState (int &inOutEvent)
{
  const Transition *trans = NULL;
  
  cout << "Now serving: " << inOutEvent << endl;
  //cout << "activeState (before): " << mActiveState << endl;
  
  bool transit = walkDown (inOutEvent);
  
  if (!transit)
  {
    cout << "nothing found -> searching in hierarchie..." << endl;
    assert (mActiveState);
    
    // map event if state has a view...
    mActiveState->mapEvent (inOutEvent);
    
    State *foundState = searchHierarchie (inOutEvent);
    //cout << "found state that fits: " << foundState << endl;
    
    if (foundState != NULL)
    {
      // run exit and entry actions
      mActiveState->runExitActions ();
      
      mActiveState->beforeTransitionCode ();
      
      mActiveState = foundState;
      foundState->runEntryActions ();
      // -->
      
      // do transitions
      walkDown (inOutEvent);
      transit = true;
    }
  }

  if (transit)
  {
    mActiveState->afterTransitionCode ();
  }
  
  //cout << "activeState (after): " << mActiveState << endl;
}

State *StateMachine::searchHierarchie (int event)
{
  State *parentState = mActiveState;
  const Transition *trans = NULL;
  
  do
  {
    // evaluate new active state
    parentState = parentState->getParentState ();
    if (parentState == NULL)
        break;
    assert (parentState);
    
    // doesn't find default transition
    trans = parentState->getWalkTransition (event, false);
    
    if (trans)
    {
      cout << "StateMachine::searchHierarchie: father state '" << parentState-> getID () << "' has searched transition" << endl;
      cout << "StateMachine::searchHierarchie: getEvent (): " << trans->getEvent () << endl;
      cout << "StateMachine::searchHierarchie: getEndState (): " << trans->getEndState ()->getID () << endl;
      
      return trans->getEndState (); // return found state from hierarchie
    }
    else
    {
      cout << "StateMachine::searchHierarchie: father state '" << parentState-> getID () << "' hasn't searched event '" << event << "'" << endl;
    }
  }
  while (parentState->getParentState () != NULL);

  return NULL; // indicate that search wasn't successful
}

bool StateMachine::walkDown (int event)
{
  // check all possible transitions from current state 
  // this loops several times if default transitions are found... ->
  const Transition *trans = NULL;

  bool transit = false;
  do
  {
    // evaluate new active state
    cout << "evaluate new active state" << endl;
    assert (mActiveState);

    // map events...
    mActiveState->mapEvent (event);
    
    trans = mActiveState->getWalkTransition (event);
    
    if (trans)
    {
      cout << "getEvent (): " << trans->getEvent () << endl;
      cout << "getEndState (): " << trans->getEndState () << endl;

      mActiveState->runExitActions ();
      
      mActiveState->beforeTransitionCode ();
      
      mActiveState = trans->getEndState (); // do state change transition
      
      mActiveState->runEntryActions ();
      
      transit = true; // down transition was possible
    }
  }
  while (trans != NULL);
  // <-
  
  return transit;
}
