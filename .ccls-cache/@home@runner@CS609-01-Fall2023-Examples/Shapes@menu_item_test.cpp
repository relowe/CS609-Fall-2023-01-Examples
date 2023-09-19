#include <iostream>
#include <string>
#include "menu_item.h"

class Test_Item : public Menu_Item
{
public:
    virtual std::string label();
    virtual void selected();
};

int main()
{
    Menu_Item *mi;  // <--- This is a pointer. If we want polymorphism, we use these

    // instantiate an object explicitly.
    mi = new Test_Item();

    std::cout << mi->label() << std::endl;
    mi->selected();

    // C++ has no garbage collector. You have to clean up your own objects!
    delete mi;
}


// Test_Item implementation
std::string Test_Item::label() 
{
    return "Test Item";
}


//
void Test_Item::selected()
{
    std::cout << "Test Item Selected" << std::endl;
}