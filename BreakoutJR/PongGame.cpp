#include "PongGame.h"

PongGame::PongGame(Level lvl, RESOURCES* resources) :
	m_resources {resources}
{
	m_levelRects = lvl.GetLvlRects();
	m_breakRects = lvl.GetBreakRects();
	m_break_objects_remaining = m_breakRects.size();
	m_balls_remaining = 3;

	m_ball = Ball(sf::Vector2f(0, 0), BALL_RADIUS);
	m_playerOne = Paddle(HORIZONTAL_MARGIN + (COURT_WIDTH / 2), COURT_HEIGHT - (VERTICLE_MARGIN / 2), PADDLE_WIDTH, PADDLE_HEIGHT);

	m_font = resources->GetFont();

	m_lvl_num_text.setFont(m_font);
	std::string level_num_string = "Level " + std::to_string(lvl.GetLvlNum() + 1);
	m_lvl_num_text.setString(level_num_string);
	m_lvl_num_text.setCharacterSize(20);
	m_lvl_num_text.setFillColor(sf::Color::White);
	m_lvl_num_text.setPosition(sf::Vector2f(HORIZONTAL_MARGIN, 5.0f));

	m_balls_remaining_text.setFont(m_font);
	std::string balls_str = "balls remaining: " + std::to_string(m_balls_remaining);
	m_balls_remaining_text.setString(balls_str);
	m_balls_remaining_text.setCharacterSize(15);
	m_balls_remaining_text.setFillColor(sf::Color::White);
	m_balls_remaining_text.setPosition(sf::Vector2f(HORIZONTAL_MARGIN + (COURT_WIDTH / 2), 5.0f));

	m_blocks_remaining_text.setFont(m_font);
	std::string score_str = "blocks remaining: " + std::to_string(m_break_objects_remaining);
	m_blocks_remaining_text.setString(score_str);
	m_blocks_remaining_text.setCharacterSize(15);
	m_blocks_remaining_text.setFillColor(sf::Color::White);
	m_blocks_remaining_text.setPosition(sf::Vector2f(HORIZONTAL_MARGIN + (COURT_WIDTH / 2), 25.0f));
}

PongGame::~PongGame()
{
}

void PongGame::PollKeys(float stepSize) {
	float paddleStep = PADDLE_SPEED_PER_MILLISECOND * stepSize;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		float rotation = std::max(std::min(m_playerOne.GetCurrAngle() + 0.50f, MAX_ROTATION_DEGREES), -MAX_ROTATION_DEGREES);
		m_playerOne.SetRotation(rotation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		float rotation = std::max(std::min(m_playerOne.GetCurrAngle() - 0.50f, MAX_ROTATION_DEGREES), -MAX_ROTATION_DEGREES);
		m_playerOne.SetRotation(rotation);
	}
}

void PongGame::BounceBall(Ball* ball, sf::Vector2f vel) {
	sf::Vector2f currPos = ball->GetPosition();
	sf::Vector2f newPos(currPos.x + (vel.x * (ball->GetRadius() / 4)), currPos.y + (vel.y * (ball->GetRadius() / 4)));
	ball->SetPosition(newPos);
	ball->SetVelocity(vel);
}

