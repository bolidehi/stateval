## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/state/glade
glade_DATA = state.glade

AM_CPPFLAGS = \
	$(STATE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = state

state_SOURCES = \
	main.cpp\
	UMLDrawer.cpp\
	UMLDrawer.h \
	Application.cpp \
	Application.h \
	AppMenuBar.cpp \
	AppMenuBar.h \
	Global.cpp \
	Global.h \
	AppToolBar.cpp \
	AppToolBar.h \
	SCObject.cpp \
	SCObject.h \
	CountedPtr.h \
	MathUtil.h \
	util.h \
	searchFile.cpp \
	searchFile.h \
	main.h \
	Primitive.cpp \
	Primitive.h \
	Rectangle.cpp \
	Rectangle.h \
	Circle.cpp \
	Circle.h \
	Curve.cpp \
	Curve.h \
	Text.cpp \
	Text.h \
	Transition.cpp \
	Transition.h \
	Condition.cpp \
	Condition.h \
	State.cpp \
	State.h \
	Types.cpp \
	Types.h \
	Vector2.h \
	Point.h \
	Rect.h \
	Size.h \
	History.cpp \
	History.h \
	Color.cpp \
	Color.h

state_LDFLAGS = 

state_LDADD = $(STATE_LIBS)

EXTRA_DIST = $(glade_DATA)
