#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	output.open("out.txt");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	m_background->Init(this);

	m_bird = Bird::CreateWithFileName("one_bird.png");
	m_bird->setPosition(BIRD_POS_X_FACTOR * visibleSize.width, center.y);
	m_bird->setContentSize(BIRD_SIZE);

	this->addChild(m_bird, BIRD_Z_INDEX);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::OnTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	schedule(schedule_selector(GameScene::GameUpdate));

	return true;
}

bool GameScene::OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_bird->Jump();
	return true;
}

void GameScene::GameUpdate(float dt)
{
	m_bird->Update(dt);
}