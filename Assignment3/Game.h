#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameEngine.h"
#include "Renderer.h"

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

    static GameEngine createInitialEngine();
public:
    Game();
    void run();
};