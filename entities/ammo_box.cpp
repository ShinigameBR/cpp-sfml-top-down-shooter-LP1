#include "./headers/ammo_box.h"

AmmoBox::AmmoBox(Vector2f position)
    : collected(false)
{
    shape.setSize(Vector2f(10.f, 10.f));
    shape.setFillColor(Color::Yellow);
    shape.setPosition(position);
}

void AmmoBox::resolveCollision(Player &player)
{
    FloatRect ammoBox = shape.getGlobalBounds();
    FloatRect playerBounds = player.getShape().getGlobalBounds();

    if (ammoBox.intersects(playerBounds))
    {
        player.reloadAmmo(50);
        collect();
    }
}
void AmmoBox::draw(RenderWindow &window) const
{
    if (!collected)
    {
        window.draw(shape);
    }
}

RectangleShape AmmoBox::getShape() const
{
    return shape;
}

bool AmmoBox::isCollected() const
{
    return collected;
}

void AmmoBox::collect()
{
    collected = true;
}
