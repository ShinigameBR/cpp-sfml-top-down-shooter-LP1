#include "./headers/menu.h"

Menu::Menu(float width, float height)
{
    font.loadFromFile("./assets/fonts/dogica/OTF/dogicapixel.otf");

    // "Jogar"
    menu[0].setFont(font);
    menu[0].setFillColor(Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(Vector2f(width / 2 - menu[0].getLocalBounds().width / 2, height / (2 + 1) * 1));

    // "Sair"
    menu[1].setFont(font);
    menu[1].setFillColor(Color::White);
    menu[1].setString("Quit");
    menu[1].setPosition(Vector2f(width / 2 - menu[1].getLocalBounds().width / 2, height / (2 + 1) * 2));

    selectedItemIndex = 0;
}

void Menu::draw(RenderWindow &window)
{
    for (int i = 0; i < 2; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 < 2)
    {
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(Color::Red);
    }
}

int Menu::getSelectedItemIndex()
{
    return selectedItemIndex;
}
