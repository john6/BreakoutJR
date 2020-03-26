#include "BreakoutMenu.h"
#include "GLOBAL_CONSTANTS.h"

BreakoutMenu::BreakoutMenu(RESOURCES* resources) :
	m_resources {resources}
{

	sf::RectangleShape playButtonRect(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
	playButtonRect.setPosition(sf::Vector2f(100, 100));
	m_playButton = Button("Play", playButtonRect);
	m_playButton.SetColors(sf::Color::Black, sf::Color::White, sf::Color(128, 128, 128));

	sf::RectangleShape exitButtonRect(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
	exitButtonRect.setPosition(sf::Vector2f(400, 100));
	m_exitButton = Button("Exit", exitButtonRect);
	m_exitButton.SetColors(sf::Color::Black, sf::Color::White, sf::Color(128, 128, 128));

	sf::RectangleShape easyButtonRect(sf::Vector2f(BUTTON_WIDTH * .75f, BUTTON_HEIGHT));
	easyButtonRect.setPosition(sf::Vector2f(70, 150 + BUTTON_HEIGHT));
	m_easyButton = Button("Easy", easyButtonRect);
	m_easyButton.SetColors(sf::Color::Green, sf::Color::White, sf::Color(128, 128, 128));
	m_easyButton.SetState(Button::UP);

	sf::RectangleShape mediumButtonRect(sf::Vector2f(BUTTON_WIDTH * .75f, BUTTON_HEIGHT));
	mediumButtonRect.setPosition(sf::Vector2f(70 + (BUTTON_WIDTH * 0.85f), 150 + BUTTON_HEIGHT));
	m_mediumButton = Button("Medium", mediumButtonRect);
	m_mediumButton.SetColors(sf::Color::Yellow, sf::Color::White, sf::Color(128, 128, 128));
	m_mediumButton.SetState(Button::UP);

	sf::RectangleShape hardButtonRect(sf::Vector2f(BUTTON_WIDTH * .75f, BUTTON_HEIGHT));
	hardButtonRect.setPosition(sf::Vector2f(70 + (BUTTON_WIDTH * 1.70f), 150 + BUTTON_HEIGHT));
	m_hardButton = Button("Hard", hardButtonRect);
	m_hardButton.SetColors(sf::Color::Red, sf::Color::White, sf::Color(128, 128, 128));
	m_hardButton.SetState(Button::UP);

	m_shouldExit = false;
	m_shouldStart = false;
	m_currDifficulty = MEDIUM;
	m_easyButton.SetState(Button::UP);
	m_mediumButton.SetState(Button::DOWN);
	m_hardButton.SetState(Button::UP);

	m_font = m_resources->GetFont();

	m_instructions1.setFont(m_font);
	m_instructions1.setString("Controls: \n'A' to move left,\n'D' to move right,\n'Q' to tilt left\n'E' to tilt right\n'W' to serve \n");
	m_instructions1.setCharacterSize(25);
	m_instructions1.setFillColor(sf::Color::White);
	m_instructions1.setPosition(sf::Vector2f(100, 500));
}

BreakoutMenu::~BreakoutMenu()
{
}

DIFFICULTY BreakoutMenu::GetDifficulty() { return m_currDifficulty; }

bool BreakoutMenu::PollInput(sf::Vector2i mousePosition, Button* button, bool stickyButton) {
	float halfWidth = (button->GetRect().getSize().x / 2);
	float halfHeight = (button->GetRect().getSize().y / 2);
	float distX = abs(mousePosition.x - (button->GetRect().getPosition().x + halfWidth));
	float distY = abs(mousePosition.y - (button->GetRect().getPosition().y + halfHeight));
	if ((distX <= halfWidth) && (distY <= halfHeight)) {
		if (!stickyButton) { button->SetState(Button::HOVER); }
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			button->SetState(Button::DOWN);
			return true;
		}
	}
	else if (!stickyButton) {
		button->SetState(Button::UP);
	}
	return false;
}

void  BreakoutMenu::UpdateButtonTriplet(sf::Vector2i mousePosition) {
	bool easyButtonPressed = PollInput(mousePosition, &m_easyButton, true);
	bool mediumButtonPressed = PollInput(mousePosition, &m_mediumButton, true);
	bool hardButtonPressed = PollInput(mousePosition, &m_hardButton, true);

	if (easyButtonPressed) {
		m_currDifficulty = EASY;
		m_easyButton.SetState(Button::DOWN);
		m_mediumButton.SetState(Button::UP);
		m_hardButton.SetState(Button::UP);
	}
	else if (mediumButtonPressed) {
		m_currDifficulty = MEDIUM;
		m_easyButton.SetState(Button::UP);
		m_mediumButton.SetState(Button::DOWN);
		m_hardButton.SetState(Button::UP);
	}
	else if (hardButtonPressed) {
		m_currDifficulty = HARD;
		m_easyButton.SetState(Button::UP);
		m_mediumButton.SetState(Button::UP);
		m_hardButton.SetState(Button::DOWN);
	}
}

GAME_STATE BreakoutMenu::Update(float millisecs, sf::RenderWindow* window, sf::Vector2i mousePosition) {
	UpdateButtonTriplet(mousePosition);
	bool playButtonPressed = PollInput(mousePosition, &m_playButton);
	bool exitButtonPressed = PollInput(mousePosition, &m_exitButton);

	if (playButtonPressed) {
		m_resources->PlaySound(RESOURCES::OCTAVE_BEEP);
		return START_GAME;
	}
	else if (exitButtonPressed) {
		m_resources->PlaySound(RESOURCES::OCTAVE_BEEP);
		return EXIT_GAME;
	}
	else { 
		return MENU; 
	}
}

void BreakoutMenu::Render(sf::RenderWindow* window) {
	window->clear();
	window->draw(m_playButton.GetRect());
	window->draw(m_exitButton.GetRect());
	window->draw(m_easyButton.GetRect());
	window->draw(m_mediumButton.GetRect());
	window->draw(m_hardButton.GetRect());

	sf::Text play = m_playButton.GetText();
	play.setFont(m_font);
	window->draw(play);

	sf::Text exit = m_exitButton.GetText();
	exit.setFont(m_font);
	window->draw(exit);

	sf::Text easy = m_easyButton.GetText();
	easy.setFont(m_font);
	window->draw(easy);

	sf::Text medium = m_mediumButton.GetText();
	medium.setFont(m_font);
	window->draw(medium);

	sf::Text hard = m_hardButton.GetText();
	hard.setFont(m_font);
	window->draw(hard);

	window->draw(m_instructions1);
	window->display();
}
