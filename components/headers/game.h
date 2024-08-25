#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "config.h"
#include "player.h"
#include "bullet.h"
#include "base.h"
#include "../../entities/headers/ammo_box.h"
#include "../../entities/headers/slow_enemy.h"
#include "../../entities/headers/shooter_enemy.h"
#include "../../entities/headers/agressive_enemy.h"
#include "../../entities/headers/explosive_enemy.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(Time deltaTime);
    void render();
    void handleGameOver(const std::string &message);
    void handleGameWin();

    void spawnEnemies(Time deltaTime);
    void checkCollisions();
    void removeInactiveEntities();

    RenderWindow window;
    Font font;
    View view;
    Clock clock;
    Time spawnTimer;

    Player player;
    RectangleShape playerHealthBar;
    Text playerHealthText;
    vector<Bullet> playerBullets;

    Base base;
    RectangleShape baseHealthBar;
    Text baseHealthText;

    vector<unique_ptr<Enemy>> enemies;
    vector<unique_ptr<AmmoBox>> ammoBoxes;
    vector<Bullet> enemyBullets;

    int currentWave;
    int maxEnemiesPerWave;
    int enemiesSpawnedInWave;
    int enemiesDefeatedInWave;
    Text currentWaveText;
};

#endif
