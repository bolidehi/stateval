#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* STD */
#include <iostream>

/* Project */
#include "AppToolBar.h"
//#include "ConfigFile.h"
#include "main.h"
#include "Global.h"
#include "UMLDrawer.h"
#include "searchFile.h"

using namespace std;

AppToolBar::AppToolBar(BaseObjectType *cobject,
                       const Glib::RefPtr<Gtk::Builder>& refGlade) :
  Gtk::HBox(cobject),
  xml_glade(refGlade),
  mToolbuttonNewDocument(NULL),
  mToolbuttonAddState(NULL),
  mToolbuttonAddStateImage(NULL),
  mToolbuttonAddViewState(NULL),
  mToolbuttonAddViewStateImage(NULL),
  mToolbuttonAddCompoundState(NULL),
  mToolbuttonAddCompoundStateImage(NULL),
  mToolbuttonAddCondition(NULL),
  mToolbuttonAddConditionImage(NULL),
  mToolbuttonAddHistory(NULL),
  mToolbuttonAddHistoryImage(NULL),
  mToolbuttonAddDeepHistory(NULL),
  mToolbuttonAddDeepHistoryImage(NULL),
  mToolbuttonAddTransition(NULL),
  mToolbuttonAddTransitionImage(NULL),
  mToolbuttonAddStartState(NULL),
  mToolbuttonAddStartStateImage(NULL),
  mToolbuttonAddFinishState(NULL),
  mToolbuttonAddFinishStateImage(NULL),
  mToggleToolbuttonMove(NULL),
  mToggleToolbuttonMoveImage(NULL)
{
  getGladeWidgets();
  connectSignalHandlers();
}

AppToolBar::~AppToolBar()
{
}

void AppToolBar::getGladeWidgets()
{
  xml_glade->get_widget("toolbuttonNewDocument", mToolbuttonNewDocument);
  xml_glade->get_widget("toolbuttonAddState", mToolbuttonAddState);
  xml_glade->get_widget("toolbuttonAddViewState", mToolbuttonAddViewState);
  xml_glade->get_widget("toolbuttonAddCompoundState", mToolbuttonAddCompoundState);
  xml_glade->get_widget("toolbuttonAddCondition", mToolbuttonAddCondition);
  xml_glade->get_widget("toolbuttonAddHistory", mToolbuttonAddHistory);
  xml_glade->get_widget("toolbuttonAddDeepHistory", mToolbuttonAddDeepHistory);
  xml_glade->get_widget("toolbuttonAddTransition", mToolbuttonAddTransition);
  xml_glade->get_widget("toolbuttonAddStartState", mToolbuttonAddStartState);
  xml_glade->get_widget("toolbuttonAddFinishState", mToolbuttonAddFinishState);
  xml_glade->get_widget("toggleToolbuttonMove", mToggleToolbuttonMove);

  mToolbuttonAddStateImage = manage(new Gtk::Image(searchPixmapFile("state.png")));
  mToolbuttonAddState->set_icon_widget(*mToolbuttonAddStateImage);

  mToolbuttonAddViewStateImage = manage(new Gtk::Image(searchPixmapFile("view_state.png")));
  mToolbuttonAddViewState->set_icon_widget(*mToolbuttonAddViewStateImage);

  mToolbuttonAddCompoundStateImage = manage(new Gtk::Image(searchPixmapFile("compound_state.png")));
  mToolbuttonAddCompoundState->set_icon_widget(*mToolbuttonAddCompoundStateImage);

  mToolbuttonAddConditionImage = manage(new Gtk::Image(searchPixmapFile("condition.png")));
  mToolbuttonAddCondition->set_icon_widget(*mToolbuttonAddConditionImage);

  mToolbuttonAddHistoryImage = manage(new Gtk::Image(searchPixmapFile("history.png")));
  mToolbuttonAddHistory->set_icon_widget(*mToolbuttonAddHistoryImage);

  mToolbuttonAddDeepHistoryImage = manage(new Gtk::Image(searchPixmapFile("deep_history.png")));
  mToolbuttonAddDeepHistory->set_icon_widget(*mToolbuttonAddDeepHistoryImage);

  mToolbuttonAddTransitionImage = manage(new Gtk::Image(searchPixmapFile("transition.png")));
  mToolbuttonAddTransition->set_icon_widget(*mToolbuttonAddTransitionImage);

  mToolbuttonAddStartStateImage = manage(new Gtk::Image(searchPixmapFile("start_state.png")));
  mToolbuttonAddStartState->set_icon_widget(*mToolbuttonAddStartStateImage);

  mToolbuttonAddFinishStateImage = manage(new Gtk::Image(searchPixmapFile("final_state.png")));
  mToolbuttonAddFinishState->set_icon_widget(*mToolbuttonAddFinishStateImage);

  mToggleToolbuttonMoveImage = manage(new Gtk::Image(searchPixmapFile("move.png")));
  mToggleToolbuttonMove->set_icon_widget(*mToggleToolbuttonMoveImage);
}

