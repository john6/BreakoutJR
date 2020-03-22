#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "CollisionHandler.h"
#include "GameRenderer.h"
#include "GAME_STATE.h"
#include "GLOBAL_CONSTANTS.h"
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
	sf::SoundBuffer bufferPaddleBounce;
	sf::SoundBuffer bufferWallBounce;
	sf::SoundBuffer bufferScore;
	sf::Sound sound;

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
	Rect m_rotating_center_rect;
	std::vector<std::vector<float>> breakObjectPositions;
	std::vector<Rect> breakObjects;


	sf::Font* m_font;
	sf::Text m_blocks_remaining_text;
	sf::Text m_balls_remaining_text;

	PLAY_STATE m_playState;

	GAME_STATE UpdateMoving(float stepSize);

	GAME_STATE ServeP1(float stepSize);

public:
	PongGame(int scoreToWin, sf::Font* font);
	~PongGame();

	GAME_STATE Update(float microSeconds);

	void PollKeys(float stepSize);

	void Render(sf::RenderWindow* window);
};

