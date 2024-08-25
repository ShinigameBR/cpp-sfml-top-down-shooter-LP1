#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream> // temp
#include <vector>
#include <cmath>
#include <list>
#include "../../components/headers/bullet.h"
using namespace sf;
using namespace std;

class Enemy
{
public:
    virtual ~Enemy() = default;
    virtual void update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets) = 0;
    virtual void draw(RenderWindow &window) const = 0;
    virtual bool isDead() const = 0;
    virtual void takeDamage(int amount) = 0;
    virtual void resolveCollision(const RectangleShape &otherShape) = 0;
    virtual RectangleShape getShape() const = 0;

private:
    virtual void moveTowards(Time deltaTime, Vector2f &direction) = 0;
};

#endif