GAME_STATE PongGame::ServeP1(float stepSize) {
	sf::Vector2f ballPosition = sf::Vector2f(m_playerOne.GetPosition().x + (m_playerOne.GetWidth() / 2) - (BALL_RADIUS), m_playerOne.GetPosition().y - 30.0f);
	sf::Vector2f rotatedBalloffSet = CollisionHandler::RotateVectorAboutAxis(ballPosition, m_playerOne.GetPosition(), m_playerOne.GetCurrAngle());
	m_ball = Ball(rotatedBalloffSet + m_playerOne.GetPosition(), BALL_RADIUS);
	m_ball.SetVelocity(sf::Vector2f(0, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		//float randomNum = (float)(((rand() % 10)/10) - 0.5f);
		//std::cout << randomNum << "\n";
		sf::Vector2f rotatedVelocity = CollisionHandler::RotateVector(sf::Vector2f(0.0f, -BALL_SPEED_PER_MILLISECOND * stepSize), m_playerOne.GetCurrAngle());
		m_ball.SetVelocity(rotatedVelocity);
		m_playState = BALL_IN_PLAY;
	}
	return IN_GAME;
}

GAME_STATE PongGame::UpdateMoving(float stepSize) {
	//ball movement
	m_ball.SetPosition(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetVelocity().x, m_ball.GetPosition().y + m_ball.GetVelocity().y));
	//Paddle bounce
	sf::Vector2f bounceVect = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_playerOne);
	if (bounceVect != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		BounceBall(&m_ball, bounceVect);
	}
	//Continuous rotation
	for (int i = 0; i < m_levelRects.size(); i++) {
		if (m_levelRects[i].GetContinuousRotation() != 0.0f) {
			float angle = m_levelRects[i].GetCurrAngle();
			float rot = m_levelRects[i].GetContinuousRotation();
			m_levelRects[i].SetRotation(angle + rot);
		}
	}
	//BreakObject Bounce
	std::vector<int> deleteIndexes;
	int vectorSizeInt = static_cast<int>(m_breakRects.size());
	for (int i = 0; i < vectorSizeInt; ++i) {
		Rect breakObj = m_breakRects[i];
		sf::Vector2f breakBounceVect = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), breakObj);
		if (breakBounceVect != sf::Vector2f(0.0f, 0.0f)) {
			BounceBall(&m_ball, breakBounceVect);
			deleteIndexes.push_back(i);
			break;
		}
	}
	//delete contacted breakobjects
	int deleteVectorSizeInt = static_cast<int>(deleteIndexes.size());
	for (int i = 0; i < deleteVectorSizeInt; i++) {
		m_breakRects.erase(m_breakRects.begin() + deleteIndexes[i]);
		m_resources->PlaySound(RESOURCES::EXPLOSION);
		m_break_objects_remaining -= 1;
		std::string score_str = "Blocks remaining: " + std::to_string(m_break_objects_remaining);
		m_blocks_remaining_text.setString(score_str);
		if (m_break_objects_remaining <= 0) {
			return WIN;
		}
	}

	//ball regular bounce
	for (Rect regularRect : m_levelRects) {
		sf::Vector2f bounceVect = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), regularRect);
		if (bounceVect != sf::Vector2f(0.0f, 0.0f)) {
			if (regularRect.IsDeath()) {
				m_resources->PlaySound(RESOURCES::NEGATIVE_BEEP);
				//m_ball.SetVelocity(bounceVect3);
				m_balls_remaining -= 1;
				std::string score_str = "Balls remaining: " + std::to_string(m_balls_remaining);
				m_balls_remaining_text.setString(score_str);
				if (m_balls_remaining <= 0) {
					return LOSE;
				}
				m_playState = SERVE_PLAYER_ONE;
			}
			else {
				m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
				BounceBall(&m_ball, bounceVect);
			}
			break;
		}
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

	for (Rect breakObj : m_breakRects) {
		sf::RectangleShape shape = GameRenderer::CreateDrawableRect(breakObj);
		shape.setFillColor(sf::Color::Red);
		window->draw(shape);
	}

	window->draw(GameRenderer::CreateDrawableRect(m_playerOne));

	for (Rect regularRect : m_levelRects) {
		sf::RectangleShape shape = GameRenderer::CreateDrawableRect(regularRect);
		shape.setFillColor(sf::Color::White);
		window->draw(shape);
	}


	window->draw(m_ball.GetBall());
	window->draw(m_lvl_num_text);
	window->draw(m_balls_remaining_text);
	window->draw(m_blocks_remaining_text);
	window->display();
}