#include "OpeningScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const int FONT_LOADING_SIZE = 35;

const cocos2d::Vec2 JOKE_OFFSET = Vec2(0, -85);

const float DISPLAY_OPENING_TIME = 2;
const float FADE_TRANSITION = 0.6f;

const cocos2d::Color4F BACKGROUND_COLOR = cocos2d::Color4F(cocos2d::Color3B(1, 134, 149));

Scene* OpeningScene::createScene()
{
	auto scene = Scene::create();
	auto layer = OpeningScene::create();
	scene->addChild(layer);
	return scene;
}

bool OpeningScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getVisibleSize();
	Point center = winSize * 0.5f;

	Director::getInstance()->setClearColor(BACKGROUND_COLOR);

	Sprite* bird = Sprite::create("textures/bird.png");
	auto birdSize = Size(bird->getContentSize().width / 4, bird->getContentSize().height);
	bird->setContentSize(birdSize);
	bird->setTextureRect(Rect(0, 0, birdSize.width, birdSize.height));
	bird->setPosition(center);

	std::string joke = "THIS SCENE IS MADE FOR EPIC...";
	Label* loadingJoke = Label::createWithTTF(joke, "fonts/FlappyBird.ttf", FONT_LOADING_SIZE);
	loadingJoke->setAnchorPoint(Vec2(0.5f, 0.5f));
	loadingJoke->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	loadingJoke->setPosition(center + JOKE_OFFSET);

	auto action = RotateBy::create(1, Vec3(0, 360, 0));
	bird->runAction(RepeatForever::create(action));

	this->scheduleOnce(schedule_selector(OpeningScene::GoToGameScene), DISPLAY_OPENING_TIME);

	this->addChild(bird);
	this->addChild(loadingJoke);

	return true;
}

void OpeningScene::GoToGameScene(float elapsedTime)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(FADE_TRANSITION, scene));
}