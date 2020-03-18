#include "Court.h"


Court::Court(sf::RectangleShape dimensions)
{
	m_dimensions = dimensions;
	m_dimensions.setFillColor(sf::Color::Black);
	m_dimensions.setOutlineThickness(15.0f);
	m_dimensions.setOutlineColor(sf::Color::White);
	m_dimensions.setPosition(50, 50);
}

Court::~Court()
{
}

sf::RectangleShape Court::GetDimensions() {
	return m_dimensions;
}
