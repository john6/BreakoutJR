#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
private:
	sf::RectangleShape m_size;
	sf::Vector2f m_position;

public:
	Paddle(sf::RectangleShape rect, sf::Vector2f position);
	Paddle() = default;
	~Paddle();

	sf::RectangleShape GetSize();
	sf::Vector2f GetPosition();

	void SetPosition(sf::Vector2f rectSet);
	void SetSize(sf::RectangleShape rectSet);
};