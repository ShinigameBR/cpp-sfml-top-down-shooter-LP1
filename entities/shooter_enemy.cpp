#include "./headers/shooter_enemy.h"

ShooterEnemy::ShooterEnemy(Vector2f position) : range(SHOOTER_ENEMY_START_RANGE), speed(SHOOTER_ENEMY_START_SPEED), health(SHOOTER_ENEMY_START_HEALTH), dead(false)
{
    shape.setSize(SHOOTER_ENEMY_START_SIZE);
    shape.setFillColor(SHOOTER_ENEMY_START_COLOR);
    shape.setPosition(position);
}

void ShooterEnemy::update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets)
{
    Vector2f target = (hypot(playerPosition.x - shape.getPosition().x, playerPosition.y - shape.getPosition().y) <
                       hypot(basePosition.x - shape.getPosition().x, basePosition.y - shape.getPosition().y))
                          ? playerPosition
                          : basePosition;
    Vector2f direction = target - shape.getPosition();

    moveTowards(deltaTime, direction);
    if (shootCooldown <= Time::Zero)
    {
        shoot(deltaTime, direction, enemyBullets);
        shootCooldown = seconds(1.5f);
    }
    else
    {
        shootCooldown -= deltaTime;
    }
}

void ShooterEnemy::moveTowards(Time deltaTime, Vector2f &direction)
{
    float distanceToTarget = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distanceToTarget != 0 && distanceToTarget > range)
    {
        direction /= distanceToTarget;
        shape.move(direction * speed * deltaTime.asSeconds());
    }
}

void ShooterEnemy::shoot(Time deltaTime, Vector2f &direction, vector<Bullet> &enemyBullets)
{
    float distanceToTarget = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distanceToTarget != 0 && distanceToTarget < range + 50.f)
    {
        direction /= distanceToTarget;
        enemyBullets.push_back(Bullet(shape.getPosition(), direction));
    }
}

void ShooterEnemy::draw(RenderWindow &window) const
{
    window.draw(shape);
}

bool ShooterEnemy::isDead() const
{
    return dead;
}

void ShooterEnemy::takeDamage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        dead = true;
    }
}

void ShooterEnemy::resolveCollision(const RectangleShape &otherShape)
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

RectangleShape ShooterEnemy::getShape() const
{
    return shape;
}