///////////////////////////////////////////////////////////////////////////
// File: menu_item.h
// Purpose: Class definition of an abstract menu item class.
//          (Basically equivalent to a Java interface)
///////////////////////////////////////////////////////////////////////////
#ifndef MENU_ITEM_H
#define MENU_ITEM_H
#include <string>

class Menu_Item
{
public:
    // pure virtual function which returns the label of this item
    virtual std::string label()=0;

    // pure virtual function which performs the action of this item
    virtual void selected()=0;
};
#endif