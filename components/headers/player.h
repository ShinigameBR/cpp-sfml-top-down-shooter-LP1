#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <cmath>
#include "config.h"
#include "bullet.h"

class Player
{
public:
    Player(Vector2f position);

    void update(Time deltaTime, vector<Bullet> &bullets, RenderWindow &window);
    void draw(RenderWindow &window);
    void takeDamage(int amount);
    int getHealth();
    int getAmmo() const;
    void reloadAmmo(int amount);
    Vector2f getPosition() const;
    RectangleShape getShape() const;

private:
    RectangleShape shape;
    Vector2f velocity;
    float speed;
    int health;
    int ammo;
    Text ammoText;
    Font font;
    Time shootCooldown;

    void shoot(vector<Bullet> &bullets, RenderWindow &window);
};

#endif
