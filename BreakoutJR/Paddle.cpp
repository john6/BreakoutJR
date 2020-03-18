#include "Paddle.h"

Paddle::Paddle(sf::RectangleShape rect, sf::Vector2f position)
{
	m_size = rect;
	m_size.setFillColor(sf::Color::White);
	m_position = position;
}

Paddle::~Paddle()
{
}

sf::RectangleShape Paddle::GetSize() {
	return m_size;
}

sf::Vector2f Paddle::GetPosition() {
	return m_position;
}

void Paddle::SetPosition(sf::Vector2f position) {
	m_position = position;
}

void Paddle::SetSize(sf::RectangleShape size) {
	m_size = size;
}
