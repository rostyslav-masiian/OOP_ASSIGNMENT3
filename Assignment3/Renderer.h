#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "GameEngine.h"

class Renderer
{
private:
    sf::RenderWindow& window;
    sf::Texture tankTexture;
    sf::Texture projTexture;
    sf::Font font;


    
    void renderHealthBar(const Tank& tank);
    void renderState(const GameEngine& engine);
public:
    Renderer(sf::RenderWindow& win) : window(win) 
    {
        if (!tankTexture.loadFromFile("assets/tank.png"))
        {
            throw std::runtime_error("Cannot load assets/tank.png");
        }
        if (!projTexture.loadFromFile("assets/proj.png"))
        {
            throw std::runtime_error("Cannot load assets/proj.png");
        }

        if (!font.openFromFile("C:/Windows/Fonts/impact.ttf"))
        {
            throw std::runtime_error("Cannot load font");
        }
    }

    
    void render(const GameEngine& engine);
};
