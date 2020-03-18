#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class CollisionHandler
{
private:
	static sf::Vector2f CalculateBounceDir(sf::Vector2f ballDir, sf::Vector2f surfaceDir);

public:
	CollisionHandler();
	~CollisionHandler();

	static sf::Vector2f DetectBallCollision(sf::CircleShape ball, sf::Vector2f ballVel, sf::RectangleShape rectSize, sf::Vector2f rectPos, bool verticle);


};

