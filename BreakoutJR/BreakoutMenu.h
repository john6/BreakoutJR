#pragma once
#include <algorithm>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GAME_STATE.h"
#include "RESOURCES.h"
#include "DIFFICULTY.h"

class BreakoutMenu
{
private:
	RESOURCES* m_resources;
	sf::Text m_instructions1;

	Button m_playButton;
	Button m_exitButton;
	Button m_easyButton;
	Button m_mediumButton;
	Button m_hardButton;
	bool m_shouldExit;
	bool m_shouldStart;
	DIFFICULTY m_currDifficulty;
	sf::Font m_font;

public:
	BreakoutMenu(RESOURCES* resources);
	~BreakoutMenu();

	bool PollInput(sf::Vector2i mousePosition, Button* button, bool stickyButton=false);

	DIFFICULTY GetDifficulty();
	
	void  UpdateButtonTriplet(sf::Vector2i mousePosition);

	GAME_STATE Update(float microSeconds, sf::RenderWindow* window, sf::Vector2i mousePosition);

	void Render(sf::RenderWindow* window);
};

