#pragma once
#include "Button.h"
#include "GAME_STATE.h"
#include <algorithm>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class PongMenu
{
private:
	Button m_playButton;
	Button m_exitButton;
	sf::SoundBuffer bufferButtonSound;
	sf::Sound sound;
	bool m_shouldExit;
	bool m_shouldStart;
	sf::Font* m_font;
	sf::Text m_instructions1;
	sf::Text m_instructions2;

public:
	PongMenu(sf::Font* font);
	~PongMenu();

	bool PollInput(sf::Vector2i mousePosition, Button* button);

	GAME_STATE Update(float microSeconds, sf::RenderWindow* window, sf::Vector2i mousePosition);

	void Render(sf::RenderWindow* window);
};

