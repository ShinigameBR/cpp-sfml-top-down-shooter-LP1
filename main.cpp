#include "./components/headers/menu.h"
#include "./components/headers/game.h"

int main()
{
    RenderWindow window(VideoMode(800, 600), "Base Defense Game Menu", Style::Close);
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    menu.moveUp();
                }
                else if (event.key.code == Keyboard::Down)
                {
                    menu.moveDown();
                }
                else if (event.key.code == Keyboard::Return)
                {
                    int selectedItemIndex = menu.getSelectedItemIndex();
                    if (selectedItemIndex == 0) // Jogar
                    {
                        window.close();
                        Game game;
                        game.run();
                    }
                    else if (selectedItemIndex == 1) // Sair
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
