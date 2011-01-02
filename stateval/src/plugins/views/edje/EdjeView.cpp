#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

/* local */
#include "EdjeView.h"
#include "EdjeContext.h"
#include <elementaryxx/Elementaryxx.h>

/* stateval */
#include "stateval/stateval.h"

/* STD */
#include <iostream>

using namespace std;

const int width = 800;
const int height = 600;

static const char* type = "View";
static const unsigned int major_version = 1;
static const unsigned int minor_version = 1;

EdjeView::EdjeView (Context *context, const std::list <std::string> &params) :
  mStateMachineAccess (&StateMachineAccess::instance ()),
  mEdjeContext (NULL),
  mEvas (NULL),
  mEdje (NULL),
  groupState (Unrealized),
  param ("label", "blub")
{
  assert (context);
  
  //if (params.length () != 2)
    //throw something
  
  std::list <std::string>::const_iterator params_it = params.begin ();
  mFilename = *params_it;
  ++params_it;
  mGroupname = *params_it;

  mEdjeContext = static_cast <EdjeContext*> (context);
  mEvas = &mEdjeContext->getCanvas ();
  
  mRealizeDispatcher.signalDispatch.connect (sigc::mem_fun (this, &EdjeView::realizeDispatched));
  mUnrealizeDispatcher.signalDispatch.connect (sigc::mem_fun (this, &EdjeView::unrealizeDispatched));
}

const std::string EdjeView::getType ()
{
  return type;
}

const unsigned int EdjeView::getMajorVersion ()
{
  return major_version;
}

const unsigned int EdjeView::getMinorVersion ()
{
  return minor_version;
}

void EdjeView::realize ()
{  
  mRealizeDispatcher.signal ();
}

void EdjeView::unrealize ()
{
  cout << "+EdjeView::unrealize ()" << endl;
  
  mUnrealizeDispatcher.signal ();
  
  // wait for animation finished on statemachine thread
  condUnrealize.wait (mutexUnrealize);

  groupState = Unrealized;

  cout << "-EdjeView::unrealize ()" << endl;
}

