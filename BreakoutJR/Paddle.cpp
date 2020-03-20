#include "Paddle.h"

Paddle::Paddle(float positionX, float positionY, float width, float height, float rotation) 
	: Rect{positionX, positionY, width, height, rotation}
{}

Paddle::~Paddle()
{
}
