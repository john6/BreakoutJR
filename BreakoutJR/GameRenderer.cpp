#include "GameRenderer.h"



GameRenderer::GameRenderer(sf::Vector2f screenDimensions) {

}


GameRenderer::~GameRenderer()
{
}

void Render(float elapsedMilliseconds) {

}

sf::RectangleShape GameRenderer::CreateDrawableRect(Rect rect) {
	sf::RectangleShape drawable;
	drawable.setPosition(rect.GetPosition());
	drawable.setSize(sf::Vector2f(rect.GetWidth(), rect.GetHeight()));
	drawable.setRotation(rect.GetRotation());
	drawable.setFillColor(sf::Color::White);
	return drawable;
}