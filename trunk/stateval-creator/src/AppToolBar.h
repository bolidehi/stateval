#ifndef APPTOOLBAR_H
#define APPTOOLBAR_H

#include <gtkmm.h>

class AppToolBar : public Gtk::HBox
{
public:
  AppToolBar (BaseObjectType* cobject, 
              const Glib::RefPtr<Gtk::Builder>& refGlade);
  ~AppToolBar ();
      
protected:
  void getGladeWidgets ();
  void connectSignalHandlers ();
  
  // signal handlers
  void onAddStateClicked ();
  void onAddConditionClicked ();
  void onAddHistoryClicked ();
  void onAddTransitionClicked ();
  void onNewDocumentClicked ();
  void onMoveClicked ();
  
private:
  Glib::RefPtr<Gtk::Builder> xml_glade;
  
  Gtk::ToolButton *mToolbuttonNewDocument;
  
  Gtk::ToolButton *mToolbuttonAddState;
  Gtk::Image *mToolbuttonAddStateImage;
  
  Gtk::ToolButton *mToolbuttonAddViewState;
  Gtk::Image *mToolbuttonAddViewStateImage;
  
  Gtk::ToolButton *mToolbuttonAddCompoundState;
  Gtk::Image *mToolbuttonAddCompoundStateImage;
  
  Gtk::ToolButton *mToolbuttonAddCondition;
  Gtk::Image *mToolbuttonAddConditionImage;

  Gtk::ToolButton *mToolbuttonAddHistory;
  Gtk::Image *mToolbuttonAddHistoryImage;

  Gtk::ToolButton *mToolbuttonAddDeepHistory;
  Gtk::Image *mToolbuttonAddDeepHistoryImage;
    
  Gtk::ToolButton *mToolbuttonAddTransition;
  Gtk::Image *mToolbuttonAddTransitionImage;
    
  Gtk::ToolButton *mToolbuttonAddStartState;
  Gtk::Image *mToolbuttonAddStartStateImage;
  
  Gtk::ToolButton *mToolbuttonAddFinishState;
  Gtk::Image *mToolbuttonAddFinishStateImage;
  
  Gtk::ToggleToolButton *mToggleToolbuttonMove;
  Gtk::Image *mToggleToolbuttonMoveImage;

  void setSelectionMode ();
};

#endif // APPTOOLBAR_H
