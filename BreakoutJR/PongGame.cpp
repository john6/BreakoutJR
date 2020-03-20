#include "PongGame.h"

PongGame::PongGame(int scoreToWin, sf::Font* font)
{
	m_maxScore = scoreToWin;
	m_playerOneScore = 0;

	m_ball = Ball(sf::Vector2f(0, 0), BALL_RADIUS);
	m_playerOne = Paddle(HORIZONTAL_MARGIN + (COURT_WIDTH / 2), COURT_HEIGHT - (VERTICLE_MARGIN / 2), PADDLE_WIDTH, PADDLE_HEIGHT);
	m_upperWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN, COURT_WIDTH, WALL_THICKNESS);
	m_lowerWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN + COURT_HEIGHT, COURT_WIDTH, WALL_THICKNESS);
	m_left_wall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN, WALL_THICKNESS, COURT_HEIGHT);
	m_right_wall = Rect(HORIZONTAL_MARGIN + COURT_WIDTH, VERTICLE_MARGIN, WALL_THICKNESS, COURT_HEIGHT);

	m_font = font;
	m_p1_score.setFont(*m_font);
	m_p1_score.setString(std::to_string(0));
	m_p1_score.setCharacterSize(40);
	m_p1_score.setFillColor(sf::Color::White);
	m_p1_score.setPosition(sf::Vector2f(120.0f, 0.0f));

	m_left_corner_rect = Rect(20, 210, 220, 10, 0);
	m_right_corner_rect = Rect(600, 50, 200, 10, 0);
	m_left_corner_rect.SetRotation(m_left_corner_rect.GetRotation() - 45.0f);
	m_right_corner_rect.SetRotation(m_right_corner_rect.GetRotation() + 45.0f);

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
		oldPos.x = std::max(std::min((oldPos.x - paddleStep), COURT_WIDTH + HORIZONTAL_MARGIN - PADDLE_WIDTH), HORIZONTAL_MARGIN);
		m_playerOne.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		sf::Vector2f oldPos = m_playerOne.GetPosition();
		oldPos.x = std::max(std::min((oldPos.x + paddleStep), COURT_WIDTH + HORIZONTAL_MARGIN - PADDLE_WIDTH), HORIZONTAL_MARGIN);
		m_playerOne.SetPosition(oldPos);
	}
}

GAME_STATE PongGame::ServeP1(float stepSize) {
	m_ball = Ball(sf::Vector2f(m_playerOne.GetPosition().x + (m_playerOne.GetWidth() / 2), m_playerOne.GetPosition().y - 35), 10.0f);
	m_ball.SetVelocity(sf::Vector2f(0, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		float randomNum = (float)(((rand() % 10)/10) - 0.5f);
		//std::cout << randomNum << "\n";
		m_ball.SetVelocity(sf::Vector2f(PIXELS_PER_MILLISECOND * randomNum * stepSize, PIXELS_PER_MILLISECOND * stepSize));
		m_playState = BALL_IN_PLAY;
	}
	return IN_GAME;
}

GAME_STATE PongGame::UpdateMoving(float stepSize) {

	//rotation
	//rotatingRect1.SetRotation(rotatingRect1.GetRotation() + 0.50f);
	//rotatingRect2.SetRotation(rotatingRect2.GetRotation() + 0.50f);

	//ball movement
	m_ball.SetPosition(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetVelocity().x, m_ball.GetPosition().y + m_ball.GetVelocity().y));
	//ball bounce
	sf::Vector2f bounceVect1 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_playerOne);
	sf::Vector2f bounceVect2 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_upperWall);
	sf::Vector2f bounceVect3 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_lowerWall);
	sf::Vector2f bounceVect4 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_right_wall);
	sf::Vector2f bounceVect5 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_left_wall);
	sf::Vector2f bounceVect6 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_left_corner_rect);
	sf::Vector2f bounceVect7 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_right_corner_rect);

	if (bounceVect1 != sf::Vector2f(0.0f, 0.0f)) {
		sound.setBuffer(bufferPaddleBounce);
		sound.play();
		m_ball.SetVelocity(bounceVect1);
	}
	else if (bounceVect2 != sf::Vector2f(0.0f, 0.0f)) {
		sound.setBuffer(bufferWallBounce);
		sound.play();
		m_ball.SetVelocity(bounceVect2);
	}
	else if (bounceVect3 != sf::Vector2f(0.0f, 0.0f)) {
		sound.setBuffer(bufferWallBounce);
		sound.play();
		m_ball.SetVelocity(bounceVect3);
	}
	else if (bounceVect4 != sf::Vector2f(0.0f, 0.0f)) {
		sound.setBuffer(bufferWallBounce);
		sound.play();
		m_ball.SetVelocity(bounceVect4);
	}
	else if (bounceVect5 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect5);
	}
	else if (bounceVect6 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect6);
	}
	else if (bounceVect7 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect7);
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
	//Draw order matters, will draw on top of last shape!
	window->clear();
	window->draw(GameRenderer::CreateDrawableRect(m_upperWall));
	window->draw(GameRenderer::CreateDrawableRect(m_lowerWall));
	window->draw(GameRenderer::CreateDrawableRect(m_right_wall));
	window->draw(GameRenderer::CreateDrawableRect(m_left_wall));
	window->draw(GameRenderer::CreateDrawableRect(m_playerOne));
	window->draw(GameRenderer::CreateDrawableRect(m_left_corner_rect));
	window->draw(GameRenderer::CreateDrawableRect(m_right_corner_rect));
	window->draw(m_ball.GetBall());
	window->draw(m_p1_score);
	window->display();
}