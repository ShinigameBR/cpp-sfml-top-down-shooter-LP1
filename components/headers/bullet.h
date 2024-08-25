#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
public:
    Bullet(Vector2f position, Vector2f direction);

    void update(Time deltaTime);
    void draw(RenderWindow &window);
    bool isInBounds(View &view) const;
    bool isActive() const;
    void setActive(bool active);
    RectangleShape getShape() const;

private:
    RectangleShape shape;
    Vector2f velocity;
    float speed;
    bool active;
};

#endif
