#include "GameRenderer.h"



GameRenderer::GameRenderer(sf::Vector2f screenDimensions) {

}


GameRenderer::~GameRenderer()
{
}

void Render(float elapsedMilliseconds) {

}

sf::RectangleShape GameRenderer::CreateDrawableRect(Rect rect, bool useNewCenter) {
	sf::RectangleShape drawable;
	drawable.setPosition(rect.GetPosition());
	if (useNewCenter) {
		drawable.setPosition(rect.GetPosition() + rect.GetCenterOffset());
	}
	if (useNewCenter) {
		drawable.setOrigin(rect.GetCenterOffset());
	}
	drawable.setSize(sf::Vector2f(rect.GetWidth(), rect.GetHeight()));
	drawable.setRotation(rect.GetCurrAngle());
	drawable.setFillColor(sf::Color::White);
	return drawable;
}