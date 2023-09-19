#include <iostream>
#include <string>
#include "menu.h"
#include "menu_item.h"

class Test_Item : public Menu_Item
{
public:
    Test_Item(const std::string &_label);
    virtual std::string label();
    virtual void selected();
private:
    std::string _label;
}

int main()
{
    Menu m;

    //add the menu items
    m.add_item(new Test_Item("Choice 1"));
    m.add_item(new Test_Item("Choice 2"));
    m.add_item(new Test_Item("Choice 3"));

    //run it forever
    while(true) {
        m.run():
    }
}


// Test item implementation
Test_Item::Test_Item(const std::string &_label)
{
    this->_label = _label;
}

std::string Test_Item::label()
{
    return this->_label;
}

void Test_Item::selected()
{
    std::cout << label() << " Selected" << std::endl;
}