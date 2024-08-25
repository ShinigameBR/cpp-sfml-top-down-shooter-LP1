#include "./headers/game.h"

Game::Game()
    : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Base Defense Game", Style::Close),
      player(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50)),
      base(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)),
      view(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT))
{
    window.setFramerateLimit(FPS);
    srand(time(nullptr));

    font.loadFromFile("./assets/fonts/dogica/OTF/dogicapixel.otf");

    playerHealthBar.setFillColor(Color::Red);
    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(8);
    playerHealthText.setFillColor(Color::White);

    baseHealthBar.setFillColor(Color::Red);
    baseHealthText.setFont(font);
    baseHealthText.setCharacterSize(8);
    baseHealthText.setFillColor(Color::White);

    currentWave = 1;
    maxEnemiesPerWave = MAX_ENEMIES_IN_START_WAVE;
    enemiesSpawnedInWave = 0;
    enemiesDefeatedInWave = 0;

    currentWaveText.setFont(font);
    currentWaveText.setCharacterSize(8);
    currentWaveText.setFillColor(Color::White);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        Time deltaTime = clock.restart();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }
}

void Game::update(Time deltaTime)
{
    if (player.getHealth() <= 0)
    {
        handleGameOver("You lost!\n\n The player has died.");
        return;
    }

    if (base.getHealth() <= 0)
    {
        handleGameOver("You lost!\n\n The base was destroyed.");
        return;
    }

    if (currentWave == NUMBER_OF_WAVES && enemiesDefeatedInWave == enemiesSpawnedInWave)
    {
        handleGameWin();
    }

    spawnEnemies(deltaTime);
    player.update(deltaTime, playerBullets, window);

    for (auto &enemy : enemies)
    {
        enemy->update(deltaTime, player.getPosition(), base.getPosition(), enemyBullets);
    }

    for (auto &bullet : playerBullets)
    {
        bullet.update(deltaTime);
    }

    for (auto &bullet : enemyBullets)
    {
        bullet.update(deltaTime);
    }

    for (auto &ammoBox : ammoBoxes)
    {
        ammoBox->draw(window);
    }

    checkCollisions();
    removeInactiveEntities();

    view.setCenter(player.getPosition());
    window.setView(view);

    playerHealthBar.setPosition(player.getPosition().x,
                                player.getPosition().y - player.getShape().getGlobalBounds().height / 2 - .5f);

    baseHealthBar.setPosition(base.getPosition().x,
                              base.getPosition().y - base.getShape().getGlobalBounds().height / 2 - .5f);

    if (player.getHealth() >= 0)
    {
        playerHealthBar.setSize(Vector2f(.6f * player.getHealth(), 15.f));
        playerHealthText.setString(to_string(player.getHealth()) + " / " + to_string(PLAYER_START_HEALTH));
    }
    if (base.getHealth() >= 0)
    {
        baseHealthBar.setSize(Vector2f(.08f * base.getHealth(), 15.f));
        baseHealthText.setString(to_string(base.getHealth()) + " / " + to_string(BASE_START_HEALTH));
    }

    playerHealthText.setPosition(playerHealthBar.getPosition().x + playerHealthBar.getSize().x / 2 - playerHealthText.getGlobalBounds().width / 2,
                                 playerHealthBar.getPosition().y);

    baseHealthText.setPosition(baseHealthBar.getPosition().x + baseHealthBar.getSize().x / 2 - baseHealthText.getGlobalBounds().width / 2,
                               baseHealthBar.getPosition().y);

    currentWaveText.setString("Wave: " + std::to_string(currentWave));

    currentWaveText.setPosition(view.getCenter().x - view.getSize().x / 2 + 20.f, view.getCenter().y - view.getSize().y / 2 + 20.f);
}

void Game::render()
{
    window.clear();
    window.draw(playerHealthBar);
    window.draw(playerHealthText);
    window.draw(baseHealthBar);
    window.draw(baseHealthText);
    window.draw(currentWaveText);

    player.draw(window);
    base.draw(window);

    for (auto &enemy : enemies)
    {
        enemy->draw(window);
    }

    for (auto &bullet : playerBullets)
    {
        bullet.draw(window);
    }

    for (auto &bullet : enemyBullets)
    {
        bullet.draw(window);
    }

    for (auto &ammoBox : ammoBoxes)
    {
        ammoBox->draw(window);
    }

    window.display();
}

