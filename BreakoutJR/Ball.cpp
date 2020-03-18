#include "Ball.h"

Ball::Ball(sf::Vector2f startPos, float radius)
{
	m_ball.setRadius(radius);
	m_ball.setPosition(startPos);
	m_ball.setFillColor(sf::Color::White);
	m_velocity = sf::Vector2f(0,0);
}

Ball::~Ball()
{
}

sf::CircleShape Ball::GetBall() {
	return m_ball;
}

sf::Vector2f Ball::GetPosition() {
	return m_ball.getPosition();
}

sf::Vector2f Ball::GetVelocity() {
	return m_velocity;
}

void Ball::SetRadius(float pos) {
	m_ball.setRadius(pos);
}

void Ball::SetPosition(sf::Vector2f pos) {
	m_ball.setPosition(pos);
}

void Ball::SetVelocity(sf::Vector2f vel) {
	m_velocity = vel;
}
