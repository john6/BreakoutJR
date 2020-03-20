#pragma once
class GLOBAL_CONSTANTS
{
public:
	GLOBAL_CONSTANTS();
	~GLOBAL_CONSTANTS();
};

//https://www.fluentcpp.com/2019/07/23/how-to-define-a-global-constant-in-cpp/
//according to this article I should be adding extern here but that means I have to define these variables elsewhere also

//GAME SETTINGS

const float PIXELS_PER_MILLISECOND = .90f;
const float MICROSECONDS_TO_MILLISECONDS = 1000.0f;
const float PADDLE_HEIGHT = 20.0f;
const float PADDLE_WIDTH = 100.0f;
const float COURT_WIDTH = 700.0f;
const float COURT_HEIGHT = 800.0f;
const float WALL_THICKNESS = 15.0f;
const float CENTER_LINE_THICKNESS = 5.0f;
const float BALL_RADIUS = 10.0f;
const float VERTICLE_MARGIN = 50.0f;
const float HORIZONTAL_MARGIN = 25.0f;


const int SCREEN_WIDTH = COURT_WIDTH + (HORIZONTAL_MARGIN * 2);
const int SCREEN_HEIGHT = COURT_HEIGHT + (VERTICLE_MARGIN * 2);

const float RADIAN_RIGHT = 0.0f;
const float RADIAN_DOWN = -4.71239;
const float DEGREE_RIGHT = 0.0f;
const float DEGREE_DOWN = -270.0f;
const float PI = 3.1459;

//MENU SETTINGS
const float BUTTON_WIDTH = SCREEN_WIDTH / 3;
const float BUTTON_HEIGHT = SCREEN_HEIGHT / 10;