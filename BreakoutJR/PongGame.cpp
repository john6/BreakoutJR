#include "PongGame.h"

PongGame::PongGame(int lvlNum, RESOURCES* resources) :
	m_resources {resources}
{
	m_balls_remaining = lvlNum;
	m_break_objects_remaining = LEVEL_ONE_BREAKABLE_COL_NUM * LEVEL_ONE_BREAKABLE_ROW_NUM;
	m_balls_remaining = 3;

	m_ball = Ball(sf::Vector2f(0, 0), BALL_RADIUS);
	m_playerOne = Paddle(HORIZONTAL_MARGIN + (COURT_WIDTH / 2), COURT_HEIGHT - (VERTICLE_MARGIN / 2), PADDLE_WIDTH, PADDLE_HEIGHT);
	m_upperWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN, COURT_WIDTH, WALL_THICKNESS);
	m_lowerWall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN + COURT_HEIGHT, COURT_WIDTH, WALL_THICKNESS);
	m_left_wall = Rect(HORIZONTAL_MARGIN, VERTICLE_MARGIN, WALL_THICKNESS, COURT_HEIGHT);
	m_right_wall = Rect(HORIZONTAL_MARGIN + COURT_WIDTH, VERTICLE_MARGIN, WALL_THICKNESS, COURT_HEIGHT);

	m_font = resources->GetFont();

	m_blocks_remaining_text.setFont(m_font);
	std::string score_str = "blocks remaining: " + std::to_string(m_break_objects_remaining);
	m_blocks_remaining_text.setString(score_str);
	m_blocks_remaining_text.setCharacterSize(15);
	m_blocks_remaining_text.setFillColor(sf::Color::White);
	m_blocks_remaining_text.setPosition(sf::Vector2f(HORIZONTAL_MARGIN, 10.0f));

	m_balls_remaining_text.setFont(m_font);
	std::string balls_str = "balls remaining: " + std::to_string(m_balls_remaining);
	m_balls_remaining_text.setString(balls_str);
	m_balls_remaining_text.setCharacterSize(15);
	m_balls_remaining_text.setFillColor(sf::Color::White);
	m_balls_remaining_text.setPosition(sf::Vector2f(HORIZONTAL_MARGIN + (COURT_WIDTH / 2), 10.0f));

	m_left_corner_rect = Rect(20, 210, 220, 10, 0);
	m_right_corner_rect = Rect(600, 50, 200, 10, 0);
	m_rotating_rect_left = Rect(HORIZONTAL_MARGIN + 100, (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 75, 10);
	m_rotating_rect_center = Rect((COURT_WIDTH / 2) + HORIZONTAL_MARGIN, (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 75, 10);
	m_rotating_rect_right = Rect(COURT_WIDTH - 100, (COURT_HEIGHT / 2) + VERTICLE_MARGIN, 75, 10);
	m_left_corner_rect.SetRotation(m_left_corner_rect.GetRotation() - 45.0f);
	m_right_corner_rect.SetRotation(m_right_corner_rect.GetRotation() + 45.0f);

	for (int i = 0; i < m_break_objects_remaining; ++i) {
		Rect breakObject = BreakObject(80.0f + ((float)(i % LEVEL_ONE_BREAKABLE_COL_NUM) * 80.0f) ,
									   210.0f + ((float)( i / LEVEL_ONE_BREAKABLE_COL_NUM) * 100.0f), 50.0f, 50.0f, 0.0f);
		breakObjects.push_back(breakObject);
	}
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
		float rotation = std::max(std::min(m_playerOne.GetRotation() + 0.50f, MAX_ROTATION_DEGREES), -MAX_ROTATION_DEGREES);
		m_playerOne.SetRotation(rotation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		float rotation = std::max(std::min(m_playerOne.GetRotation() - 0.50f, MAX_ROTATION_DEGREES), -MAX_ROTATION_DEGREES);
		m_playerOne.SetRotation(rotation);
	}
}

GAME_STATE PongGame::ServeP1(float stepSize) {
	sf::Vector2f ballPosition = sf::Vector2f(m_playerOne.GetPosition().x + (m_playerOne.GetWidth() / 2) - (BALL_RADIUS), m_playerOne.GetPosition().y - 30.0f);
	sf::Vector2f rotatedBalloffSet = CollisionHandler::RotateVectorAboutAxis(ballPosition, m_playerOne.GetPosition(), m_playerOne.GetRotation());
	m_ball = Ball(rotatedBalloffSet + m_playerOne.GetPosition(), BALL_RADIUS);
	m_ball.SetVelocity(sf::Vector2f(0, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		//float randomNum = (float)(((rand() % 10)/10) - 0.5f);
		//std::cout << randomNum << "\n";
		sf::Vector2f rotatedVelocity = CollisionHandler::RotateVector(sf::Vector2f(0.0f, -BALL_SPEED_PER_MILLISECOND * stepSize), m_playerOne.GetRotation());
		m_ball.SetVelocity(rotatedVelocity);
		m_playState = BALL_IN_PLAY;
	}
	return IN_GAME;
}

GAME_STATE PongGame::UpdateMoving(float stepSize) {
	//rotation
	m_rotating_rect_left.SetRotation(m_rotating_rect_right.GetRotation() + 0.50f);
	m_rotating_rect_center.SetRotation(m_rotating_rect_right.GetRotation() + 0.50f);
	m_rotating_rect_right.SetRotation(m_rotating_rect_right.GetRotation() + 0.50f);
	//ball movement
	m_ball.SetPosition(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetVelocity().x, m_ball.GetPosition().y + m_ball.GetVelocity().y));

	//BreakObject Bounce
	std::vector<int> deleteIndexes;
	int vectorSizeInt = static_cast<int>(breakObjects.size());
	for (int i = 0; i < vectorSizeInt; ++i) {
		Rect breakObj = breakObjects[i];
		sf::Vector2f breakBounceVect = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), breakObj);
		if (breakBounceVect != sf::Vector2f(0.0f, 0.0f)) {
			deleteIndexes.push_back(i);
		}
	}
	int deleteVectorSizeInt = static_cast<int>(deleteIndexes.size());
	for (int i = 0; i < deleteVectorSizeInt; i++) {
		sf::Vector2f breakBounceVect = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), breakObjects[deleteIndexes[i]]);
		m_ball.SetVelocity(breakBounceVect);
		breakObjects.erase(breakObjects.begin() + deleteIndexes[i]);
		m_resources->PlaySound(RESOURCES::EXPLOSION);
		m_break_objects_remaining -= 1;
		std::string score_str = "Blocks remaining: " + std::to_string(m_break_objects_remaining);
		m_blocks_remaining_text.setString(score_str);
		if (m_break_objects_remaining <= 0) {
			return MENU;
		}
	}

	//ball bounce
	sf::Vector2f bounceVect1 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_playerOne);
	sf::Vector2f bounceVect2 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_upperWall);
	sf::Vector2f bounceVect3 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_lowerWall);
	sf::Vector2f bounceVect4 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_right_wall);
	sf::Vector2f bounceVect5 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_left_wall);
	sf::Vector2f bounceVect6 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_left_corner_rect);
	sf::Vector2f bounceVect7 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_right_corner_rect);
	sf::Vector2f bounceVect8 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_rotating_rect_left);
	sf::Vector2f bounceVect9 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_rotating_rect_center);
	sf::Vector2f bounceVect10 = CollisionHandler::BounceBall(m_ball.GetBall(), m_ball.GetVelocity(), m_rotating_rect_right);


	if (bounceVect1 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect1);
	}
	else if (bounceVect2 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect2);
	}
	else if (bounceVect3 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::NEGATIVE_BEEP);
		//m_ball.SetVelocity(bounceVect3);
		m_balls_remaining -= 1;
		std::string score_str = "Balls remaining: " + std::to_string(m_balls_remaining);
		m_balls_remaining_text.setString(score_str);
		if (m_balls_remaining <= 0) {
			return MENU;
		}
		m_playState = SERVE_PLAYER_ONE;
	}
	else if (bounceVect4 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect4);
	}
	else if (bounceVect5 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect5);
	}
	else if (bounceVect6 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect6);
	}
	else if (bounceVect7 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect7);
	}
	else if (bounceVect8 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect8);
	}
	else if (bounceVect9 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect9);
	}
	else if (bounceVect10 != sf::Vector2f(0.0f, 0.0f)) {
		m_resources->PlaySound(RESOURCES::REGULAR_BEEP);
		m_ball.SetVelocity(bounceVect10);
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

	for (Rect breakObj : breakObjects) {
		sf::RectangleShape shape = GameRenderer::CreateDrawableRect(breakObj);
		shape.setFillColor(sf::Color::Red);
		window->draw(shape);
	}

	window->draw(GameRenderer::CreateDrawableRect(m_upperWall));
	window->draw(GameRenderer::CreateDrawableRect(m_lowerWall));
	window->draw(GameRenderer::CreateDrawableRect(m_right_wall));
	window->draw(GameRenderer::CreateDrawableRect(m_left_wall));
	window->draw(GameRenderer::CreateDrawableRect(m_playerOne));
	window->draw(GameRenderer::CreateDrawableRect(m_left_corner_rect));
	window->draw(GameRenderer::CreateDrawableRect(m_right_corner_rect));
	window->draw(GameRenderer::CreateDrawableRect(m_rotating_rect_left));
	window->draw(GameRenderer::CreateDrawableRect(m_rotating_rect_center));
	window->draw(GameRenderer::CreateDrawableRect(m_rotating_rect_right));
	window->draw(m_ball.GetBall());
	window->draw(m_blocks_remaining_text);
	window->draw(m_balls_remaining_text);
	window->display();
}