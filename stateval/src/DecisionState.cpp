#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include "../include/stateval/DecisionState.h"

DecisionState::DecisionState (State *parentState) :
  State (parentState),
  mElseTrans (NULL)
{
}

DecisionState::~DecisionState ()
{
  // free mLeaveTransitonList
  for (std::list <std::pair <Condition*, Transition*> >::iterator ct_it = mConditionList.begin ();
       ct_it != mConditionList.end ();
       ++ct_it)
  {
    std::pair <Condition*, Transition*> &conTrans = *ct_it;
    delete conTrans.first;
    delete conTrans.second;
  }
}

void DecisionState::addConditionTransition (const std::pair <Condition*, Transition*> &conTrans)
{
  mConditionList.push_back (conTrans);
}

void DecisionState::beforeTransitionCode ()
{  
}

void DecisionState::afterTransitionCode ()
{
}

void DecisionState::mapEvent (int &inOutEvent)
{

}
 
const Transition *DecisionState::getWalkTransition (int event, bool walkDefaultTransition) const
{
  for (std::list <std::pair <Condition*, Transition*> >::const_iterator cl_it = mConditionList.begin ();
       cl_it !=  mConditionList.end ();
       ++cl_it)
  {
    const std::pair <Condition*, Transition*> &conTran = *cl_it;

    if (conTran.first->evaluate ())
    {
      return conTran.second;
    }
  }

  return mElseTrans;
}

void DecisionState::runEntryActions ()
{
}

void DecisionState::runExitActions ()
{
}