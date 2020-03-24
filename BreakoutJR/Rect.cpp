#include "Rect.h"

Rect::Rect(float positionX, float positionY, float width, float height, float startRot, float continuousRot, bool isDeath)
	: m_position(sf::Vector2f(positionX, positionY)), m_width(width), m_height(height), m_currAngle(startRot),
	  m_start_rotation(startRot), m_continuous_rotation(continuousRot), m_isDeath(isDeath)
{
}

Rect::~Rect()
{
}

float Rect::DegrToRad(float dAngle) {
	return (dAngle * PI) / 180.0f;
}

std::vector<sf::Vector2f> Rect::GetPoints() {
	sf::Vector2f topLeftPoint = m_position;
	sf::Vector2f topRightPoint = sf::Vector2f(topLeftPoint.x + cos(DegrToRad(DEGREE_RIGHT + m_currAngle))*m_width, topLeftPoint.y + sin(DegrToRad(DEGREE_RIGHT + m_currAngle))*m_width);
	sf::Vector2f bottomLeftPoint = sf::Vector2f(topLeftPoint.x + cos(DegrToRad(DEGREE_DOWN + m_currAngle))*m_height, topLeftPoint.y + sin(DegrToRad(DEGREE_DOWN + m_currAngle))*m_height);
	sf::Vector2f bottomRightPoint = sf::Vector2f(bottomLeftPoint.x + cos(DegrToRad(DEGREE_RIGHT + m_currAngle))*m_width, bottomLeftPoint.y + sin(DegrToRad(DEGREE_RIGHT + m_currAngle))*m_width);
	std::vector<sf::Vector2f> returnVect{ topLeftPoint, topRightPoint, bottomLeftPoint, bottomRightPoint };
	return returnVect;
}

sf::Vector2f Rect::GetPosition() { return m_position; }
float Rect::GetWidth() { return m_width; }
float Rect::GetHeight() { return m_height; }
float Rect::GetCurrAngle() { return m_currAngle;  }
float Rect::GetContinuousRotation() { return m_continuous_rotation; }
void Rect::SetPosition(sf::Vector2f origin) { m_position = origin;  }
void Rect::SetWidth(float width) { m_width = width;  }
void Rect::SetHeight(float height) { m_height = height;  }
void Rect::SetRotation(float rotation) { m_currAngle = rotation;  }
bool Rect::IsDeath() { return m_isDeath; }
