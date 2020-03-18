#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
private:
	sf::CircleShape m_ball;
	sf::Vector2f m_velocity;

public:
	Ball(sf::Vector2f startPos, float radius);
	Ball() = default;
	~Ball();


	sf::CircleShape GetBall();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();

	void SetRadius(float pos);
	void SetPosition(sf::Vector2f pos);
	void SetVelocity(sf::Vector2f vel);
};

