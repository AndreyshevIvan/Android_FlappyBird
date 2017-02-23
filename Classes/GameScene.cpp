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
	collideListener->onContactBegin = CC_CALLBACK_1(GameScene::IsBirdCollideAny, this);

	auto pKeybackListener = EventListenerKeyboard::create();
	pKeybackListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithFixedPriority(touchListener, -1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collideListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pKeybackListener, this);
}

void GameScene::update(float elapsedTime)
{
	m_interface->Update(m_bird->GetPosition());

	float unreachableHeight = Director::getInstance()->getVisibleSize().height;
	float birdHeight = m_bird->GetPosition().y;

	if (m_interface->GetPointsCount() == POINTS_MAX ||
		birdHeight > unreachableHeight ||
		birdHeight < 0)
	{
		SetBehavior(m_gameoverBehavior);
	}
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	if (m_currBehavior == m_startBehavior)
	{
		SetBehavior(m_gameplayBehavior);
	}
	else if (m_currBehavior == m_gameoverBehavior && m_interface->IsGameoverTableAppeared())
	{
		SetBehavior(m_startBehavior);
	}

	m_currBehavior->Behavior(m_bird, m_map, m_interface);

	return true;
}

void GameScene::SetBehavior(GameBehavior* newBehavior)
{
	m_currBehavior = newBehavior;
	m_currBehavior->UpdateOptions(m_bird, m_map, m_interface);
}

bool GameScene::IsBirdCollideAny(PhysicsContact& contact)
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
		m_interface->AddPoint();
		return false;
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