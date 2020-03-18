#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <ctime>    
#include "PongGame.h"
#include "PongMenu.h"
#include "GAME_STATE.h"

int main()
{
	GAME_STATE state = MENU;
	sf::RenderWindow window(sf::VideoMode(1500, 900), "PONG");
	sf::Font font;
	if (!font.loadFromFile("kongtext.ttf")) {
		std::cerr << "error loading font \n";
	}
	PongGame game(5, &font);
	PongMenu menu = PongMenu(&font);

	typedef std::chrono::high_resolution_clock hiResTime;
	typedef std::chrono::microseconds microSec;
	typedef std::chrono::high_resolution_clock::time_point hiRes_time_point;

	hiRes_time_point currTime = hiResTime::now();
	const microSec UPDATE_INTERVAL(10000);
	microSec lag(0);

	while (window.isOpen())
	{
		sf::Event currEvent;
		if (((window.pollEvent(currEvent)) && (currEvent.type == sf::Event::Closed)) || (state == EXIT_GAME)) { window.close(); }
		hiRes_time_point newTime = hiResTime::now();
		microSec currInterval = std::chrono::duration_cast<microSec>(newTime - currTime);
		//std::cout << currInterval.count() << "\n";
		currTime = newTime;
		lag += currInterval;
		while (lag >= UPDATE_INTERVAL) {
			switch (state) {
				case MENU: {
					//std::cout << "update menu\n";
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					state = menu.Update((float)UPDATE_INTERVAL.count(), &window, mousePosition);
					break;
				}
				case IN_GAME: {
					//std::cout << "update game\n";
					state = game.Update((float)UPDATE_INTERVAL.count());
					break;
				}
			}
			lag -= UPDATE_INTERVAL;
			//lag = ms(0);
		}
		if (state == IN_GAME) {
			//std::cout << "render game\n";
			game.Render(&window);
		}
		else {
			//std::cout << "render menu\n";
			menu.Render(&window);
		}
	}
	return 0;
}