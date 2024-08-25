#ifndef BASE_H
#define BASE_H

#include "config.h"

class Base
{
public:
    Base(Vector2f position);

    void draw(RenderWindow &window);
    void takeDamage(int amount);
    int getHealth();
    Vector2f getPosition() const;
    RectangleShape getShape() const;

private:
    RectangleShape shape;
    int health;
};

#endif
