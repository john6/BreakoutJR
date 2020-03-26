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
const float MICROSECONDS_TO_MILLISECONDS = 1000.0f;
const float PADDLE_HEIGHT = 20.0f;
const float COURT_WIDTH = 700.0f;
const float COURT_HEIGHT = 800.0f;
const float WALL_THICKNESS = 15.0f;
const float CENTER_LINE_THICKNESS = 5.0f;
const float BALL_RADIUS = 10.0f;
const float VERTICLE_MARGIN = 50.0f;
const float HORIZONTAL_MARGIN = 25.0f;

//EASY SETTINGS
const float BALL_SPEED_PER_MILLISECOND_EASY = 0.40f;
const float PADDLE_SPEED_PER_MILLISECOND_EASY = 0.6f;
const float PADDLE_WIDTH_EASY = 150.0f;
const float SECONDS_TO_WIN_EASY = 300.0f;
//MEDIUM SETTINGS
const float BALL_SPEED_PER_MILLISECOND_MEDIUM = 0.7f;
const float PADDLE_SPEED_PER_MILLISECOND_MEDIUM = 0.6f;
const float PADDLE_WIDTH_MEDIUM = 120.0f;
const float SECONDS_TO_WIN_MEDIUM = 180.0f;

//HARD SETTINGS
const float BALL_SPEED_PER_MILLISECOND_HARD = 1.0f;
const float PADDLE_SPEED_PER_MILLISECOND_HARD = 0.9f;
const float PADDLE_WIDTH_HARD = 100.0f;
const float SECONDS_TO_WIN_HARD = 135.0f;

const int SCREEN_WIDTH = static_cast<int>(COURT_WIDTH + (HORIZONTAL_MARGIN * 2));
const int SCREEN_HEIGHT = static_cast<int>(COURT_HEIGHT + (VERTICLE_MARGIN * 2));

const float RADIAN_RIGHT = 0.0f;   //these should be doubles
const float RADIAN_DOWN = -4.71239f;
const float DEGREE_RIGHT = 0.0f;
const float DEGREE_DOWN = -270.0f;
const float MAX_ROTATION_DEGREES = 45;
const float PI = 3.1459f;

//MENU SETTINGS
const float BUTTON_WIDTH = SCREEN_WIDTH / 3;
const float BUTTON_HEIGHT = SCREEN_HEIGHT / 10;