#include "GameScene.h"

USING_NS_CC;

const float WORLD_GRAVITY = 2400;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(3);
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

	m_bird->init();
	m_map->init();
	m_interface->init();

	AddListeners();
	scheduleUpdate();

	SetNewBehavior(BehaviorType::START);

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
		SetNewBehavior(BehaviorType::GAMEOVER);
	}
}


bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	PlayBehavior(m_behavior);
	return true;
}

void GameScene::ChangeBehavior(BehaviorType const& newBehavior)
{
	m_behavior = newBehavior;
}

void GameScene::SetStartBehaviorOptions()
{
	m_bird->Reset();
	m_map->Reset();
	m_interface->Reset();
}

void GameScene::SetGameplayBehaviorOptions()
{
	m_interface->SetGameplayUI();
	m_map->StartMotion();
	m_bird->StartFlapping();
}

void GameScene::SetGameoverBehaviorOptions()
{
	m_interface->SetGameoverUI();
	m_bird->Death();
	m_map->StopMotion();
}

void GameScene::StartBehavior()
{
	SetNewBehavior(BehaviorType::GAMEPLAY);
}

void GameScene::GameplayBehavior()
{
	m_bird->Jump();
}

void GameScene::GameoverBehavior()
{
	if (m_interface->IsGameoverTableAppeared())
	{
		SetNewBehavior(BehaviorType::START);
	}
}

/*
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	switch (m_behavior)
	{
	case BehaviorType::GAMEPLAY:
		m_bird->Jump();
		break;

	case BehaviorType::START:
		SetNewBehavior(BehaviorType::GAMEPLAY);
		break;

	case BehaviorType::GAMEOVER:
		if (m_interface->IsGameoverTableAppeared())
		{
			SetNewBehavior(BehaviorType::START);
		}
		break;
	default:
		break;
	}

	return true;
}

void GameScene::SetBehavoir(BehaviorType newBehavior)
{

	switch (newBehavior)
	{
	case BehaviorType::START:
		m_bird->Reset();
		m_map->Reset();
		m_interface->Reset();
		break;

	case BehaviorType::GAMEPLAY:
		m_interface->SetGameplayUI();
		m_map->StartMotion();
		m_bird->StartFlapping();
		break;

	case BehaviorType::GAMEOVER:
		m_interface->SetGameoverUI();
		m_bird->Death();
		m_map->StopMotion();
		break;
	default:
		break;
	}
}
*/

bool GameScene::IsBirdCollideAny(PhysicsContact& contact)
{
	auto bitMaskA = contact.getShapeA()->getCollisionBitmask();
	auto bitMaskB = contact.getShapeB()->getCollisionBitmask();

	if ((bitMaskA == MAP_BITMASK && bitMaskB == BIRD_BITMASK) ||
		(bitMaskA == BIRD_BITMASK && bitMaskB == MAP_BITMASK))
	{
		SetNewBehavior(BehaviorType::GAMEOVER);
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