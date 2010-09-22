#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

/* STD */
#include <cassert>
#include <cmath>
#include <iostream>

/* CAIRO */
#include <cairomm/context.h>

/* Project */
#include "util.h"
#include "UMLDrawer.h"
#include "Types.h"

using namespace std;

UMLDrawer::UMLDrawer (BaseObjectType* cobject,
                      const Glib::RefPtr<Gtk::Builder>& refGlade) :
  Gtk::DrawingArea (cobject),
  mXMLGlade (refGlade),
  mOperationState (UMLDrawer::ModeSelect),
  mSelectedObject (NULL),
  mUmlEditMenu (NULL),
  mUmlEditDel (NULL)
{
  getGladeWidgets ();
  
  connectSignalHandlers ();
}

UMLDrawer::~UMLDrawer ()
{
  clear ();
}

void UMLDrawer::getGladeWidgets ()
{
  mXMLGlade->get_widget ("umlEditMenu", mUmlEditMenu);
  //mXMLGlade->get_widget ("umlEditDel", mUmlEditDel);
}

void UMLDrawer::connectSignalHandlers ()
{
  add_events (Gdk::POINTER_MOTION_MASK |
		          Gdk::POINTER_MOTION_HINT_MASK |
		          Gdk::BUTTON_PRESS_MASK |
              Gdk::BUTTON_RELEASE_MASK);
  
  if (mUmlEditDel)
  {
    mUmlEditDel->signal_activate ().connect(sigc::mem_fun (*this,
                                            &UMLDrawer::onUmlEditDel) );
  }
}

void UMLDrawer::onUmlEditDel ()
{
  
}

void UMLDrawer::clear ()
{
  for_each (mSCObjectList.begin (),
            mSCObjectList.end (),
            delete_one <SC::Object>);
  mSCObjectList.clear ();
}

void UMLDrawer::deselectAllObjects ()
{
  SC::Object *scObject = NULL;
  for (std::list <SC::Object*>::iterator sc_it = mSCObjectList.begin ();
       sc_it != mSCObjectList.end ();
       ++sc_it)
  {
    scObject = *sc_it;
    scObject->setSelected (false);
  }
}

void UMLDrawer::newDocument ()
{
  clear ();
  
  redraw ();
}

void UMLDrawer::setOperationMode (UMLDrawerStates opState)
{
  mOperationState = opState;
}

UMLDrawer::UMLDrawerStates UMLDrawer::getOperationMode ()
{
  return mOperationState;
}

void UMLDrawer::selectObject (SC::Object *scObject)
{
  mSelectedObject = scObject;

  // currently don't allow multi selection of objects
  deselectAllObjects ();

  if (mSelectedObject)
  {
    mSelectedObject->setSelected (true);
  }
}

void UMLDrawer::deselectObject ()
{
  if (mSelectedObject)
  {
    mSelectedObject->setSelected (false);
    mSelectedObject = NULL;
  }
}

SC::Object *UMLDrawer::getSelectedObject ()
{
  return mSelectedObject;
}

void UMLDrawer::addState (const Point &pos)
{
  State *scState = new State (pos);
  selectObject (scState);
  
  mSCObjectList.push_back (scState);

  redraw ();
}

void UMLDrawer::addCondition (const Point &pos)
{
  Condition *scCond  = new Condition (pos);
  selectObject (scCond);
  
  mSCObjectList.push_back (scCond);

  redraw ();
}

void UMLDrawer::addHistory (const Point &pos)
{
  History *scHist  = new History (pos);
  selectObject (scHist);
  
  mSCObjectList.push_back (scHist);

  redraw ();
}

void UMLDrawer::addTransition (const SC::Object &fromState, const SC::Object &toState)
{
  Transition *scTrans = new Transition (fromState, toState);
  selectObject (scTrans);
  
  mSCObjectList.push_back (scTrans);

  redraw ();
}

/*
typedef struct {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble *axes;
  guint state;
  gint16 is_hint;
  GdkDevice *device;
  gdouble x_root, y_root;
} GdkEventMotion;
*/
bool UMLDrawer::on_motion_notify_event (GdkEventMotion* event)
{
  Point mousePos (event->x, event->y);
  // cursor choose help: http://www.pygtk.org/docs/pygtk/class-gdkcursor.html

  switch (mOperationState)
  {
    case ModeMoveResizeRequest:
      {
        SC::Object *scObjectHit = NULL;
        for (std::list <SC::Object*>::iterator sc_it = mSCObjectList.begin ();
             sc_it != mSCObjectList.end ();
             ++sc_it)
        {
          scObjectHit = *sc_it;

          if (scObjectHit->isHitBy (Inset, mousePos))
          {
            Glib::RefPtr <Gdk::Window> window_ref = get_window();
            window_ref->set_cursor (Gdk::Cursor(Gdk::FLEUR));
            break;
          }
          else if (scObjectHit->isHitBy (Border, mousePos))
          {
            Glib::RefPtr <Gdk::Window> window_ref = get_window();
            window_ref->set_cursor (Gdk::Cursor(Gdk::DRAPED_BOX));
            break;
          }
          else
          {
            Glib::RefPtr <Gdk::Window> window_ref = get_window();
            window_ref->set_cursor (Gdk::Cursor());
          }
            scObjectHit = NULL;
        }        
      }
      break;

      default:
        Glib::RefPtr <Gdk::Window> window_ref = get_window();
        window_ref->set_cursor (Gdk::Cursor());
  }
  
  switch (mOperationState)
  {
    case ModeMove:
      if (getSelectedObject ())
      {
        getSelectedObject ()->moveTo (mousePos + mMoveDelta);
        redraw ();
      }
      break;

    case ModeResize:
      if (getSelectedObject ())
      {
        Point diffPoint (mousePos - getSelectedObject ()->getPos ());
        Sized size = convertPoint2Sized (diffPoint);

        // FIXME: limit width/height separate from each other...
        if ((size.getWidth () > 10) && (size.getHeight () > 10))
        {
          getSelectedObject ()->resizeTo (size);
          redraw ();
        }
      }
      break;
      
    default:
      break;
  }
}

