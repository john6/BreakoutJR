#pragma once
#include <SFML/Graphics.hpp>

class Court
{
private:
	sf::RectangleShape m_dimensions;

public:
	Court(sf::RectangleShape dimensions);
	Court() = default;
	~Court();

	sf::RectangleShape GetDimensions();
};