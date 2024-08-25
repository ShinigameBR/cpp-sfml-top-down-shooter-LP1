#include "./headers/bullet.h"

Bullet::Bullet(Vector2f position, Vector2f direction)
    : speed(300.0f), active(true)
{
    shape.setSize(Vector2f(5, 10));
    shape.setFillColor(Color::Yellow);
    shape.setPosition(position);
    velocity = direction * speed;
}

void Bullet::update(Time deltaTime)
{
    if (active)
    {
        shape.move(velocity * deltaTime.asSeconds());
    }
}

void Bullet::draw(RenderWindow &window)
{
    if (active)
    {
        window.draw(shape);
    }
}

bool Bullet::isInBounds(View &view) const
{
    return shape.getPosition().y + shape.getSize().y >= 0 &&
           shape.getPosition().y <= view.getSize().y &&
           shape.getPosition().x + shape.getSize().x >= 0 &&
           shape.getPosition().x <= view.getSize().x;
}

bool Bullet::isActive() const
{
    return active;
}

void Bullet::setActive(bool active)
{
    this->active = active;
}

RectangleShape Bullet::getShape() const
{
    return shape;
}