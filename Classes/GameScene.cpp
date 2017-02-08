#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//m_log.open("out.txt");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	m_background.Init(this);
	m_bird.Init(this);

	auto collideListener = EventListenerPhysicsContact::create();
	collideListener->onContactBegin = CC_CALLBACK_1(GameScene::IsBirdCollideAny, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collideListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::IsScreenTouched, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	schedule(schedule_selector(GameScene::GameUpdate));

	return true;
}

bool GameScene::IsBirdCollideAny(PhysicsContact& contact)
{
	if (IsCollideWithGround(contact))
	{
		m_bird.Reset();
		return true;
	}

	return false;
}

bool GameScene::IsCollideWithGround(cocos2d::PhysicsContact& contact)
{
	//m_log << "Check collide!";

	PhysicsBody* bodyA = contact.getShapeA()->getBody();
	PhysicsBody* bodyB = contact.getShapeB()->getBody();

	if ((bodyA->getContactTestBitmask() == BIRD_COLLISION_BITMASK && bodyB->getContactTestBitmask() == GROUND_COLLISION_BITMASK) ||
		(bodyA->getContactTestBitmask() == GROUND_COLLISION_BITMASK && bodyB->getContactTestBitmask() == BIRD_COLLISION_BITMASK))
	{
		return true;
	}

	return false;
}

bool GameScene::IsScreenTouched(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_bird.Jump();
	return true;
}

void GameScene::GameUpdate(float elapsedTime)
{
	m_bird.Update(elapsedTime);
	m_background.Update(elapsedTime);
}