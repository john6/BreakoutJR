#include "CollisionHandler.h"

sf::Vector2f CollisionHandler::CalculateBounceDir(sf::Vector2f ballDir, sf::Vector2f surfaceDir) {
	//verticle vector => (0,1) , (0,-1)
	//horizontal vector => (1,0) , (-1,0)
	//Get surface normal
	sf::Vector2f surfNorm1(-surfaceDir.y, surfaceDir.x);
	sf::Vector2f surfNorm2(surfaceDir.y, -surfaceDir.x);
	return sf::Vector2f(0.0f, 0.0f);
}

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
}

sf::Vector2f CollisionHandler::DetectBallCollision(sf::CircleShape ball, sf::Vector2f ballVel, sf::RectangleShape rectSize, sf::Vector2f rectPos, bool verticle) {
	sf::Vector2f rectCenter((rectPos.x + (rectSize.getSize().x / 2)), rectPos.y + (rectSize.getSize().y / 2));
	float distX = abs(ball.getPosition().x - rectCenter.x);
	float distY = abs(ball.getPosition().y - rectCenter.y);
	float shapeWidthX = abs(ball.getRadius() + (rectSize.getSize().x / 2));
	float shapeHeightY = abs(ball.getRadius() + (rectSize.getSize().y / 2));
	if ((shapeWidthX > distX) && (shapeHeightY > distY)) {
		if (verticle) {
			return sf::Vector2f(-ballVel.x, ballVel.y);
		}
		else {
			return sf::Vector2f(ballVel.x, -ballVel.y);
		}
	}
	else {
		return sf::Vector2f(0.0f, 0.0f);
	}
}
