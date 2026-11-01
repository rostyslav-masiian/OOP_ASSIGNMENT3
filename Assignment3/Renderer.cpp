#include "Renderer.h"
#include <iostream>
#include "Color.h"
static sf::Color toSf(const Color& c)
{
    return sf::Color(c.r, c.g, c.b, c.a);
}

void Renderer::render(const GameEngine& engine)
{
    window.clear(sf::Color::Black);

    const GameMap& map = engine.getMap();
    for (int y = 0; y < map.getHeight(); y++)
    {
        for (int x = 0; x < map.getWidth(); x++)
        {
            sf::RectangleShape tileShape(sf::Vector2f(map.getTileSize(), map.getTileSize()));
            tileShape.setPosition(sf::Vector2f(x * map.getTileSize(), y * map.getTileSize()));
            if (map.getTile(x, y) == TileType::Mud)
            {
                tileShape.setFillColor(toSf(Palette::Mud));
            }
            else
            {
                tileShape.setFillColor(toSf(Palette::Ground));
            }
            tileShape.setOutlineThickness(1.0f);
            tileShape.setOutlineColor(toSf(Palette::Outline));
            window.draw(tileShape);
        }
    }

    for (const auto& wall : engine.getWalls())
    {
        if (!wall.isDestroyed())
        {
            sf::RectangleShape wallShape(sf::Vector2f(wall.getCollider().getWidth(), wall.getCollider().getHeight()));
            wallShape.setPosition(sf::Vector2f(wall.getCollider().getPosition().getX(), wall.getCollider().getPosition().getY()));
            wallShape.setFillColor(toSf(Palette::Wall));
            wallShape.setOutlineThickness(1.0f);
            wallShape.setOutlineColor(toSf(Palette::Outline));
            window.draw(wallShape);
        }
    }

    const PlayerTank* playerTank = engine.getPlayer();
    if (playerTank && playerTank->isAlive())
    {
        sf::Sprite sprite(tankTexture);
        sf::Vector2u textureSize = tankTexture.getSize();
        float size = static_cast<float>(playerTank->getSize());
        
        sprite.setOrigin(sf::Vector2f(textureSize.x / 2.0f, textureSize.y / 2.0f));
        sprite.setScale(sf::Vector2f(size / textureSize.x, size / textureSize.y));

        sprite.setPosition(sf::Vector2f(playerTank->getCenter().getX(), playerTank->getCenter().getY()));

        Vector2D dir = playerTank->getDirection();
        if (dir.getX() != 0.0f || dir.getY() != 0.0f)
        {
            sprite.setRotation(sf::radians(std::atan2(dir.getY(), dir.getX())) + sf::degrees(90));
        }
        renderHealthBar(*playerTank);
        window.draw(sprite);
    }

    for (const auto& bot : engine.getBots())
    {
        if (bot && bot->isAlive())
        {
            sf::Sprite sprite(tankTexture);
            sf::Vector2u textureSize = tankTexture.getSize();
            float size = static_cast<float>(bot->getSize());

            sprite.setOrigin(sf::Vector2f(textureSize.x / 2.0f, textureSize.y / 2.0f));
            sprite.setScale(sf::Vector2f(size / textureSize.x, size / textureSize.y));

            sprite.setPosition(sf::Vector2f(bot->getCenter().getX(), bot->getCenter().getY()));

            Vector2D dir = bot->getDirection();
            if (dir.getX() != 0.0f || dir.getY() != 0.0f)
            {
                sprite.setRotation(sf::radians(std::atan2(dir.getY(), dir.getX())) + sf::degrees(90));
            }

            
            renderHealthBar(*bot);
            window.draw(sprite);
        }
    }

    for (const auto& proj : engine.getProjectiles())
    {
        if (proj.isAlive())
        {
            sf::Sprite sprite(projTexture);
            sf::Vector2u textureSize = projTexture.getSize();
            float diameter = static_cast<float>(proj.getRadius()) * 2.0f;
            sprite.setOrigin(sf::Vector2f(textureSize.x / 2.0f, textureSize.y / 2.0f));
            sprite.setScale(sf::Vector2f(diameter / textureSize.x, diameter / textureSize.y));

            sprite.setPosition(sf::Vector2f(proj.getCenter().getX(), proj.getCenter().getY()));

            Vector2D dir = proj.getDirection();
            if (dir.getX() != 0.0f || dir.getY() != 0.0f)
            {
                sprite.setRotation(sf::radians(std::atan2(dir.getY(), dir.getX())) + sf::degrees(90));
            }

            
            window.draw(sprite);
        }
    }
    if (engine.isGameOver())
    {
        renderWin(engine.didPlayerWin());
    }
    

    window.display();
}

void Renderer::renderWin(const bool didPlayerWin)
{
    sf::Font font;
    if (font.openFromFile("C:/Windows/Fonts/impact.ttf"))
    {
        sf::Text text(font);
        if (didPlayerWin)
        {
            text.setString("!!!PLAYER WON!!!");
            text.setFillColor(sf::Color::Blue);
        }
        else
        {
            text.setString("!!!PLAYER LOST!!!");
            text.setFillColor(sf::Color::Yellow);
        }
        text.setCharacterSize(48);
        text.setStyle(sf::Text::Bold);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(sf::Vector2f{ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
        text.setPosition(sf::Vector2f{ window.getSize().x / 2.0f, window.getSize().y / 2.0f });

        window.draw(text);
    }

}

void Renderer::renderHealthBar(const Tank& tank)
{
    float barWidth = static_cast<float>(tank.getSize());
    const float barHeight = 5.0f;
    const float offsetAbove = 8.0f;

    float ratio = static_cast<float>(tank.getHealth()) / static_cast<float>(tank.getMaxHealth());
    ratio = std::clamp(ratio, 0.0f, 1.0f);

    float halfSize = static_cast<float>(tank.getSize()) / 2.0f;
    float x = tank.getCenter().getX() - barWidth / 2.0f;
    float y = tank.getCenter().getY() - halfSize - offsetAbove;

    sf::RectangleShape backBar(sf::Vector2f(barWidth, barHeight));
    backBar.setPosition(sf::Vector2f(x, y));
    backBar.setFillColor(sf::Color(40, 40 ,40));
    
    window.draw(backBar);


    sf::RectangleShape fillBar(sf::Vector2f(barWidth * ratio, barHeight));
    fillBar.setPosition(sf::Vector2f(x, y));
    fillBar.setFillColor(sf::Color(static_cast<uint8_t>(255 * (1.0f - ratio)), static_cast<uint8_t>(255 * ratio), 0));
    
    window.draw(fillBar);
}
