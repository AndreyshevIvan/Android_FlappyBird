#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// SPLASH_SCENE
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.5

// BACKGROUND
const int SKY_Z_INDEX = 0;
const int CITY_Z_INDEX = 1;
const int GROUND_Z_INDEX = 3;
const float GROUND_HEIGHT = 70;

// PIPES
const float PIPE_SPAWN_FREQUENCY = 1.3f;
const float LOWER_SCREEN_PIPE_THRESHOLD = 0.40f;
const float UPPER_SCREEN_PIPE_THRESHOLD = 0.80f;
const float PIPE_GAP = 150;
const float PIPE_SPEED = 250;

// BIRD
const int BIRD_Z_INDEX = 10;
const cocos2d::Size BIRD_SIZE = cocos2d::Size( 34, 24 );
const int BIRD_FRAMES = 3;
const float BIRD_POS_X_FACTOR = 0.2;

#endif // __CONSTANTS_H__