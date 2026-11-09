#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameEngine.h"
#include "Renderer.h"


class Command;
class Game
{
private:
    sf::RenderWindow window;
    GameEngine engine;
    Renderer renderer;
    sf::Clock clock;

    void processEvents();
    void update(float dt);
    void render();
    std::vector<std::unique_ptr<Command>> handleInput();
    static GameEngine createInitialEngine();
    void restart();
public:
    Game();
    void run();
};