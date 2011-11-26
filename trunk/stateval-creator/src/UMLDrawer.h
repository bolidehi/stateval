#ifndef UML_DRAWER_H
#define UML_DRAWER_H

/* GTK */
#include <gtkmm/drawingarea.h>
#include <gtkmm.h>

/* Project */
#include "CountedPtr.h"
#include "SCObject.h"
#include "Transition.h"
#include "Condition.h"
#include "State.h"
#include "History.h"

class UMLDrawer : public Gtk::DrawingArea
{
public:
  enum UMLDrawerStates
  {
    ModeSelect,
    ModeMove,
    ModeResize,
    ModeMoveResizeRequest,
    ModeAddState,
    ModeAddCondition,
    ModeAddHistory,
    ModeAddTransitionStart,
    ModeAddTransitionEnd
  };

  UMLDrawer(BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~UMLDrawer();

  void newDocument();

  void deselectAllObjects();

  void setOperationMode(UMLDrawerStates);

  UMLDrawerStates getOperationMode();

  void selectObject(SC::Object *scObject);

  void deselectObject();

  SC::Object *getSelectedObject();

  void addState(const Point &pos);

  void addCondition(const Point &pos);

  void addHistory(const Point &pos);

  void addTransition(const SC::Object &fromState, const SC::Object &toState);

protected:
  //Override default signal handler:
  bool on_expose_event(GdkEventExpose *event);

  bool on_button_press_event(GdkEventButton *event);

  bool on_button_release_event(GdkEventButton *event);

  bool on_motion_notify_event(GdkEventMotion *event);

  void redraw();

  void clear();

private:
  void connectSignalHandlers();

  void getGladeWidgets();

  void onUmlEditDel();

  Glib::RefPtr<Gtk::Builder> mXMLGlade;
  Cairo::RefPtr<Cairo::Context> cr;

  std::list <SC::Object *> mSCObjectList; // TODO: free this!!

  enum UMLDrawerStates mOperationState;

  SC::Object *mSelectedObject;

  Gtk::Menu *mUmlEditMenu;
  Gtk::MenuItem *mUmlEditDel;

  Point mMoveDelta;
};


#endif // UML_DRAWER_H
