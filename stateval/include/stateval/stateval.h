#ifndef STATEVAL_H
#define STATEVAL_H

/* gloabal include header
 */

#include "StateMachine.h"
#include "StateMachineAccess.h"
#include "StateMachineThread.h"
#include "EventList.h"
#include "SimpleState.h"
#include "ViewState.h"
#include "CompoundState.h"
#include "HistoryState.h"
#include "DecisionState.h"
#include "FireEventAction.h"
#include "GlobalVariables.h"
#include "Variable.h"

#if HAVE_EFL
#include "EdjeView.h"
#include "GraphicContext.h"
#endif

#endif // STATEVAL_H