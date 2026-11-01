#include "Game.h"


GameEngine Game::createInitialEngine()
{
    float tileSize = 32.0f;
    int mapWidth = 24;
    int mapHeight = 18; 

    GameMap map(mapWidth, mapHeight, tileSize);
    std::vector<Wall> walls;

    walls.push_back(Wall(5, 5, tileSize));
    walls.push_back(Wall(5, 6, tileSize));
    walls.push_back(Wall(6, 5, tileSize));

    
    walls.push_back(Wall(18, 12, tileSize));
    walls.push_back(Wall(18, 13, tileSize));
    walls.push_back(Wall(17, 12, tileSize));

    
    walls.push_back(Wall(12, 8, tileSize));
    walls.push_back(Wall(12, 9, tileSize));

    auto player = std::make_unique<PlayerTank>(Vector2D(96.0f, 96.0f), 130.0f, 1000);

    std::vector<std::unique_ptr<BotTank>> bots;
    bots.push_back(std::make_unique<BotTank>(Vector2D(600.0f, 160.0f), 80.0f, 50));
    bots.push_back(std::make_unique<BotTank>(Vector2D(630.0f, 400.0f), 80.0f, 50));

    return GameEngine(std::move(map), std::move(player), std::move(bots), std::move(walls));
}

Game::Game()
    : window(sf::VideoMode({ 768, 576 }), "2D Tank Game"), engine(createInitialEngine()), renderer(window)
{
    window.setFramerateLimit(144);
}



void Game::run()
{
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        if (dt > 0.1f) dt = 0.1f;

        processEvents();
        update(dt);
        render();
    }
}


void Game::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}


void Game::update(float dt)
{
    if (!engine.isGameOver())
    {
        engine.update(dt, readInput());
    }
}

InputState Game::readInput()
{
    InputState input;
    input.forward = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W);
    input.turnRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D);
    input.turnLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A);
    input.fire = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space);
    
    return input;
}

void Game::render()
{
    renderer.render(engine);
}