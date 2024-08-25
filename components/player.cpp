#include "./headers/player.h"

Player::Player(Vector2f position)
    : speed(PLAYER_START_SPEED), health(PLAYER_START_HEALTH), ammo(PLAYER_START_AMMO), shootCooldown(PLAYER_START_SHOOT_COOLDOWN)
{
    shape.setSize(PLAYER_START_SIZE);
    shape.setFillColor(PLAYER_START_COLOR);
    shape.setPosition(position);

    font.loadFromFile("./assets/fonts/dogica/OTF/dogicapixel.otf");
    ammoText.setFont(font);
    ammoText.setCharacterSize(8);
    ammoText.setFillColor(Color::White);
}

void Player::update(Time deltaTime, vector<Bullet> &bullets, RenderWindow &window)
{
    velocity = Vector2f(0, 0);

    if (Keyboard::isKeyPressed(Keyboard::W))
        velocity.y -= speed;
    if (Keyboard::isKeyPressed(Keyboard::S))
        velocity.y += speed;
    if (Keyboard::isKeyPressed(Keyboard::A))
        velocity.x -= speed;
    if (Keyboard::isKeyPressed(Keyboard::D))
        velocity.x += speed;
    if (velocity == Vector2f(0, 0) && Mouse::isButtonPressed(Mouse::Right))
    {
        Vector2f direction = window.mapPixelToCoords(Mouse::getPosition(window)) - shape.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0)
        {
            direction /= length;
            velocity = direction * speed;
        }
    }

    shape.move(velocity * deltaTime.asSeconds());
    ammoText.setPosition(shape.getPosition().x, shape.getPosition().y + shape.getSize().y / 2.0f);
    ammoText.setString("Ammo: " + std::to_string(ammo));

    if (shootCooldown <= Time::Zero && Mouse::isButtonPressed(Mouse::Left) && ammo > 0)
    {
        shoot(bullets, window);
        shootCooldown = seconds(0.2f);
    }

    if (shootCooldown > Time::Zero)
    {
        shootCooldown -= deltaTime;
    }
}

void Player::shoot(vector<Bullet> &bullets, RenderWindow &window)
{
    Vector2f playerPos = shape.getPosition();
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    Vector2f direction = Vector2f(mousePos) - playerPos;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
    {
        direction /= length;
    }
    bullets.push_back(Bullet(playerPos + Vector2f(20, 20), direction));
    ammo--;
}

void Player::draw(RenderWindow &window)
{
    window.draw(shape);
    window.draw(ammoText);
}

void Player::takeDamage(int amount)
{
    health -= amount;
}

void Player::reloadAmmo(int amount)
{
    ammo += amount;
}

int Player::getHealth()
{
    return health;
}

int Player::getAmmo() const
{
    return ammo;
}

Vector2f Player::getPosition() const
{
    return shape.getPosition();
}

RectangleShape Player::getShape() const
{
    return shape;
}