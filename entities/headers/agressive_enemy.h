#ifndef AGRESSIVE_ENEMY_H
#define AGRESSIVE_ENEMY_H

#include "../../components/headers/enemy.h"
#include "../../components/headers/config.h"

class AgressiveEnemy : public Enemy
{
public:
    AgressiveEnemy(Vector2f position);
    void update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets) override;
    void draw(RenderWindow &window) const override;
    bool isDead() const override;
    void takeDamage(int amount) override;
    void resolveCollision(const RectangleShape &otherShape);
    RectangleShape getShape() const override;

private:
    RectangleShape shape;
    float speed;
    int health;
    bool dead;

    void moveTowards(Time deltaTime, Vector2f &direction) override;
};

#endif
