#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <ctime>    
#include "PongGame.h"
#include "PongMenu.h"
#include "GAME_STATE.h"
#include "GLOBAL_CONSTANTS.h"
#include "RESOURCES.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BREAKOUT");

	int currLvl = 1;
	RESOURCES resources = RESOURCES();
	PongGame* lvlOne = new PongGame(Level(0), &resources);
	PongGame* lvlTwo = new PongGame(Level(1), &resources);
	PongGame* lvlThree = new PongGame(Level(2), &resources);
	std::vector<PongGame*> levels{ lvlOne, lvlTwo, lvlThree };
	PongGame* game = levels[currLvl];
	PongMenu menu(&resources);
	GAME_STATE state = MENU;

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
				state = game->Update((float)UPDATE_INTERVAL.count());
				break;
			}
			case WIN: {
				// std::cout << "update game\n";
				delete levels[currLvl];
				PongGame* pongGame = new PongGame(Level(currLvl), &resources);
				levels[currLvl] = pongGame;
				if (currLvl < (levels.size() - 1)) { //proceed to next level
					currLvl += 1;
					game = levels[currLvl];
					state = IN_GAME;
				}
				else { //Player won the game
					currLvl = 0;
					game = levels[currLvl];
					state = MENU;
				}
				break;

			}
			case LOSE: {
				delete levels[currLvl];
				PongGame* pongGame = new PongGame(Level(currLvl), &resources);
				levels[currLvl] = pongGame;
				currLvl = 0;
				game = levels[currLvl];
				state = MENU;
				break;
			}
			}
			lag -= UPDATE_INTERVAL;
		}
		if (state == IN_GAME) {
			//std::cout << "render game\n";
			game->Render(&window);
		}
		else {
			//std::cout << "render menu\n";
			menu.Render(&window);
		}
	}
	return 0;
}