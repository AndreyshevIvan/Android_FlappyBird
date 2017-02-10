#include "map.h"

USING_NS_CC;


void GameMap::Init(Layer* layer)
{
	Size visibleSize = layer->getContentSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	
	m_background = Sprite::create("background.png");
	m_background->setContentSize(visibleSize);
	m_background->setPosition(center);

	m_city = Sprite::create("city.png");
	m_city->setAnchorPoint(Vec2(0.5f, 0));
	m_city->setPosition(center.x, GROUND_HEIGHT);

	layer->addChild(m_background, SKY_Z_INDEX);
	layer->addChild(m_city, CITY_Z_INDEX);

	InitGround(layer);
	InitTubes(layer);
	InitPointsBodies(layer);

	Reset();
}

void GameMap::InitGround(Layer* layer)
{
	m_ground = Sprite::create("ground.png");
	m_ground->setAnchorPoint(Vec2(0, 0));
	m_ground->setPosition(GROUND_OFFSET * 0, 0);

	auto groundBody = PhysicsBody::createBox(m_ground->getContentSize());
	groundBody->setCollisionBitmask(1);
	groundBody->setContactTestBitmask(true);
	groundBody->setDynamic(false);
	m_ground->setPhysicsBody(groundBody);

	layer->addChild(m_ground, GROUND_Z_INDEX);
}

void GameMap::InitTubes(Layer* layer)
{
	Size visibleSize = layer->getContentSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	for (size_t i = 0; i != TUBES_COUNT; i++)
	{
		auto topPipe = Sprite::create("tubeTop.png");
		auto bottomPipe = Sprite::create("tubeBottom.png");
		topPipe->setAnchorPoint(cocos2d::Vec2(0.5, 0));
		bottomPipe->setAnchorPoint(cocos2d::Vec2(0.5, 1));

		const float PIPE_WIDTH = topPipe->getContentSize().width;

		auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
		auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

		topPipeBody->setDynamic(false);
		bottomPipeBody->setDynamic(false);

		topPipeBody->setCollisionBitmask(TUBE_COLLISION_BITMASK);
		bottomPipeBody->setCollisionBitmask(TUBE_COLLISION_BITMASK);

		topPipeBody->setContactTestBitmask(true);
		bottomPipeBody->setContactTestBitmask(true);

		topPipe->setPhysicsBody(topPipeBody);
		bottomPipe->setPhysicsBody(bottomPipeBody);

		m_tubes.push_back(topPipe);
		m_tubes.push_back(bottomPipe);

		layer->addChild(topPipe, TUBE_Z_INDEX);
		layer->addChild(bottomPipe, TUBE_Z_INDEX);
	}
}

void GameMap::InitPointsBodies(Layer* layer)
{
	Size winSize = layer->getContentSize();
	
	for (size_t i = 0; i <= m_tubes.size(); i += 2)
	{
		auto body = PhysicsBody::createBox(Size(1, winSize.height));
		body->setDynamic(false);
		body->setCollisionBitmask(5);
		body->setContactTestBitmask(true);
		auto node = Node::create();
		node->addComponent(body);
		m_pointsBodies.push_back(body);

		layer->addChild(node);
	}
}

void GameMap::Update(float elapsedTime)
{
	UpdateGround(elapsedTime);
	UpdateTubes(elapsedTime);
	UpdatePointsBodies();
}

void GameMap::UpdateGround(float elapsedTime)
{
	Vec2 movement = Vec2(-SPEED * elapsedTime, 0);

	const float groundPosition = m_ground->getPosition().x;

	if (groundPosition <= -m_ground->getContentSize().width / 2.0f)
	{
		m_ground->setPosition(Point::ZERO);
	}

	m_ground->setPosition(m_ground->getPosition() + movement);
}

void GameMap::UpdateTubes(float elapsedTime)
{
	for (size_t tubeNum = 0; tubeNum != m_tubes.size(); tubeNum += 2)
	{
		auto topTube = m_tubes[tubeNum];
		auto bottomTube = m_tubes[tubeNum + 1];

		auto tubePos = m_tubes[tubeNum]->getPosition();

		if (tubePos.x + topTube->getContentSize().width / 2.0f <= 0)
		{
			ResetTubes(topTube, bottomTube);
		}

		Vec2 movement = Vec2(SPEED * elapsedTime, 0);
		topTube->setPosition(topTube->getPosition() - movement);
		bottomTube->setPosition(bottomTube->getPosition() - movement);
	}
}

void GameMap::UpdatePointsBodies()
{
	for (size_t i = 0; i != m_tubes.size(); i += 2)
	{
		m_pointsBodies[i / 2]->setPositionOffset(m_tubes[i]->getPosition());
	}
}

cocos2d::PhysicsBody* GameMap::GetGroundBody()
{
	return m_ground->getPhysicsBody();
}

std::vector<cocos2d::PhysicsBody*> GameMap::GetTubesBodies()
{
	std::vector<cocos2d::PhysicsBody*> bodies;

	for (auto tube : m_tubes)
	{
		bodies.push_back(tube->getPhysicsBody());
	}

	return bodies;
}

std::vector<cocos2d::PhysicsBody*> GameMap::GetPointsBodies()
{
	return m_pointsBodies;
}

void GameMap::Reset()
{
	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const float halfTubeWidth = m_tubes.front()->getContentSize().width / 2.0f;
	const float instantPosX = visibleSize.width + halfTubeWidth + TUBES_START_OFFSET;

	for (size_t tubeNum = 0; tubeNum != m_tubes.size(); tubeNum += 2)
	{
		const float pairOffset = TUBES_BETWEEN_OFFSET * tubeNum / 2.0f;

		auto topTube = m_tubes[tubeNum];
		auto bottomTube = m_tubes[tubeNum + 1];

		topTube->setPosition(Point(instantPosX + pairOffset, this->GetHeight()));
		bottomTube->setPosition(Point(instantPosX + pairOffset, topTube->getPositionY() - TUBE_GAP));
	}

	UpdatePointsBodies();
}

float GameMap::GetHeight()
{
	const Size winSize = Director::getInstance()->getVisibleSize();
	const float minHeight = winSize.height * LOWER_SCREEN_TUBE_THRESHOLD;
	const float maxHeight = winSize.height * UPPER_SCREEN_TUBE_THRESHOLD;
	const float heightRange = maxHeight - minHeight;

	return heightRange * CCRANDOM_0_1() + minHeight;
}

void GameMap::ResetTubes(Sprite* topTube, Sprite* bottomTube)
{
	const float oldPosX = topTube->getPosition().x;
	const float newTopHeight = this->GetHeight();

	const Vec2 newTopPos = Vec2(TUBE_RESET_OFFSET + oldPosX, newTopHeight);
	const Vec2 newbottomPos = Vec2(TUBE_RESET_OFFSET + oldPosX, newTopHeight - TUBE_GAP);

	topTube->setPosition(newTopPos);
	bottomTube->setPosition(newbottomPos);
}