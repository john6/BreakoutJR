#pragma once
#include "Rect.h"
#include <SFML/Graphics.hpp>

class Paddle : public Rect
{
private:

public:
	Paddle(float positionX, float positionY, float width, float height, float rotation = 0.0f);
	Paddle() = default;
	~Paddle();
};