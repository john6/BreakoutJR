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
	float m_start_rotation; //in degrees
	float m_continuous_rotation; //in degrees
	float m_currAngle;
	bool m_isDeath;

	float DegrToRad(float dAngle);

public:
	Rect(float positionX, float positionY, float width, float height, float startRot = 0.0f, float continuousRot = 0.0f, bool isDeath = false);
	Rect() = default;
	~Rect();

	sf::Vector2f GetPosition();
	std::vector<sf::Vector2f> GetPoints();
	float GetWidth();
	float GetHeight();
	float GetCurrAngle();
	float GetContinuousRotation();
	void SetPosition(sf::Vector2f origin);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetRotation(float rotation);
	bool IsDeath();
};
