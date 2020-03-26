#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <ctime>    
#include "BreakoutGame.h"
#include "BreakoutMenu.h"
#include "GAME_STATE.h"
#include "GLOBAL_CONSTANTS.h"
#include "DIFFICULTY.h"
#include "RESOURCES.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BREAKOUT");

	int currLvl;
	RESOURCES resources = RESOURCES();
	DIFFICULTY difficulty = MEDIUM;
	std::vector<BreakoutGame*> levels;
	BreakoutGame* game = new BreakoutGame(Level(0), difficulty, &resources); // This is bad but its just here to avoid an unintialized thing on line 49
	BreakoutMenu menu(&resources);
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
				if (currLvl < (levels.size() - 1)) { //proceed to next level
					currLvl += 1;
					game = levels[currLvl];
					state = IN_GAME;
				}
				else { //Player won the game
					delete levels[0];
					delete levels[1];
					delete levels[2];
					state = MENU;
				}
				break;

			}
			case LOSE: {
				delete levels[0];
				delete levels[1];
				delete levels[2];
				state = MENU;
				break;
			}
			case START_GAME: {
				currLvl = 0;
				DIFFICULTY difficulty = menu.GetDifficulty();
				levels.clear();
				BreakoutGame* lvlOne = new BreakoutGame(Level(0), difficulty, &resources);
				BreakoutGame* lvlTwo = new BreakoutGame(Level(1), difficulty, &resources);
				BreakoutGame* lvlThree = new BreakoutGame(Level(2), difficulty, &resources);
				levels.insert(levels.begin(), lvlOne);
				levels.insert(levels.begin() + 1, lvlTwo);
				levels.insert(levels.begin() + 2, lvlThree);
				game = levels[currLvl];
				state = IN_GAME;
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