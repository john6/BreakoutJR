#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "CollisionHandler.h"
#include "GameRenderer.h"
#include "GAME_STATE.h"
#include "GLOBAL_CONSTANTS.h"
#include "RESOURCES.h"
#include "BreakObject.h"
#include <algorithm>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rect.h"

enum PLAY_STATE { SERVE_PLAYER_ONE, BALL_IN_PLAY };

class PongGame
{
private:

	int m_break_objects_remaining;
	int	m_balls_remaining;

	Ball m_ball;
	Rect m_playerOne;

	Rect m_upperWall;
	Rect m_lowerWall;
	Rect m_right_wall;
	Rect m_left_wall;
	Rect m_centerLine;

	Rect m_left_corner_rect;
	Rect m_right_corner_rect;
	Rect m_rotating_rect_left;
	Rect m_rotating_rect_center;
	Rect m_rotating_rect_right;
	std::vector<std::vector<float>> breakObjectPositions;
	std::vector<Rect> breakObjects;


	RESOURCES* m_resources;
	sf::Font m_font;
	sf::Text m_blocks_remaining_text;
	sf::Text m_balls_remaining_text;

	PLAY_STATE m_playState;

	GAME_STATE UpdateMoving(float stepSize);

	GAME_STATE ServeP1(float stepSize);

public:
	PongGame(int lvlNum, RESOURCES* resources);
	~PongGame();

	GAME_STATE Update(float microSeconds);

	void PollKeys(float stepSize);

	void Render(sf::RenderWindow* window);
};

