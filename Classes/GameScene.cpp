#include "GameScene.h"

USING_NS_CC;

const float WORLD_GRAVITY = 2400;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

	auto winSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(winSize * 0.5f);

	m_background.Init(this);
	m_bird.Init(this);
	m_interface.Init(this);

	auto mapEdge = PhysicsBody::createEdgeBox(winSize);
	auto edgeNode = Node::create();
	edgeNode->addComponent(mapEdge);
	edgeNode->setPosition(center);
	this->addChild(edgeNode);

	auto collideListener = EventListenerPhysicsContact::create();
	collideListener->onContactBegin = CC_CALLBACK_1(GameScene::IsBirdCollideAny, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collideListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::HandleTouch, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	schedule(schedule_selector(GameScene::Update));
	SetBehavoir(GameBehavior::START);

	return true;
}

void GameScene::Update(float elapsedTime)
{
	m_bird.Update(elapsedTime);
	m_interface.Update(m_bird.GetPosition());
	m_background.Update();

	if (m_interface.GetPointsCount() == POINTS_MAX)
	{
		SetBehavoir(GameBehavior::GAMEOVER);
	}
}

bool GameScene::HandleTouch(Touch* touch, Event* event)
{
	switch (m_behavior)
	{
	case GameBehavior::START:
		m_bird.Jump();
		SetBehavoir(GameBehavior::GAMEPLAY);
		break;

	case GameBehavior::GAMEPLAY:
		m_bird.Jump();
		break;

	case GameBehavior::GAMEOVER:
		SetBehavoir(GameBehavior::START);
		break;
	default:
		break;
	}

	return true;
}

void GameScene::SetBehavoir(GameBehavior newBehavior)
{
	m_behavior = newBehavior;

	switch (newBehavior)
	{
	case GameBehavior::START:
		m_bird.Reset();
		m_background.Reset();
		m_interface.Reset();
		break;

	case GameBehavior::GAMEPLAY:
		m_interface.SetGameplayUI();
		m_background.StartMotion();
		break;

	case GameBehavior::GAMEOVER:
		m_bird.Death();
		m_background.StopMotion();
		m_interface.SetGameoverUI();
		break;
	default:
		break;
	}
}

bool GameScene::IsBirdCollideAny(PhysicsContact& contact)
{
	auto bitMaskA = contact.getShapeA()->getCollisionBitmask();
	auto bitMaskB = contact.getShapeB()->getCollisionBitmask();

	if ((bitMaskA == MAP_BITMASK && bitMaskB == BIRD_BITMASK) ||
		(bitMaskA == BIRD_BITMASK && bitMaskB == MAP_BITMASK))
	{
		SetBehavoir(GameBehavior::GAMEOVER);
		return true;
	}
	else if ((bitMaskA == BIRD_BITMASK && bitMaskB == POINT_BITMASK) ||
			(bitMaskA == POINT_BITMASK && bitMaskB == BIRD_BITMASK))
	{
		m_interface.AddPoint();
		return false;
	}

	return false;
}