void Game::spawnEnemies(Time deltaTime)
{
    spawnTimer += deltaTime;

    if (spawnTimer.asSeconds() >= SPAWNTIMERCOOLDOWN && enemiesSpawnedInWave < maxEnemiesPerWave)
    {
        float enemyX = static_cast<float>(rand() % ((3000 - WINDOW_WIDTH + 1) + WINDOW_WIDTH));
        float enemyY = static_cast<float>(rand() % ((3000 - WINDOW_HEIGHT + 1) + WINDOW_HEIGHT));
        float type = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        if (type < SLOW_ENEMY_SPAWN_CHANCE)
        {
            enemies.push_back(make_unique<SlowEnemy>(Vector2f(enemyX, enemyY)));
        }
        else if (type < SLOW_ENEMY_SPAWN_CHANCE + AGRESSIVE_ENEMY_SPAWN_CHANCE)
        {
            enemies.push_back(make_unique<AgressiveEnemy>(Vector2f(enemyX, enemyY)));
        }
        else if (type < SLOW_ENEMY_SPAWN_CHANCE + AGRESSIVE_ENEMY_SPAWN_CHANCE + SHOOTER_ENEMY_SPAWN_CHANCE)
        {
            enemies.push_back(make_unique<ShooterEnemy>(Vector2f(enemyX, enemyY)));
        }
        else if (type < SLOW_ENEMY_SPAWN_CHANCE + AGRESSIVE_ENEMY_SPAWN_CHANCE + SHOOTER_ENEMY_SPAWN_CHANCE + EXPLOSIVE_ENEMY_SPAWN_CHANCE)
        {
            enemies.push_back(make_unique<ExplosiveEnemy>(Vector2f(enemyX, enemyY)));
        }

        enemiesSpawnedInWave++;
        spawnTimer = Time::Zero;
    }
    if (enemiesSpawnedInWave >= maxEnemiesPerWave && enemiesDefeatedInWave >= maxEnemiesPerWave)
    {
        if (currentWave <= NUMBER_OF_WAVES)
        {
            currentWave++;
            maxEnemiesPerWave = static_cast<int>(floor(maxEnemiesPerWave * ENEMIES_INCREASE_BY_WAVE));
        }

        enemiesSpawnedInWave = 0;
        enemiesDefeatedInWave = 0;
    }
}

void Game::checkCollisions()
{
    for (auto &bullet : playerBullets)
    {
        for (auto &enemy : enemies)
        {
            if (bullet.getShape().getGlobalBounds().intersects(enemy->getShape().getGlobalBounds()))
            {
                enemy->takeDamage(1);
                bullet.setActive(false);
            }
        }
    }

    for (auto &ammoBox : ammoBoxes)
    {
        ammoBox->resolveCollision(player);
    }

    for (auto &enemy : enemies)
    {
        enemy->resolveCollision(player.getShape());
        enemy->resolveCollision(base.getShape());

        for (auto &otherEnemy : enemies)
        {
            if (enemy != otherEnemy)
            {
                enemy->resolveCollision(otherEnemy->getShape());
            }
        }

        if (enemy->getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
        {
            player.takeDamage(1);
        }
        if (enemy->getShape().getGlobalBounds().intersects(base.getShape().getGlobalBounds()))
        {
            base.takeDamage(1);
        }
    }

    for (auto &bullet : enemyBullets)
    {
        if (bullet.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
        {
            player.takeDamage(1);
            bullet.setActive(false);
        }
        if (bullet.getShape().getGlobalBounds().intersects(base.getShape().getGlobalBounds()))
        {
            base.takeDamage(1);
            bullet.setActive(false);
        }
    }
}

void Game::removeInactiveEntities()
{
    playerBullets.erase(remove_if(playerBullets.begin(), playerBullets.end(), [](const Bullet &b)
                                  { return !b.isActive(); }),
                        playerBullets.end());

    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(), [](const Bullet &b)
                                 { return !b.isActive(); }),
                       enemyBullets.end());

    for (auto it = enemies.begin(); it != enemies.end();)
    {
        if ((*it)->isDead())
        {
            ExplosiveEnemy *explosiveEnemy = dynamic_cast<ExplosiveEnemy *>(it->get());
            ShooterEnemy *shooterEnemy = dynamic_cast<ShooterEnemy *>(it->get());
            if (explosiveEnemy)
            {
                explosiveEnemy->explode(player, base, window);
                window.display();
            }
            if (shooterEnemy)
            {
                ammoBoxes.push_back(make_unique<AmmoBox>(shooterEnemy->getShape().getPosition()));
            }
            it = enemies.erase(it);
            enemiesDefeatedInWave++;
        }
        else
        {
            ++it;
        }
    }

    ammoBoxes.erase(
        std::remove_if(ammoBoxes.begin(), ammoBoxes.end(), [](const std::unique_ptr<AmmoBox> &a)
                       { return a->isCollected(); }),
        ammoBoxes.end());
}

void Game::handleGameOver(const std::string &message)
{
    window.clear();
    Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(50);
    text.setFillColor(Color::Red);
    text.setStyle(Text::Bold);
    text.setPosition(player.getPosition().x - (WINDOW_WIDTH / 2) + 30.f, player.getPosition().y);

    window.draw(text);
    window.display();
    sleep(seconds(3));
    window.close();
}

void Game::handleGameWin()
{
    window.clear();
    Text text;
    text.setFont(font);
    text.setString("Congratulations!\n\n You survived.");
    text.setCharacterSize(50);
    text.setFillColor(Color::Green);
    text.setStyle(Text::Bold);
    text.setPosition(player.getPosition().x - (WINDOW_WIDTH / 2) + 30.f, player.getPosition().y);

    window.draw(text);
    window.display();
    sleep(seconds(3));
    window.close();
}