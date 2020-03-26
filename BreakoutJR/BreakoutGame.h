#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "CollisionHandler.h"
#include "GameRenderer.h"
#include "GAME_STATE.h"
#include "GLOBAL_CONSTANTS.h"
#include "DIFFICULTY.h"
#include "RESOURCES.h"
#include "BreakObject.h"
#include <algorithm>
#include <chrono>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rect.h"
#include "Level.h"

enum PLAY_STATE { SERVE_PLAYER_ONE, BALL_IN_PLAY };

class BreakoutGame
{
private:
	int m_break_objects_remaining;
	int	m_balls_remaining;
	Ball m_ball;
	Rect m_playerOne;
	std::vector<Rect> m_levelRects;
	std::vector<Rect> m_breakRects;
	RESOURCES* m_resources;
	sf::Font m_font;
	sf::Text m_lvl_num_text;
	sf::Text m_time_remaining_text;
	sf::Text m_blocks_remaining_text;
	sf::Text m_balls_remaining_text;
	float m_ball_speed_per_mill;
	float m_paddle_width;
	float m_paddle_speed;

	std::chrono::high_resolution_clock::time_point m_beginTime;
	std::chrono::microseconds TimeSinceBegan;
	float m_time_to_complete;


	PLAY_STATE m_playState;

	GAME_STATE UpdateMoving(float stepSize);

	GAME_STATE ServeP1(float stepSize);

	void BounceBall(Ball* ball, sf::Vector2f vel);

public:
	BreakoutGame(Level lvl, DIFFICULTY difficulty, RESOURCES* resources);
	~BreakoutGame();

	GAME_STATE Update(float microSeconds);

	bool IsTimeUp();

	void PollKeys(float stepSize);

	void Render(sf::RenderWindow* window);
};

