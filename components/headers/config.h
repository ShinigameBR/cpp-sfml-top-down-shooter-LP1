#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Game
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int FPS = 60;
const float SPAWNTIMERCOOLDOWN = 1.f;
const float SLOW_ENEMY_SPAWN_CHANCE = 0.7f;
const float AGRESSIVE_ENEMY_SPAWN_CHANCE = 0.15f;
const float SHOOTER_ENEMY_SPAWN_CHANCE = 0.1f;
const float EXPLOSIVE_ENEMY_SPAWN_CHANCE = 0.05f;
const int NUMBER_OF_WAVES = 5;
const int MAX_ENEMIES_IN_START_WAVE = 20;
const float ENEMIES_INCREASE_BY_WAVE = 1.5f;

// Player
const int PLAYER_START_HEALTH = 100;
const float PLAYER_START_SPEED = 200.0f;
const int PLAYER_START_AMMO = 200;
const Time PLAYER_START_SHOOT_COOLDOWN = seconds(0.2f);
const Vector2f PLAYER_START_SIZE = Vector2f(60, 60);
const Color PLAYER_START_COLOR = Color::Blue;

// Player
const int BASE_START_HEALTH = 1000;
const Vector2f BASE_START_SIZE = Vector2f(80, 80);
const Color BASE_START_COLOR = Color::Cyan;

// SLOW ENEMY
const int SLOW_ENEMY_START_HEALTH = 3;
const float SLOW_ENEMY_START_SPEED = 50.0f;
const Vector2f SLOW_ENEMY_START_SIZE = Vector2f(40, 40);
const Color SLOW_ENEMY_START_COLOR = Color::Green;

// AGRESSIVE ENEMY
const int AGRESSIVE_ENEMY_START_HEALTH = 1;
const float AGRESSIVE_ENEMY_START_SPEED = 150.0f;
const Vector2f AGRESSIVE_ENEMY_START_SIZE = Vector2f(40, 40);
const Color AGRESSIVE_ENEMY_START_COLOR = Color::Green;

// SHOOTER ENEMY
const int SHOOTER_ENEMY_START_HEALTH = 6;
const float SHOOTER_ENEMY_START_SPEED = 70.0f;
const float SHOOTER_ENEMY_START_RANGE = 200.0f;
const Vector2f SHOOTER_ENEMY_START_SIZE = Vector2f(40, 40);
const Color SHOOTER_ENEMY_START_COLOR = Color::Magenta;

// EXPLOSIVE ENEMY
const int EXPLOSIVE_ENEMY_START_HEALTH = 1;
const float EXPLOSIVE_ENEMY_START_SPEED = 150.0f;
const float EXPLOSIVE_ENEMY_START_EXPLOSION_RADIUS = 100.0f;
const Vector2f EXPLOSIVE_ENEMY_START_SIZE = Vector2f(40, 40);
const Color EXPLOSIVE_ENEMY_START_COLOR = Color::Yellow;

#endif