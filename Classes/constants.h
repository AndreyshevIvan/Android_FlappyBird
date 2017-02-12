#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

const int FONT_OUTLINE_THICKNESS = 5;
const cocos2d::Color4B FONT_OUTLINE_COLOR = cocos2d::Color4B(92, 53, 70, 255);

const int MAP_BITMASK = 1;
const int POINT_BITMASK = 2;
const int BIRD_BITMASK = 3;

const float FLAPPING_SPEED = 10;
const float OSCILLATION_AMPLITUDE = 8;

const unsigned POINTS_BRONZE = 10;
const unsigned POINTS_SILVER = 20;
const unsigned POINTS_GOLD = 50;
const unsigned POINTS_PLATINUM = 100;
const unsigned POINTS_MAX = 4815;

#endif // __CONSTANTS_H__