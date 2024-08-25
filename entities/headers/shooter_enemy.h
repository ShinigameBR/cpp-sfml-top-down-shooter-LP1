#ifndef SHOOTER_ENEMY_H
#define SHOOTER_ENEMY_H

#include "../../components/headers/enemy.h"
#include "../../components/headers/config.h"

class ShooterEnemy : public Enemy
{
public:
    ShooterEnemy(Vector2f position);
    void update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets);
    void draw(RenderWindow &window) const override;
    bool isDead() const override;
    void takeDamage(int amount) override;
    void resolveCollision(const RectangleShape &otherShape);
    RectangleShape getShape() const override;

private:
    RectangleShape shape;
    Time shootCooldown;
    float range;
    float speed;
    int health;
    bool dead;

    void moveTowards(Time deltaTime, Vector2f &direction) override;
    void shoot(Time deltaTime, Vector2f &direction, vector<Bullet> &enemyBullets);
};

#endif
