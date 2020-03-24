#pragma once
#include <vector>
#include "Rect.h"
#include "BreakObject.h"

class Level
{
private:
	int m_lvl_num;
	std::vector<Rect> m_levelRects;
	std::vector<Rect> m_breakObjects;

	//LEVEL ONE VALUES
	const int LVL_ONE_BREAKABLE_ROW_NUM = 2;
	const int LVL_ONE_BREAKABLE_COL_NUM = 8;
	const float LVL_ONE_OBSTACLE_ROT_SPEED = 0.5f;

	//LEVEL TWO VALUES
	const int LVL_TWO_BREAKABLE_ROW_NUM = 3;
	const int LVL_TWO_BREAKABLE_COL_NUM = 8;
	const float LVL_TWO_OBSTACLE_ROT_SPEED = 0.9f;

	//LEVEL THREE VALUES
	const int LVL_THREE_BREAKABLE_ROW_NUM = 3;
	const int LVL_THREE_BREAKABLE_COL_NUM = 8;
	const float LVL_THREE_OBSTACLE_ROT_SPEED = 1.7f;

	void CreateLvlOne();
	void CreateLvlTwo();
	void CreateLvlThree();

public:
	Level(int levelNum);
	~Level();

	std::vector<Rect> GetLvlRects();
	std::vector<Rect> GetBreakRects();
	int GetLvlNum();
};

