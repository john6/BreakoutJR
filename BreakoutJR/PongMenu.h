#pragma once
#include <algorithm>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GAME_STATE.h"
#include "RESOURCES.h"

class PongMenu
{
private:
	RESOURCES* m_resources;
	sf::Text m_instructions1;
	//sf::Text m_instructions2;

	Button m_playButton;
	Button m_exitButton;
	bool m_shouldExit;
	bool m_shouldStart;
	sf::Font m_font;

public:
	PongMenu(RESOURCES* resources);
	~PongMenu();

	bool PollInput(sf::Vector2i mousePosition, Button* button);

	GAME_STATE Update(float microSeconds, sf::RenderWindow* window, sf::Vector2i mousePosition);

	void Render(sf::RenderWindow* window);
};

