#pragma once
#include "Court.h"
#include "Ball.h"
#include "Paddle.h"
#include "CollisionHandler.h"
#include "GameRenderer.h"
#include "GAME_STATE.h"
#include "GLOBAL_CONSTANTS.h"
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

	int m_playerOneScore;
	int	m_playerTwoScore;
	int	m_maxScore;
	Court m_court;
	Ball m_ball;
	Paddle m_playerOne;
	Paddle m_playerTwo;
	sf::RectangleShape m_upperWall;
	sf::RectangleShape m_lowerWall;
	sf::RectangleShape m_right_wall;
	sf::RectangleShape m_left_wall;
	sf::RectangleShape m_centerLine;

	Rect rotatingRect1;
	Rect rotatingRect2;

	sf::Font* m_font;
	sf::Text m_p1_score;
	sf::Text m_p2_score;

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

