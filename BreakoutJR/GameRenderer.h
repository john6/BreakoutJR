#pragma once
#include <SFML/Graphics.hpp>
class GameRenderer
{
public:
	GameRenderer(sf::Vector2f screenDimensions);
	~GameRenderer();

	static void Render(float elapsedMilliseconds);
};