#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* local */
#include "stateval/Variable.h"
#include "MemoryUtil.h"

/* STD */
#include <cassert>

AbstractVariable::AbstractVariable (Type type) :
  mType (type)
{ 
}

AbstractVariable::Type AbstractVariable::getType () const
{
  return mType;
}

//////////////////////////

Bool::Bool (bool b) :
  AbstractVariable (TYPE_BOOL),
  mValue (b)
{
  
}

bool Bool::equals (AbstractVariable *var) const
{
  cout << "equals this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());
  
  bool ret = (static_cast <Bool*> (var))->mValue == mValue;
  
  return ret;
}

void Bool::assign (AbstractVariable *var)
{
  cout << "assign this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());

  mValue = (static_cast <Bool*> (var))->mValue;
}

bool Bool::getData () const
{
  return mValue;
}

//////////////////////////

Float::Float (float f) :
  AbstractVariable (TYPE_FLOAT),
  mValue (f)
{
  
}

bool Float::equals (AbstractVariable *var) const
{
  cout << "equals this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());
  
  float ret = (static_cast <Float*> (var))->mValue == mValue;
  
  return ret;
}

void Float::assign (AbstractVariable *var)
{
  cout << "assign this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());

  mValue = (static_cast <Float*> (var))->mValue;
}

float Float::getData () const
{
  return mValue;
}


//////////////////////////

String::String (const std::string &s) :
  AbstractVariable (TYPE_STRING),
  mValue (s)
{
  
}

bool String::equals (AbstractVariable *var) const
{
  cout << "equals this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());
  
  bool ret = (static_cast <String*> (var))->mValue == mValue;
  
  return ret;
}

void String::assign (AbstractVariable *var)
{
  cout << "assign this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());

  mValue = (static_cast <String*> (var))->mValue;
}

void String::change (const std::string &str)
{
  mValue = str;
}

std::string String::getData () const
{
  return mValue;
}

//////////////////////////

Struct::Struct () :
  AbstractVariable (TYPE_STRUCT)
{
}

Struct::~Struct ()
{
  delete_stl_container (mValueMap);
}

bool Struct::equals (AbstractVariable *var) const
{
  cout << "equals this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());

  // TODO: implement
  bool ret = false;//(static_cast <String*> (var))->mValue == mValue;
  assert (false);
  
  return ret;
}

void Struct::assign (AbstractVariable *var)
{
  cout << "assign this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());

  // TODO: implement
  //mValue = (static_cast <String*> (var))->mValue;
  assert (false);
}

void Struct::add (const std::string &s, AbstractVariable *var)
{
  mValueMap[s] = var;
}

AbstractVariable *Struct::getData (const std::string &s)
{
  cout << "mValueMap size: " << mValueMap.size () << endl;
  return mValueMap[s];
}

Struct::Iterator Struct::begin ()
{
  return mValueMap.begin ();
}

Struct::Iterator Struct::end ()
{
  return mValueMap.end ();
}

//////////////////////////

List::List () :
  AbstractVariable (TYPE_LIST)
{
}

List::~List ()
{
  clear ();
}

bool List::equals (AbstractVariable *var) const
{
  cout << "equals this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());

  // TODO: implement
  bool ret = false;//(static_cast <String*> (var))->mValue == mValue;
  assert (false);
  
  return ret;
}

void List::assign (AbstractVariable *var)
{
  cout << "assign this:Type: " << getType () << endl;
  cout << "var:Type: " << var->getType () << endl;
  assert (getType () == var->getType ());

  // TODO: implement
  //mValue = (static_cast <String*> (var))->mValue;
  assert (false);
}

void List::pushBack (AbstractVariable *var)
{
  mValueList.push_back (var);
}

void List::pushFront (AbstractVariable *var)
{
  mValueList.push_front (var);
}

void List::clear ()
{
  delete_stl_container (mValueList);
}

List::Iterator List::begin ()
{
  return mValueList.begin ();
}

List::Iterator List::end ()
{
  return mValueList.end ();
}