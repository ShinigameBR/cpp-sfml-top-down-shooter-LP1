#ifndef EXPLOSIVE_ENEMY_H
#define EXPLOSIVE_ENEMY_H

#include "../../components/headers/enemy.h"
#include "../../components/headers/player.h"
#include "../../components/headers/base.h"
#include "../../components/headers/config.h"

class ExplosiveEnemy : public Enemy
{
public:
    ExplosiveEnemy(Vector2f position);
    void update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets) override;
    void draw(RenderWindow &window) const override;
    bool isDead() const override;
    void takeDamage(int amount) override;
    void resolveCollision(const RectangleShape &otherShape);
    void explode(Player &player, Base &base, RenderWindow &window);
    RectangleShape getShape() const override;

private:
    void moveTowards(Time deltaTime, Vector2f &direction) override;
    void drawExplosion(RenderWindow &window);

    RectangleShape shape;
    CircleShape explosion;
    int health;
    float speed;
    float explosionRadius;
    bool dead;
};

#endif
