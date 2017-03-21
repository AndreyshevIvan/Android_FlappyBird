#include "GameScene.h"

USING_NS_CC;

const float WORLD_GRAVITY = 2400;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, -WORLD_GRAVITY));

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

	this->isKeypadEnabled();

	auto winSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(winSize * 0.5f);

	m_bird = new Bird();
	m_map = new GameMap();
	m_interface = new GameInterface();

	m_startBehavior = new StartGameBehavior();
	m_gameplayBehavior = new GameplayBehavior();
	m_gameoverBehavior = new GameoverBehavior();

	m_startBehavior->Init(m_bird, m_map, m_interface);
	m_gameplayBehavior->Init(m_bird, m_map, m_interface);
	m_gameoverBehavior->Init(m_bird, m_map, m_interface);

	AddListeners();
	scheduleUpdate();

	SetBehavior(m_startBehavior);

	this->addChild(m_map);
	this->addChild(m_bird);
	this->addChild(m_interface);

	return true;
}

void GameScene::AddListeners()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
		return onTouchBegan(touch, event);
	};

	auto collideListener = EventListenerPhysicsContact::create();
	collideListener->onContactBegin = CC_CALLBACK_1(GameScene::IsBirdContactWithAny, this);

	auto pKeybackListener = EventListenerKeyboard::create();
	pKeybackListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithFixedPriority(touchListener, -1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collideListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pKeybackListener, this);
}

void GameScene::update(float elapsedTime)
{
	m_currBehavior->Update(elapsedTime);
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	m_currBehavior->OnTouchEvent();

	if (m_currBehavior == m_startBehavior)
	{
		SetBehavior(m_gameplayBehavior);
	}
	else if (m_currBehavior == m_gameoverBehavior && m_currBehavior->IsOnTouchChange())
	{
		SetBehavior(m_startBehavior);
	}

	return true;
}

void GameScene::SetBehavior(GameBehavior* newBehavior)
{
	m_currBehavior = newBehavior;
	m_currBehavior->Start();
}

bool GameScene::IsBirdContactWithAny(PhysicsContact& contact)
{
	auto bitMaskA = contact.getShapeA()->getCollisionBitmask();
	auto bitMaskB = contact.getShapeB()->getCollisionBitmask();

	if ((bitMaskA == MAP_BITMASK && bitMaskB == BIRD_BITMASK) ||
		(bitMaskA == BIRD_BITMASK && bitMaskB == MAP_BITMASK))
	{
		SetBehavior(m_gameoverBehavior);
		return true;
	}
	else if ((bitMaskA == BIRD_BITMASK && bitMaskB == POINT_BITMASK) ||
		(bitMaskA == POINT_BITMASK && bitMaskB == BIRD_BITMASK))
	{
		m_currBehavior->CollideWithPointEvent();
	}

	return false;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();
	}
}