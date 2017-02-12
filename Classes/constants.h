#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

const int FONT_OUTLINE_THICKNESS = 5;
const cocos2d::Color4B FONT_OUTLINE_COLOR = cocos2d::Color4B(92, 53, 70, 255);

const int MAP_BITMASK = 1;
const int POINT_BITMASK = 2;
const int BIRD_BITMASK = 3;

const float FLAPPING_SPEED = 10;
const float OSCILLATION_AMPLITUDE = 8;

const unsigned POINTS_BRONZE = 5;
const unsigned POINTS_SILVER = 15;
const unsigned POINTS_GOLD = 30;
const unsigned POINTS_PLATINUM = 60;
const unsigned POINTS_MAX = 4815;

#endif // __CONSTANTS_H__