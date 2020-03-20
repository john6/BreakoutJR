#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "GLOBAL_CONSTANTS.h"
#pragma once

class Rect
{
protected:
	sf::Vector2f m_position;
	sf::Vector2f m_center;
	float m_width;
	float m_height;
	float m_rotation; //in degrees

	float DegrToRad(float dAngle);

public:
	Rect(float positionX, float positionY, float width, float height, float rotation = 0.0f);
	Rect() = default;
	~Rect();

	sf::Vector2f GetPosition();
	std::vector<sf::Vector2f> GetPoints();
	float GetWidth();
	float GetHeight();
	float GetRotation();
	void SetPosition(sf::Vector2f origin);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetRotation(float rotation);
};