void EdjeView::realizeDispatched (int missedEvents)
{
  cout << "EdjeView::realize ()" << endl;
  
  cout << "Filename: '" << mFilename << "', Groupname: " << mGroupname << endl;
      
  mEdje = new Edjexx::Object (*mEvas, mFilename, mGroupname);
  
  // connect visible/invisible handler
  mEdje->connect ("invisible_signal", "edje", sigc::mem_fun (this, &EdjeView::invisibleFunc));
  mEdje->connect ("visible_signal", "edje", sigc::mem_fun (this, &EdjeView::visibleFunc));

  mEdje->connect ("*", "edje", sigc::mem_fun (this, &EdjeView::edjeFunc));
  mEdje->connect ("*", "framework", sigc::mem_fun (this, &EdjeView::frameworkFunc));
  
  mEdje->connect ("*", "*", sigc::mem_fun (this, &EdjeView::allFunc));

  mEdje->resize (mEdjeContext->getResolution ());

  GlobalVariables &global = GlobalVariables::instance ();
  
  for (WidgetIterator wl_it = beginOfWidgets ();
       wl_it != endOfWidgets ();
       ++wl_it)
  {
    const Widget &w = *wl_it;
    
    AbstractVariable *val = global.getVariable (w.getVariable ());
    Edjexx::Part &part = mEdje->getPart (w.getName ());

    // TODO: it'n not a good design to relay on TYPE_STRUCT is a external widget...
    // TODO: handle where ever possible as ExternalParams as much generic as possible...
    if (val->getType () == AbstractVariable::TYPE_STRUCT)
    {
      Struct *st = static_cast <Struct*> (val);

      try
      {
        // The code below accesses a Edje External widget (here: Elementary Slider) in a type save way
        Evasxx::Object &ext_eo3 = part.getExternalObject ();
        Evasxx::Object &eo3 = part.getSwallow ();
        cout << "Edje External Widget type: " << ext_eo3.getType () << endl;
        cout << "Edje Part Widget type: " << eo3.getType () << endl;
        
        if (ext_eo3.getType () == "elm_widget")
        {
          Elmxx::Object &elm_object = *(static_cast <Elmxx::Object*> (&ext_eo3));

          cout << "Elm Widget type: " << elm_object.getWidgetType () << endl;
          if (elm_object.getWidgetType () == "slider")
          {
            Elmxx::Slider &slider = *(static_cast <Elmxx::Slider*> (&elm_object));
            AbstractVariable *av1 = st->getData ("label");
            if (av1->getType () == AbstractVariable::TYPE_STRING)
            {
              String *s1 = static_cast <String*> (av1);
              slider.setLabel (s1->getData ());
            }
            
            AbstractVariable *av2 = st->getData ("value");
            if (av2->getType () == AbstractVariable::TYPE_FLOAT)
            {
              Float *f1 = static_cast <Float*> (av2);
              slider.setValue (f1->getData ());
            }
          }
          else if (elm_object.getWidgetType () == "bubble")
          {
            Elmxx::Entry &slider = *(static_cast <Elmxx::Entry*> (&elm_object));
            AbstractVariable *av1 = st->getData ("info");
            if (av1->getType () == AbstractVariable::TYPE_STRING)
            {
              String *s1 = static_cast <String*> (av1);
              Edjexx::ExternalParam param ("info", s1->getData ());

              part.setParam (&param);
            }
            
            av1 = st->getData ("label");
            if (av1->getType () == AbstractVariable::TYPE_STRING)
            {
              String *s1 = static_cast <String*> (av1);
              Edjexx::ExternalParam param ("label", s1->getData ());

              part.setParam (&param);
            }

            // hm, content isn't working, even not in editje, maybe Elm bug?
            av1 = st->getData ("content");
            if (av1->getType () == AbstractVariable::TYPE_STRING)
            {
              String *s1 = static_cast <String*> (av1);
              Edjexx::ExternalParam param ("content", s1->getData ());

              part.setParam (&param);
            }
          }          
        }
      }
      catch (Edjexx::PartNotExistingException pne)
      {
        cerr << pne.what () << endl;
      }
      catch (Edjexx::ExternalNotExistingException ene)
      {
        cerr << ene.what () << endl;
      }
    }
    else if (val->getType () == AbstractVariable::TYPE_STRING)
    {
      String *str = static_cast <String*> (val);
      
      part.setText (str->getData ());
    }
    
    cout << "Widget name: " << w.getName () << endl;
    cout << "Widget variable: " << w.getVariable () << endl;
  }
  
  mEdje->setLayer (0);
  mEdje->show ();

  groupState = Realizing;
  mEdje->emit ("visible", "framework");
}

void EdjeView::unrealizeDispatched (int missedEvents)
{
  if (mEdje)
  {
    groupState = Unrealizing;
    mEdje->emit ("invisible", "framework");
  }
}

void EdjeView::invisibleFunc (const std::string emmision, const std::string source)
{
  cout << "invisibleFunc" << endl;

  delete mEdje;
  mEdje = NULL;
  
  // signal the edje statemachine thread that the animation is finished
  condUnrealize.signal ();
}

void EdjeView::visibleFunc (const std::string emmision, const std::string source)
{
  cout << "visibleFunc" << endl;
  
  groupState = Realized;
}

void EdjeView::frameworkFunc (const std::string emmision, const std::string source)
{
  cout << "frameworkFunc: " << emmision << ", " << source << endl;
}

void EdjeView::edjeFunc (const std::string emmision, const std::string source)
{
  cout << "edjeFunc: " << emmision << ", " << source << endl;
}

void EdjeView::allFunc (const std::string emmision, const std::string source)
{
  cout << "allFunc: " << emmision << ", " << source << endl;
  string event (source + "#" + emmision);

  // only push new events for realized screens
  // when I do this it leads into freezes as the invisible signal doesn't come
  //if (groupState != Realized) return;
  
  if (mStateMachineAccess->findMapingEvent (event) != -1)
  {
    cout << "mStateMachineAccess->pushEvent" << endl;
    mStateMachineAccess->pushEvent (event); //"Button01#clicked"
  }
}

/*****************************/
/* Plugin needed C functions */
/*****************************/

PLUGIN_EXPORT EdjeView *plugin_create (Context *context, const std::list <std::string> &params)
{
  return new EdjeView (context, params);
}

PLUGIN_EXPORT void plugin_destroy (View *plugin)
{
  delete plugin;
}

PLUGIN_EXPORT const char *get_plugin_type ()
{
  return type;
}

PLUGIN_EXPORT unsigned int get_plugin_major_version ()
{
  return major_version;
}
