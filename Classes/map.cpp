#include "map.h"

USING_NS_CC;

const int SKY_Z_INDEX = 0;
const int CITY_Z_INDEX = 1;
const int TUBE_Z_INDEX = 3;
const int GROUND_Z_INDEX = 4;

const int ACTION_MOVE_TAG = 1;

const float CITY_OFFSET_X = 105;
const float TUBES_INTERNAL_OFFSET_X = 450;
const float TUBES_START_OFFSET_X = 256;

const float TUBE_GAP = 300;
const float LOWER_SCREEN_TUBE_THRESHOLD = 0.40f;
const float UPPER_SCREEN_TUBE_THRESHOLD = 0.90f;

const float TUBES_SPEED = 350;

void GameMap::Init(Layer* layer)
{
	Size winSize = layer->getContentSize();
	Vec2 center = Vec2(winSize * 0.5f);

	m_background = Sprite::create("textures/background.png");
	m_background->setContentSize(winSize);
	m_background->setPosition(center);

	m_city = Sprite::create("textures/city.png");
	m_city->setAnchorPoint(Vec2(0.5f, 0));
	m_city->setPosition(center.x, CITY_OFFSET_X);

	layer->addChild(m_background, SKY_Z_INDEX);
	layer->addChild(m_city, CITY_Z_INDEX);

	auto tubesCount = static_cast<int>(winSize.width / TUBES_INTERNAL_OFFSET_X) + 2;

	InitGround(layer);
	InitTubes(layer, tubesCount);
	InitPointsBodies(layer);

	Reset();
}

void GameMap::InitGround(Layer* layer)
{
	m_ground = Sprite::create("textures/ground.png");
	m_ground->setAnchorPoint(Vec2(0, 0));
	m_ground->setPosition(Point::ZERO);

	auto groundBody = PhysicsBody::createBox(m_ground->getContentSize());
	groundBody->setDynamic(false);
	groundBody->setCollisionBitmask(MAP_BITMASK);
	groundBody->setContactTestBitmask(true);
	m_ground->setPhysicsBody(groundBody);

	layer->addChild(m_ground, GROUND_Z_INDEX);
}

void GameMap::InitTubes(Layer* layer, int tubesCount)
{
	Size winSize = layer->getContentSize();
	Vec2 center = Vec2(winSize * 0.5f);

	for (size_t i = 0; i != tubesCount; i++)
	{
		auto topTube = Sprite::create("textures/tubeTop.png");
		topTube->setAnchorPoint(Vec2(0.5, 0));
		auto topTubeBody = PhysicsBody::createBox(topTube->getContentSize());
		topTubeBody->setDynamic(false);
		topTubeBody->setCollisionBitmask(MAP_BITMASK);
		topTubeBody->setContactTestBitmask(true);
		topTube->setPhysicsBody(topTubeBody);

		auto bottomTube = Sprite::create("textures/tubeBottom.png");
		bottomTube->setAnchorPoint(Vec2(0.5, 1));
		auto bottomTubeBody = PhysicsBody::createBox(bottomTube->getContentSize());
		bottomTubeBody->setDynamic(false);
		bottomTubeBody->setCollisionBitmask(MAP_BITMASK);
		bottomTubeBody->setContactTestBitmask(true);
		bottomTube->setPhysicsBody(bottomTubeBody);

		m_tubes.push_back(topTube);
		m_tubes.push_back(bottomTube);

		layer->addChild(topTube, TUBE_Z_INDEX);
		layer->addChild(bottomTube, TUBE_Z_INDEX);
	}
}

void GameMap::InitPointsBodies(Layer* layer)
{
	Size winSize = layer->getContentSize();
	
	for (size_t i = 0; i <= m_tubes.size(); i += 2)
	{
		auto body = PhysicsBody::createBox(Size(1, winSize.height));
		body->setDynamic(false);
		body->setCollisionBitmask(POINT_BITMASK);
		body->setContactTestBitmask(true);
		auto node = Node::create();
		node->addComponent(body);
		m_pointsBodies.push_back(body);

		layer->addChild(node);
	}
}

