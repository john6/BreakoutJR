#pragma once
#include <SFML/Graphics.hpp>
#include "Rect.h"
#include <iostream>
#include <algorithm>

class CollisionHandler
{
private:
	static sf::Vector2f CalculateBounceDir(sf::Vector2f ballDir, sf::Vector2f surfaceDir);

public:
	CollisionHandler();
	~CollisionHandler();

	static float DegrToRad(float dAngle);

	static sf::Vector2f RotateVector(sf::Vector2f point, float rotationDegrees);

	static sf::Vector2f DetectBallCollision(sf::CircleShape ball, sf::Vector2f ballVel, sf::RectangleShape rectSize, sf::Vector2f rectPos, bool verticle);

	static bool DetectLineIntersection(sf::CircleShape ball, sf::Vector2f point1, sf::Vector2f point2);

	static float VectorLengthSqaured(sf::Vector2f point1, sf::Vector2f point2);

	static float DotProd(sf::Vector2f v1, sf::Vector2f v2);

	static float VectorDistance(sf::Vector2f point1, sf::Vector2f point2);

	static sf::Vector2f VectorAdd(sf::Vector2f v1, sf::Vector2f v2);

	static sf::Vector2f VectorSubtract(sf::Vector2f v1, sf::Vector2f v2);

	static bool DetectLineSegmentIntersection(sf::CircleShape ball, sf::Vector2f point1, sf::Vector2f point2);

	static float GetLineSegmentDist(sf::CircleShape ball, sf::Vector2f point1, sf::Vector2f point2);

	static sf::Vector2f BounceBall(sf::CircleShape ball, sf::Vector2f ballVel, Rect rect);

};

