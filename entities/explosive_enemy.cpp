#include "./headers/explosive_enemy.h"

ExplosiveEnemy::ExplosiveEnemy(Vector2f position)
    : speed(EXPLOSIVE_ENEMY_START_SPEED), health(EXPLOSIVE_ENEMY_START_HEALTH), dead(false), explosionRadius(EXPLOSIVE_ENEMY_START_EXPLOSION_RADIUS)
{
    shape.setSize(EXPLOSIVE_ENEMY_START_SIZE);
    shape.setFillColor(EXPLOSIVE_ENEMY_START_COLOR);
    shape.setPosition(position);

    explosion.setRadius(explosionRadius);
}

void ExplosiveEnemy::update(Time deltaTime, Vector2f playerPosition, Vector2f basePosition, vector<Bullet> &enemyBullets)
{
    Vector2f target = (hypot(playerPosition.x - shape.getPosition().x, playerPosition.y - shape.getPosition().y) <
                       hypot(basePosition.x - shape.getPosition().x, basePosition.y - shape.getPosition().y))
                          ? playerPosition
                          : basePosition;
    Vector2f direction = target - shape.getPosition();
    moveTowards(deltaTime, direction);
}

void ExplosiveEnemy::moveTowards(Time deltaTime, Vector2f &direction)
{
    float distanceToTarget = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distanceToTarget > 20.f)
    {
        direction /= distanceToTarget;
        shape.move(direction * speed * deltaTime.asSeconds());
    }
}

void ExplosiveEnemy::draw(RenderWindow &window) const
{
    window.draw(shape);
}

bool ExplosiveEnemy::isDead() const
{
    return dead;
}

void ExplosiveEnemy::takeDamage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        dead = true;
    }
}

void ExplosiveEnemy::resolveCollision(const RectangleShape &otherShape)
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

void ExplosiveEnemy::explode(Player &player, Base &base, RenderWindow &window)
{
    int explosionDamage = 50;
    Vector2f explosionCenter = this->shape.getPosition();
    Vector2f playerPosition = player.getPosition();
    Vector2f basePosition = base.getPosition();

    float left = explosionCenter.x - explosionRadius;
    float right = explosionCenter.x + explosionRadius;
    float top = explosionCenter.y - explosionRadius;
    float bottom = explosionCenter.y + explosionRadius;

    if (playerPosition.x >= left && playerPosition.x <= right &&
        playerPosition.y >= top && playerPosition.y <= bottom)
    {
        player.takeDamage(explosionDamage);
    }

    if (basePosition.x >= left && basePosition.x <= right &&
        basePosition.y >= top && basePosition.y <= bottom)
    {
        base.takeDamage(explosionDamage);
    }
    drawExplosion(window);
}

void ExplosiveEnemy::drawExplosion(RenderWindow &window)
{
    explosion.setRadius(explosionRadius);
    explosion.setPosition(shape.getPosition() + Vector2f(25, 25));
    explosion.setOrigin(explosionRadius, explosionRadius);
    explosion.setFillColor(Color(255, 0, 0, 128));
    window.draw(explosion);
}

RectangleShape ExplosiveEnemy::getShape() const
{
    return shape;
}