void GameMap::StartMotion()
{
	auto movement = Vec2(-TUBES_SPEED, 0);
	for (auto tube : m_tubes)
	{
		tube->stopAllActions();
		auto action = RepeatForever::create(MoveBy::create(1, movement));
		action->setTag(ACTION_MOVE_TAG);
		tube->runAction(action);
	}
	m_ground->stopAllActions();
	auto action = RepeatForever::create(MoveBy::create(1, movement));
	action->setTag(ACTION_MOVE_TAG);
	m_ground->runAction(action);
}

void GameMap::StopMotion()
{
	for (auto tube : m_tubes)
		tube->stopAllActions();
	m_ground->stopAllActions();
}

void GameMap::Update()
{
	UpdateGround();
	UpdateTubes();
	UpdatePointsBodies();
}

void GameMap::UpdateGround()
{
	const float groundPosition = m_ground->getPosition().x;
	const float finalPosition = -m_ground->getContentSize().width / 2.0f;

	if (groundPosition <= finalPosition)
	{
		m_ground->setPosition(Point::ZERO);
	}
}

void GameMap::UpdateTubes()
{
	for (size_t tubeNum = 0; tubeNum != m_tubes.size(); tubeNum += 2)
	{
		auto topTube = m_tubes[tubeNum];
		auto bottomTube = m_tubes[tubeNum + 1];

		auto tubePos = topTube->getPosition();

		if (tubePos.x + topTube->getContentSize().width / 2.0f <= 0)
		{
			ResetTubes(topTube, bottomTube);
		}
	}
}

void GameMap::UpdatePointsBodies()
{
	for (size_t i = 0; i != m_tubes.size(); i += 2)
	{
		m_pointsBodies[i / 2]->setPositionOffset(m_tubes[i]->getPosition());
	}
}

PhysicsBody* GameMap::GetGroundBody()
{
	return m_ground->getPhysicsBody();
}

std::vector<PhysicsBody*> GameMap::GetTubesBodies()
{
	std::vector<PhysicsBody*> bodies;

	for (auto tube : m_tubes)
	{
		bodies.push_back(tube->getPhysicsBody());
	}

	return bodies;
}

std::vector<PhysicsBody*> GameMap::GetPointsBodies()
{
	return m_pointsBodies;
}

void GameMap::Reset()
{
	const Size winSize = Director::getInstance()->getVisibleSize();
	const float halfTubeWidth = m_tubes.front()->getContentSize().width / 2.0f;
	const float instantPosX = winSize.width + halfTubeWidth + TUBES_START_OFFSET_X;

	for (size_t i = 0; i != m_tubes.size(); i += 2)
	{
		const float pairOffset = TUBES_INTERNAL_OFFSET_X * i / 2.0f;

		auto topTube = m_tubes[i];
		auto bottomTube = m_tubes[i + 1];

		topTube->setPosition(Point(instantPosX + pairOffset, this->GetHeight()));
		bottomTube->setPosition(Point(instantPosX + pairOffset, topTube->getPositionY() - TUBE_GAP));
	}

	UpdatePointsBodies();
}

float GameMap::GetHeight()
{
	const Size winSize = Director::getInstance()->getVisibleSize();
	const float maxHeight = winSize.height * UPPER_SCREEN_TUBE_THRESHOLD;
	const float minHeight = winSize.height * LOWER_SCREEN_TUBE_THRESHOLD;
	const float heightRange = maxHeight - minHeight;

	return heightRange * CCRANDOM_0_1() + minHeight;
}

void GameMap::ResetTubes(Sprite* topTube, Sprite* bottomTube)
{
	const float oldPosX = topTube->getPosition().x;
	const float newTopHeight = this->GetHeight();
	const float resetOffsetX = (m_tubes.size() / 2.0f) * TUBES_INTERNAL_OFFSET_X;

	const Vec2 newTopPos = Vec2(resetOffsetX + oldPosX, newTopHeight);
	const Vec2 newbottomPos = Vec2(resetOffsetX + oldPosX, newTopHeight - TUBE_GAP);

	topTube->setPosition(newTopPos);
	bottomTube->setPosition(newbottomPos);
}