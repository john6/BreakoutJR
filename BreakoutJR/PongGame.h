#pragma once
#include "Court.h"
#include "Ball.h"
#include "Paddle.h"
#include "CollisionHandler.h"
#include "GAME_STATE.h"
#include <algorithm>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum PLAY_STATE { SERVE_PLAYER_ONE, SERVE_PLAYER_TWO, TOWARD_PLAYER_ONE, TOWARD_PLAYER_TWO };

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
	sf::RectangleShape m_p1_goal;
	sf::RectangleShape m_p2_goal;
	sf::RectangleShape m_centerLine;
	sf::Font* m_font;
	sf::Text m_p1_score;
	sf::Text m_p2_score;

	const float PIXELS_PER_MILLISECOND = .90f;
	const float MICROSECONDS_TO_MILLISECONDS = 1000.0f;
	const float PADDLE_WIDTH = 100.0f;
	const float PADDLE_THICKNESS = 20.0f;
	const float COURT_LENGTH = 1400.0f;
	const float COURT_WIDTH = 800.0f;
	const float WALL_THICKNESS = 10.0f;
	const float CENTER_LINE_THICKNESS = 5.0f;
	const float BALL_RADIUS = 10.0f;
	const float VERTICLE_MARGIN = 50.0f;
	const float HORIZONTAL_MARGIN = 50.0f;

	PLAY_STATE m_playState;

	GAME_STATE ScoreP1();

	GAME_STATE ScoreP2();

	GAME_STATE UpdateMoving(float stepSize);

	GAME_STATE ServeP1(float stepSize);
	
	GAME_STATE ServeP2(float stepSize);

public:
	PongGame(int scoreToWin, sf::Font* font);
	~PongGame();

	GAME_STATE Update(float microSeconds);

	void PollKeys(float stepSize);

	void Render(sf::RenderWindow* window);
};