bool UMLDrawer::on_button_release_event (GdkEventButton *event)
{
  switch (getOperationMode ())
  {
    case ModeMove:
      setOperationMode (ModeMoveResizeRequest);
      deselectObject ();
      break;

    case ModeResize:
      setOperationMode (ModeMoveResizeRequest);
      deselectObject ();
      break;
      
    default:
      break;
  }
}

/*typedef struct {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble *axes;
  guint state;
  guint button;
  GdkDevice *device;
  gdouble x_root, y_root;
} GdkEventButton;
*/
bool UMLDrawer::on_button_press_event (GdkEventButton* event)
{ 
  Point mousePos (event->x, event->y);

  cout << "onMousePressed: " << event->button << " : " << event->state << endl;
  cout << "x: " << event->x << " , y: " << event->y << endl;
  
  SC::Object *scObjectHit = NULL;
  for (std::list <SC::Object*>::iterator sc_it = mSCObjectList.begin ();
       sc_it != mSCObjectList.end ();
       ++sc_it)
  {
    scObjectHit = *sc_it;

    if (scObjectHit->isHitBy (Complete, mousePos))
    {
      cout << "Hit!" << endl;
      break;
    }
    scObjectHit = NULL;
  }

  Point pos;
  switch (getOperationMode ())
  {
    case ModeSelect:
      selectObject (scObjectHit);
      break;
      
    case ModeMoveResizeRequest:
      selectObject (scObjectHit);
      if (getSelectedObject ())
      {
        if (getSelectedObject ()->isHitBy (Border, mousePos))
        {
          // resize
          setOperationMode (ModeResize);
        }
        else
        {
          // move
          pos = getSelectedObject ()->getPos ();
          mMoveDelta = pos - mousePos;
          setOperationMode (ModeMove);
        }
      }
      break;
      
    case ModeAddState:
      addState (mousePos);
      setOperationMode (ModeSelect);
      break;
      
    case ModeAddCondition:
      addCondition (mousePos);
      setOperationMode (ModeSelect);
      break;

    case ModeAddHistory:
      addHistory (mousePos);
      setOperationMode (ModeSelect);
      break;
      
    case ModeAddTransitionStart:
      cout << "started transition" << endl;
      selectObject (scObjectHit);
      setOperationMode (ModeAddTransitionEnd);
      break;
      
    case ModeAddTransitionEnd:
      cout << "ended transition" << endl;
      if (getSelectedObject () && scObjectHit)
      {
        addTransition (*getSelectedObject (), *scObjectHit);
      }
      setOperationMode (ModeSelect);
      deselectObject ();
      break;
      
    default:
      break;
  }
  
  if (event->button == 3)
  {
    cout << "button 3" << endl; 
    /*popup  	(  	guint   	 button,
		guint32  	activate_time	 
	) 		*/	
  }
  
  return true;
}

bool UMLDrawer::on_expose_event (GdkEventExpose* event)
{
  double m_radius(0.42);
  double m_line_width(0.05);
  
  Gtk::Allocation allocation = get_allocation ();
  const int width = allocation.get_width ();
  const int height = allocation.get_height ();

    // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window ();
  assert (window);
  
  cr = window->create_cairo_context ();
  assert (cr);

  if (event)
  {
    // clip to the area indicated by the expose event so that we only
    // redraw the portion of the window that needs to be redrawn
    cr->rectangle (event->area.x, event->area.y,
                   event->area.width, event->area.height);
    cr->clip();
  }

  cr->set_line_width (2.0);
  
  for (std::list <SC::Object*>::iterator sc_it = mSCObjectList.begin ();
       sc_it != mSCObjectList.end ();
       ++sc_it)
  {
    SC::Object *scObject = *sc_it;

    scObject->render (cr);
  }

  return true;
}

void UMLDrawer::redraw ()
{
  Glib::RefPtr<Gdk::Window> window = get_window();
  assert (window);

  // TODO: possible optimization by defining the rect for redraw after creating a new object...
  Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                   get_allocation().get_height());

  window->invalidate_rect (r, false);
}
