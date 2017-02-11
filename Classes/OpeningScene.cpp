#include "OpeningScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const float DISPLAY_OPENING_TIME = 1.2;
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

	Sprite* bird = Sprite::create("bird.png");
	auto birdSize = Size(bird->getContentSize().width / 4, bird->getContentSize().height);
	bird->setContentSize(birdSize);
	bird->setTextureRect(Rect(0, 0, birdSize.width, birdSize.height));
	bird->setPosition(center);

	auto action = RotateBy::create(1, Vec3(0, 360, 0));
	bird->runAction(RepeatForever::create(action));

	this->scheduleOnce(schedule_selector(OpeningScene::GoToGameScene), DISPLAY_OPENING_TIME);

	this->addChild(bird);

	return true;
}

void OpeningScene::GoToGameScene(float elapsedTime)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(FADE_TRANSITION, scene));
}