void AppToolBar::connectSignalHandlers()
{
  mToolbuttonNewDocument->signal_clicked().connect(sigc::mem_fun(*this,
      &AppToolBar::onNewDocumentClicked));

  mToolbuttonAddState->signal_clicked().connect(sigc::mem_fun(*this,
      &AppToolBar::onAddStateClicked));

  mToolbuttonAddCondition->signal_clicked().connect(sigc::mem_fun(*this,
      &AppToolBar::onAddConditionClicked));

  mToolbuttonAddHistory->signal_clicked().connect(sigc::mem_fun(*this,
      &AppToolBar::onAddHistoryClicked));


  mToolbuttonAddTransition->signal_clicked().connect(sigc::mem_fun(*this,
      &AppToolBar::onAddTransitionClicked));

  mToggleToolbuttonMove->signal_toggled().connect(sigc::mem_fun(*this,
      &AppToolBar::onMoveClicked));
}

void AppToolBar::onAddStateClicked()
{
  Global &global = Global::instance();

  setSelectionMode();

  UMLDrawer *umlDrawer = global.getUMLDrawer();
  umlDrawer->setOperationMode(UMLDrawer::ModeAddState);
}

void AppToolBar::onAddConditionClicked()
{
  Global &global = Global::instance();

  setSelectionMode();

  UMLDrawer *umlDrawer = global.getUMLDrawer();
  umlDrawer->setOperationMode(UMLDrawer::ModeAddCondition);
}

void AppToolBar::onAddHistoryClicked()
{
  Global &global = Global::instance();

  setSelectionMode();

  UMLDrawer *umlDrawer = global.getUMLDrawer();
  umlDrawer->setOperationMode(UMLDrawer::ModeAddHistory);
}

void AppToolBar::onAddTransitionClicked()
{
  Global &global = Global::instance();

  setSelectionMode();

  UMLDrawer *umlDrawer = global.getUMLDrawer();
  umlDrawer->setOperationMode(UMLDrawer::ModeAddTransitionStart);
}

void AppToolBar::onNewDocumentClicked()
{
  Global &global = Global::instance();

  setSelectionMode();

  UMLDrawer *umlDrawer = global.getUMLDrawer();

  umlDrawer->newDocument();
}

void AppToolBar::onMoveClicked()
{
  Global &global = Global::instance();

  UMLDrawer *umlDrawer = global.getUMLDrawer();

  if (mToggleToolbuttonMove->get_active())
  {
    umlDrawer->deselectObject();
    umlDrawer->setOperationMode(UMLDrawer::ModeMoveResizeRequest);
  }
  else
  {
    umlDrawer->deselectObject();
    umlDrawer->setOperationMode(UMLDrawer::ModeSelect);
  }
}

void AppToolBar::setSelectionMode()
{
  mToggleToolbuttonMove->set_active(false);
}
