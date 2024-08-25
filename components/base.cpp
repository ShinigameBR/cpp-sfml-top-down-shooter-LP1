#include "./headers/base.h"

Base::Base(Vector2f position) : health(BASE_START_HEALTH)
{
    shape.setSize(BASE_START_SIZE);
    shape.setFillColor(BASE_START_COLOR);
    shape.setPosition(position);
}

void Base::draw(RenderWindow &window)
{
    window.draw(shape);
}

void Base::takeDamage(int amount)
{
    health -= amount;
}

int Base::getHealth()
{
    return health;
}

Vector2f Base::getPosition() const
{
    return shape.getPosition();
}

RectangleShape Base::getShape() const
{
    return shape;
}