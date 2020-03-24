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
#include "Level.h"

enum PLAY_STATE { SERVE_PLAYER_ONE, BALL_IN_PLAY };

class PongGame
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
	sf::Text m_blocks_remaining_text;
	sf::Text m_balls_remaining_text;

	PLAY_STATE m_playState;

	GAME_STATE UpdateMoving(float stepSize);

	GAME_STATE ServeP1(float stepSize);

	void BounceBall(Ball* ball, sf::Vector2f vel);

public:
	PongGame(Level lvl, RESOURCES* resources);
	~PongGame();

	GAME_STATE Update(float microSeconds);

	void PollKeys(float stepSize);

	void Render(sf::RenderWindow* window);
};

