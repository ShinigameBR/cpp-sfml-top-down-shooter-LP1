#include "./headers/slow_enemy.h"

SlowEnemy::SlowEnemy(Vector2f position) : speed(SLOW_ENEMY_START_SPEED), health(SLOW_ENEMY_START_HEALTH), dead(false)
{
    shape.setSize(SLOW_ENEMY_START_SIZE);
    shape.setFillColor(SLOW_ENEMY_START_COLOR);
    shape.setPosition(position);
}

void SlowEnemy::update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets)
{
    Vector2f target = (hypot(playerPosition.x - shape.getPosition().x, playerPosition.y - shape.getPosition().y) <
                       hypot(basePosition.x - shape.getPosition().x, basePosition.y - shape.getPosition().y))
                          ? playerPosition
                          : basePosition;

    Vector2f direction = target - shape.getPosition();
    moveTowards(deltaTime, direction);
}

void SlowEnemy::moveTowards(Time deltaTime, Vector2f &direction)
{
    float distanceToTarget = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distanceToTarget > 25.f)
    {
        direction /= distanceToTarget;
        shape.move(direction * speed * deltaTime.asSeconds());
    }
}

void SlowEnemy::draw(RenderWindow &window) const
{
    window.draw(shape);
}

bool SlowEnemy::isDead() const
{
    return dead;
}

void SlowEnemy::takeDamage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        dead = true;
    }
}

void SlowEnemy::resolveCollision(const RectangleShape &otherShape)
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
    // if (enemyBounds.intersects(otherBounds))
    // {
    //     float deltaX = (enemyBounds.left + enemyBounds.width / 2) - (otherBounds.left + otherBounds.width / 2);
    //     float deltaY = (enemyBounds.top + enemyBounds.height / 2) - (otherBounds.top + otherBounds.height / 2);
    //     float intersectX = abs(deltaX) - (enemyBounds.width / 2 + otherBounds.width / 2);
    //     float intersectY = abs(deltaY) - (enemyBounds.height / 2 + otherBounds.height / 2);

    //     if (intersectX < intersectY)
    //     {
    //         if (deltaX > 0)
    //             shape.move(intersectX, 0.f);
    //         else
    //             shape.move(-intersectX, 0.f);
    //     }
    //     else
    //     {
    //         if (deltaY > 0)
    //             shape.move(0.f, intersectY);
    //         else
    //             shape.move(0.f, -intersectY);
    //     }
    // }
}

RectangleShape SlowEnemy::getShape() const
{
    return shape;
}