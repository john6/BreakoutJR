#pragma once
#include "Rect.h"
class BreakObject :
	public Rect
{
public:
	BreakObject(float positionX, float positionY, float width, float height, float rotation = 0.0f);
	BreakObject();
	~BreakObject();
};

