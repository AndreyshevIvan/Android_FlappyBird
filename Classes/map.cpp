#include "map.h"

USING_NS_CC;


void GameMap::Init(Layer* layer)
{
	m_log.open("out.txt");
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
}

void GameMap::InitGround(Layer* layer)
{
	m_ground = Sprite::create("ground.png");
	m_ground->setAnchorPoint(Vec2(0, 0));
	m_ground->setPosition(GROUND_OFFSET * 0, 0);

	auto groundBody = PhysicsBody::createBox(m_ground->getContentSize());
	groundBody->setCollisionBitmask(2);
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

		const float MIN_PIPE_HEIGHT = visibleSize.height * LOWER_SCREEN_TUBE_THRESHOLD;
		const float MAX_PIPE_HEIGHT = visibleSize.height * UPPER_SCREEN_TUBE_THRESHOLD;
		const float PIPE_HEIGHT_RANGE = MAX_PIPE_HEIGHT - MIN_PIPE_HEIGHT;
		const float TOP_PIPE_HEIGHT = PIPE_HEIGHT_RANGE * CCRANDOM_0_1() + MIN_PIPE_HEIGHT;

		topPipeBody->setDynamic(false);
		bottomPipeBody->setDynamic(false);

		topPipeBody->setCollisionBitmask(TUBE_COLLISION_BITMASK);
		bottomPipeBody->setCollisionBitmask(TUBE_COLLISION_BITMASK);

		topPipeBody->setContactTestBitmask(true);
		bottomPipeBody->setContactTestBitmask(true);

		topPipe->setPhysicsBody(topPipeBody);
		bottomPipe->setPhysicsBody(bottomPipeBody);

		auto pipePosX = visibleSize.width + PIPE_WIDTH / 2.0f + TUBES_OFFSET * i;

		topPipe->setPosition(Point(pipePosX, TOP_PIPE_HEIGHT));
		bottomPipe->setPosition(Point(pipePosX, topPipe->getPositionY() - PIPE_GAP));

		m_tubes.push_back(topPipe);
		m_tubes.push_back(bottomPipe);

		layer->addChild(topPipe, TUBE_Z_INDEX);
		layer->addChild(bottomPipe, TUBE_Z_INDEX);
	}
}

void GameMap::Update(float elapsedTime)
{
	UpdateGround(elapsedTime);
	UpdateTubes(elapsedTime);
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
	const Vec2 restartOffset = Vec2(TUBES_OFFSET * TUBES_COUNT, 0);

	for (auto tube : m_tubes)
	{
		const Vec2 tubePos = tube->getPosition();

		if (tubePos.x + tube->getContentSize().width / 2.0f <= 0)
		{
			tube->setPosition(tubePos + restartOffset);
			m_log << tubePos.x << "\n";
		}

		Vec2 movement = Vec2(SPEED * elapsedTime, 0);
		tube->setPosition(tube->getPosition() - movement);
	}
}

cocos2d::Rect GameMap::GetGroundBox()
{
	return m_ground->getBoundingBox();
}