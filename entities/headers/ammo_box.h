#ifndef AMMO_BOX_H
#define AMMO_BOX_H

#include <SFML/Graphics.hpp>
#include "../../components/headers/player.h"
using namespace sf;

class AmmoBox
{
public:
    AmmoBox(Vector2f position);
    void resolveCollision(Player &player);
    void draw(RenderWindow &window) const;
    bool isCollected() const;
    void collect();
    RectangleShape getShape() const;

private:
    RectangleShape shape;
    bool collected;
};

#endif
