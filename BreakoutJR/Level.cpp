#include "Level.h"



Level::Level(int levelNum) :
	m_lvl_num{ levelNum }
{
	switch (levelNum) {
	case 0: {
		CreateLvlOne();
		break;
		}
	case 1: {
		CreateLvlTwo();
		break;
	}
	case 2: {
		CreateLvlThree();
		break;
	}
	}
}


Level::~Level()
{
}

void Level::CreateLvlOne() {
	int m_break_objects_remaining = LVL_ONE_BREAKABLE_COL_NUM * LVL_ONE_BREAKABLE_ROW_NUM;
	Rect m_upperWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN, COURT_WIDTH, WALL_THICKNESS);
	Rect m_lowerWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN + COURT_HEIGHT, COURT_WIDTH, WALL_THICKNESS, 0.0f, 0.0f, true);
	Rect m_left_wall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN, WALL_THICKNESS, COURT_HEIGHT);
	Rect m_right_wall = Rect(HORIZONTAL_MARGIN + COURT_WIDTH, VERTICLE_MARGIN, WALL_THICKNESS, COURT_HEIGHT);
	Rect m_left_corner_rect = Rect(30, 210, 220, 10, -45.0f);
	Rect m_right_corner_rect = Rect(595, 50, 200, 10, 45.0f);
	Rect m_rotating_rect_left = Rect(HORIZONTAL_MARGIN + 100, (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_ONE_OBSTACLE_ROT_SPEED);
	Rect m_rotating_rect_center = Rect((COURT_WIDTH / 2) + HORIZONTAL_MARGIN, (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 75, 10, 0.0f, -LVL_ONE_OBSTACLE_ROT_SPEED);
	Rect m_rotating_rect_right = Rect(COURT_WIDTH - 100, (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_ONE_OBSTACLE_ROT_SPEED);

	m_levelRects.push_back(m_upperWall);
	m_levelRects.push_back(m_lowerWall);
	m_levelRects.push_back(m_left_wall);
	m_levelRects.push_back(m_right_wall);
	m_levelRects.push_back(m_left_corner_rect);
	m_levelRects.push_back(m_right_corner_rect);
	m_levelRects.push_back(m_rotating_rect_left);
	m_levelRects.push_back(m_rotating_rect_center);
	m_levelRects.push_back(m_rotating_rect_right);

	for (int i = 0; i < m_break_objects_remaining; ++i) {
		Rect breakObject = BreakObject(80.0f + ((float)(i % LVL_ONE_BREAKABLE_COL_NUM) * 80.0f),
			210.0f + ((float)(i / LVL_ONE_BREAKABLE_COL_NUM) * 100.0f), 50.0f, 50.0f, 0.0f);
		m_breakObjects.push_back(breakObject);
	}
}

void Level::CreateLvlTwo() {
	int m_break_objects_remaining = LVL_TWO_BREAKABLE_COL_NUM * LVL_TWO_BREAKABLE_ROW_NUM;
	Rect m_upperWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN * 2, COURT_WIDTH, WALL_THICKNESS);
	Rect m_lowerWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN + COURT_HEIGHT, COURT_WIDTH + WALL_THICKNESS, WALL_THICKNESS, 0.0f, 0.0f, true);
	Rect m_left_wall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN * 2, WALL_THICKNESS, COURT_HEIGHT - WALL_THICKNESS);
	Rect m_right_wall = Rect(HORIZONTAL_MARGIN + COURT_WIDTH, VERTICLE_MARGIN * 2, WALL_THICKNESS, COURT_HEIGHT - WALL_THICKNESS);
	Rect m_left_corner_rect = Rect(30, 210 + VERTICLE_MARGIN, 220, 10, -45.0f);
	Rect m_right_corner_rect = Rect(595, 50 + VERTICLE_MARGIN, 200, 10, 45.0f);
	Rect m_rotating_rect_left_up = Rect(HORIZONTAL_MARGIN + 100, (COURT_HEIGHT / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_TWO_OBSTACLE_ROT_SPEED);
	Rect m_rotating_rect_right_up = Rect(COURT_WIDTH - 100, (COURT_HEIGHT / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_TWO_OBSTACLE_ROT_SPEED);
	Rect m_rotating_rect_left_down = Rect(HORIZONTAL_MARGIN + 100, (COURT_HEIGHT * 2 / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_TWO_OBSTACLE_ROT_SPEED);
	Rect m_rect_center_down = Rect((COURT_WIDTH / 2) + HORIZONTAL_MARGIN + (WALL_THICKNESS/2), (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 100, 100, 45.0f);
	Rect m_rotating_rect_right_down = Rect(COURT_WIDTH - 100, (COURT_HEIGHT * 2 / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_TWO_OBSTACLE_ROT_SPEED);

	m_levelRects.push_back(m_upperWall);
	m_levelRects.push_back(m_lowerWall);
	m_levelRects.push_back(m_left_wall);
	m_levelRects.push_back(m_right_wall);
	m_levelRects.push_back(m_left_corner_rect);
	m_levelRects.push_back(m_right_corner_rect);
	m_levelRects.push_back(m_rotating_rect_left_up);
	m_levelRects.push_back(m_rotating_rect_right_up);
	m_levelRects.push_back(m_rotating_rect_left_down);
	m_levelRects.push_back(m_rect_center_down);
	m_levelRects.push_back(m_rotating_rect_right_down);

	for (int i = 0; i < m_break_objects_remaining; ++i) {
		Rect breakObject = BreakObject(80.0f + ((float)(i % LVL_ONE_BREAKABLE_COL_NUM) * 80.0f),
			210.0f + ((float)(i / LVL_ONE_BREAKABLE_COL_NUM) * 100.0f), 50.0f, 50.0f, 0.0f);
		m_breakObjects.push_back(breakObject);
	}
}

void Level::CreateLvlThree() {
	int m_break_objects_remaining = LVL_THREE_BREAKABLE_COL_NUM * LVL_THREE_BREAKABLE_ROW_NUM;
	Rect m_upperWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN * 3, COURT_WIDTH, WALL_THICKNESS);
	Rect m_lowerWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN + COURT_HEIGHT, COURT_WIDTH + WALL_THICKNESS, WALL_THICKNESS, 0.0f, 0.0f, true);
	Rect m_left_wall = Rect(HORIZONTAL_MARGIN, (VERTICLE_MARGIN * 3), WALL_THICKNESS, COURT_HEIGHT - (VERTICLE_MARGIN * 2));
	Rect m_right_wall = Rect(HORIZONTAL_MARGIN + COURT_WIDTH, (VERTICLE_MARGIN * 3), WALL_THICKNESS, COURT_HEIGHT - (VERTICLE_MARGIN * 2));
	Rect m_middle_wall = Rect(HORIZONTAL_MARGIN + (COURT_WIDTH / 2) + (WALL_THICKNESS/5), (VERTICLE_MARGIN * 3), WALL_THICKNESS, (VERTICLE_MARGIN * 7));
	Rect m_left_corner_rect = Rect(30, 210 + (VERTICLE_MARGIN * 1.5), 180, 10, -45.0f);
	Rect m_right_corner_rect = Rect(610, 75 + (VERTICLE_MARGIN * 1.5), 180, 10, 45.0f);
	Rect m_rotating_rect_left_up = Rect(HORIZONTAL_MARGIN + 100, (COURT_HEIGHT / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_THREE_OBSTACLE_ROT_SPEED);
	Rect m_rotating_rect_right_up = Rect(COURT_WIDTH - 100, (COURT_HEIGHT / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_THREE_OBSTACLE_ROT_SPEED);
	Rect m_rotating_rect_left_down = Rect(HORIZONTAL_MARGIN + 100, (COURT_HEIGHT * 2 / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_THREE_OBSTACLE_ROT_SPEED);
	Rect m_rect_center_down = Rect((COURT_WIDTH / 2) + HORIZONTAL_MARGIN + (WALL_THICKNESS/2), (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 100, 100, 45.0f);
	Rect m_rotating_rect_right_down = Rect(COURT_WIDTH - 100, (COURT_HEIGHT * 2 / 3) + VERTICLE_MARGIN, 75, 10, 0.0f, LVL_THREE_OBSTACLE_ROT_SPEED);

	m_levelRects.push_back(m_upperWall);
	m_levelRects.push_back(m_lowerWall);
	m_levelRects.push_back(m_left_wall);
	m_levelRects.push_back(m_middle_wall);
	m_levelRects.push_back(m_right_wall);
	m_levelRects.push_back(m_left_corner_rect);
	m_levelRects.push_back(m_right_corner_rect);
	m_levelRects.push_back(m_rotating_rect_left_up);
	m_levelRects.push_back(m_rotating_rect_right_up);
	m_levelRects.push_back(m_rotating_rect_left_down);
	m_levelRects.push_back(m_rect_center_down);
	m_levelRects.push_back(m_rotating_rect_right_down);

	for (int i = 0; i < m_break_objects_remaining; ++i) {
		if ((i != 0) && (i != 7)) {
			Rect breakObject = BreakObject(80.0f + ((float)(i % LVL_ONE_BREAKABLE_COL_NUM) * 80.0f),
				180.0f + ((float)(i / LVL_ONE_BREAKABLE_COL_NUM) * 100.0f), 50.0f, 50.0f, 0.0f);
			m_breakObjects.push_back(breakObject);
		}
	}
}

int Level::GetLvlNum() { return m_lvl_num;  }
std::vector<Rect> Level::GetLvlRects() { return m_levelRects;  }
std::vector<Rect> Level::GetBreakRects() { return m_breakObjects;  }