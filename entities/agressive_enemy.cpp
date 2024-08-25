#include "./headers/agressive_enemy.h"

AgressiveEnemy::AgressiveEnemy(Vector2f position) : speed(AGRESSIVE_ENEMY_START_SPEED), health(AGRESSIVE_ENEMY_START_HEALTH), dead(false)
{
    shape.setSize(AGRESSIVE_ENEMY_START_SIZE);
    shape.setFillColor(AGRESSIVE_ENEMY_START_COLOR);
    shape.setPosition(position);
}

void AgressiveEnemy::update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets)
{
    Vector2f target = (hypot(playerPosition.x - shape.getPosition().x, playerPosition.y - shape.getPosition().y) <
                       hypot(basePosition.x - shape.getPosition().x, basePosition.y - shape.getPosition().y))
                          ? playerPosition
                          : basePosition;

    Vector2f direction = target - shape.getPosition();
    moveTowards(deltaTime, direction);
}

void AgressiveEnemy::moveTowards(Time deltaTime, Vector2f &direction)
{
    float distanceToTarget = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distanceToTarget > 20.f)
    {
        direction /= distanceToTarget;
        shape.move(direction * speed * deltaTime.asSeconds());
    }
}

void AgressiveEnemy::draw(RenderWindow &window) const
{
    window.draw(shape);
}

bool AgressiveEnemy::isDead() const
{
    return dead;
}

void AgressiveEnemy::takeDamage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        dead = true;
    }
}

void AgressiveEnemy::resolveCollision(const RectangleShape &otherShape)
{
    FloatRect enemyBounds = shape.getGlobalBounds();
    FloatRect otherBounds = otherShape.getGlobalBounds();

    if (enemyBounds.intersects(otherBounds))
    {
        if (enemyBounds.left < otherBounds.left)
            shape.move(-1.f, 0.f);
        else if (enemyBounds.left + enemyBounds.width > otherBounds.left + otherBounds.width)
            shape.move(1.f, 0.f);

        if (enemyBounds.top < otherBounds.top)
            shape.move(0.f, -1.f);
        else if (enemyBounds.top + enemyBounds.height > otherBounds.top + otherBounds.height)
            shape.move(0.f, 1.f);
    }
}

RectangleShape AgressiveEnemy::getShape() const
{
    return shape;
}