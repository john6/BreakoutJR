#include "PongGame.h"

PongGame::PongGame(int scoreToWin, sf::Font* font)
{
	m_maxScore = scoreToWin;
	m_playerOneScore = 0;

	m_ball = Ball(sf::Vector2f(0, 0), BALL_RADIUS);
	m_playerOne = Paddle(sf::RectangleShape(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT)), sf::Vector2f(HORIZONTAL_MARGIN + (COURT_WIDTH / 2), COURT_HEIGHT - (VERTICLE_MARGIN / 2)));

	m_upperWall = sf::RectangleShape(sf::Vector2f(COURT_WIDTH, WALL_THICKNESS));
	m_upperWall.setPosition(HORIZONTAL_MARGIN, VERTICLE_MARGIN);

	m_lowerWall = sf::RectangleShape(sf::Vector2f(COURT_WIDTH, WALL_THICKNESS));
	m_lowerWall.setPosition(HORIZONTAL_MARGIN, VERTICLE_MARGIN + COURT_HEIGHT);
	
	m_left_wall = sf::RectangleShape(sf::Vector2f(WALL_THICKNESS, COURT_HEIGHT));
	m_left_wall.setPosition(sf::Vector2f(HORIZONTAL_MARGIN, VERTICLE_MARGIN));
	m_left_wall.setFillColor(sf::Color::White);

	m_right_wall = sf::RectangleShape(sf::Vector2f(WALL_THICKNESS, COURT_HEIGHT));
	m_right_wall.setPosition(HORIZONTAL_MARGIN + COURT_WIDTH, VERTICLE_MARGIN);
	m_right_wall.setFillColor(sf::Color::White);

	m_font = font;
	m_p1_score.setFont(*m_font);
	m_p1_score.setString(std::to_string(0));
	m_p1_score.setCharacterSize(40);
	m_p1_score.setFillColor(sf::Color::White);
	m_p1_score.setPosition(sf::Vector2f(120.0f, 0.0f));

	if (!bufferPaddleBounce.loadFromFile("tone-beep.wav")) {
		std::cerr << "error loading bounce sound \n";
	}
	if (!bufferWallBounce.loadFromFile("tone-beep-lower-slower.wav")) {
		std::cerr << "error loading bounce sound \n";
	}
	if (!bufferScore.loadFromFile("sine-octaves-up-beep.wav")) {
		std::cerr << "error loading score sound \n";
	}
}

PongGame::~PongGame()
{
}

void PongGame::PollKeys(float stepSize) {
	float paddleStep = PIXELS_PER_MILLISECOND * stepSize;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		sf::Vector2f oldPos = m_playerOne.GetPosition();
		oldPos.x = std::max(std::min((oldPos.x - paddleStep), COURT_WIDTH + HORIZONTAL_MARGIN), HORIZONTAL_MARGIN);
		m_playerOne.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		sf::Vector2f oldPos = m_playerOne.GetPosition();
		oldPos.x = std::max(std::min((oldPos.x + paddleStep), COURT_WIDTH + HORIZONTAL_MARGIN), HORIZONTAL_MARGIN);
		m_playerOne.SetPosition(oldPos);
	}
}

GAME_STATE PongGame::ServeP1(float stepSize) {
	m_ball = Ball(sf::Vector2f(m_playerOne.GetPosition().x + (m_playerOne.GetSize().getSize().x / 2), m_playerOne.GetPosition().y - 35), 10.0f);
	m_ball.SetVelocity(sf::Vector2f(0, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		float randomNum = (float)(((rand() % 10)/10) - 0.5f);
		//std::cout << randomNum << "\n";
		m_ball.SetVelocity(sf::Vector2f(randomNum * stepSize, PIXELS_PER_MILLISECOND * stepSize));
		m_playState = BALL_IN_PLAY;
	}
	return IN_GAME;
}

GAME_STATE PongGame::UpdateMoving(float stepSize) {
	//ball movement
	m_ball.SetPosition(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetVelocity().x, m_ball.GetPosition().y + m_ball.GetVelocity().y));
	//ball bounce
	sf::Vector2f bounceVect1 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_playerOne.GetSize(), m_playerOne.GetPosition(), false);
	sf::Vector2f bounceVect3 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_upperWall, m_upperWall.getPosition(), false);
	sf::Vector2f bounceVect4 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_lowerWall, m_lowerWall.getPosition(), false);
	sf::Vector2f bounceVect5 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_right_wall, m_right_wall.getPosition(), true);
	sf::Vector2f bounceVect6 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_left_wall, m_left_wall.getPosition(), true);

	if (bounceVect1 != sf::Vector2f(0.0f, 0.0f)) {
		sound.setBuffer(bufferPaddleBounce);
		sound.play();
		m_ball.SetVelocity(bounceVect1);
	}
	if (bounceVect3 != sf::Vector2f(0.0f, 0.0f)) {
		sound.setBuffer(bufferWallBounce);
		sound.play();
		m_ball.SetVelocity(bounceVect3);
	}
	if (bounceVect4 != sf::Vector2f(0.0f, 0.0f)) {
		sound.setBuffer(bufferWallBounce);
		sound.play();
		m_ball.SetVelocity(bounceVect4);
	}
	if (bounceVect5 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect5);
	}
	if (bounceVect6 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect6);
	}

	return IN_GAME;
}

GAME_STATE PongGame::Update(float microSeconds) {
	float elapsedMilliseconds = abs(microSeconds / MICROSECONDS_TO_MILLISECONDS);
	//std::cout << "stepSize: " << elapsedMilliseconds << "\n";
	PollKeys(elapsedMilliseconds);
	switch (m_playState) {
	case (SERVE_PLAYER_ONE): {
		return ServeP1(elapsedMilliseconds);
		break;
	}
	case (BALL_IN_PLAY): {
		return UpdateMoving(elapsedMilliseconds);
		break;
	}
	default: {
		return MENU;
		break;
	}
	}
	
}

void PongGame::Render(sf::RenderWindow* window) {
	window->clear();
	//Draw order matters, will draw on top of last shape!
	window->draw(m_upperWall);
	window->draw(m_lowerWall);
	window->draw(m_right_wall);
	window->draw(m_left_wall);
	window->draw(m_p1_score);
	window->draw(m_ball.GetBall());
	sf::RectangleShape renderPaddle1(m_playerOne.GetSize());
	renderPaddle1.setPosition(m_playerOne.GetPosition());
	window->draw(renderPaddle1);
	window->display();
}