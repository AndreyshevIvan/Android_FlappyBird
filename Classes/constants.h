#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// SPLASH_SCENE
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.5

// COMMON
const float G = 12;
const float IMPULSE = 160;
const float SPEED = 250;

// BACKGROUND
const int SKY_Z_INDEX = 0;
const int CITY_Z_INDEX = 1;
const int GROUND_Z_INDEX = 3;
const float GROUND_HEIGHT = 70;
const size_t GROUNDS_COUNT = 3;
const float GROUND_OFFSET = 446;

// PIPES
const float PIPE_SPAWN_FREQUENCY = 1.3f;
const float LOWER_SCREEN_PIPE_THRESHOLD = 0.40f;
const float UPPER_SCREEN_PIPE_THRESHOLD = 0.80f;
const float PIPE_GAP = 150;

// BIRD
const int BIRD_Z_INDEX = 10;
const cocos2d::Size BIRD_SIZE = cocos2d::Size( 50, 35 );
const float BIRD_MAX_HEIGHT = 640;
const int BIRD_FRAMES = 3;
const float BIRD_POS_X_FACTOR = 0.2f;

const float BIRD_JUMP_HEIGHT = 64;
const float BIRD_JUMP_SPEED = sqrt((2.0f * BIRD_JUMP_HEIGHT) / G);

const float FLAPPING_SPEED = 15;
const float OSCILLATION_AMPLITUDE = 3;

const float UP_ROT_ANGALE = -50;
const float DOWN_ROT_ANGLE = 90;
const float DOWN_ROT_SPEED = 280;

#endif // __CONSTANTS_H__