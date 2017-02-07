#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	auto bgSprite = Sprite::create("background.png");
	bgSprite->setPosition(center);

	auto citySprite = Sprite::create("city.png");
	citySprite->setAnchorPoint(Vec2(0.5f, 0));
	citySprite->setPosition(center.x, GROUND_HEIGHT);

	auto groundSprite = Sprite::create("ground.png");
	groundSprite->setAnchorPoint(Vec2(0, 0));
	groundSprite->setPosition(Point::ZERO);

	this->addChild(bgSprite, SKY_Z_INDEX);
	this->addChild(citySprite, CITY_Z_INDEX);
	this->addChild(groundSprite, GROUND_Z_INDEX);

	m_bird = Bird::CreateWithFileName("one_bird.png");
	m_bird->setPosition(BIRD_POS_X_FACTOR * visibleSize.width, center.y);

	this->addChild(m_bird, BIRD_Z_INDEX);

	return true;
}
