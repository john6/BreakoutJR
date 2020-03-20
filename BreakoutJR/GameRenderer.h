#pragma once
#include <SFML/Graphics.hpp>
#include "Rect.h"

class GameRenderer
{
public:
	GameRenderer(sf::Vector2f screenDimensions);
	~GameRenderer();

	static void Render(float elapsedMilliseconds);

	static sf::RectangleShape CreateDrawableRect(Rect rect);
};