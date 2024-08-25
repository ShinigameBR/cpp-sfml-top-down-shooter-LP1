#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Menu
{
public:
    Menu(float width, float height);
    void draw(RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex();

private:
    int selectedItemIndex;
    Font font;
    Text menu[2];
};

#endif
