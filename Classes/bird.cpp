#include "bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


void Bird::Init(Layer* layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	m_body = Sprite::create("bird.png");
	const float bodyWidth = m_body->getContentSize().width / (float)BIRD_FRAMES;
	const float bodyHeight = m_body->getContentSize().height;
	m_body->setContentSize(Size(bodyWidth, bodyHeight));

	auto physBody = PhysicsBody::createCircle(m_body->getContentSize().height / 2.0f);
	physBody->setCollisionBitmask(1);
	physBody->setContactTestBitmask(true);
	physBody->setDynamic(false);
	m_body->setPhysicsBody(physBody);

	layer->addChild(m_body, BIRD_Z_INDEX);

	this->Reset();
}

void Bird::Update(float elapsedTime)
{
	if (m_status == BirdStatus::IDLE)
	{
		Idle(elapsedTime);
	}

	FlappingAnimate(elapsedTime);
	RotateBird(elapsedTime);
}

void Bird::Idle(float elapsedTime)
{
	const float PI = static_cast<float>(M_PI);

	m_idleAnimTime += elapsedTime;
	if (m_idleAnimTime >= 2 * PI)
	{
		m_idleAnimTime = 0;
	}

	Vec2 movement(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * m_idleAnimTime));
	m_body->setPosition(m_body->getPosition() - movement);
}

void Bird::Jump()
{
	m_status = BirdStatus::FLAPPING;
	m_body->getPhysicsBody()->setDynamic(true);
	m_body->getPhysicsBody()->setVelocity(Vec2(0, 500));
}

void Bird::FlappingAnimate(float elapsedTime)
{
	m_flappingAnimTime += FLAPPING_SPEED * elapsedTime;

	if (static_cast<int>(m_flappingAnimTime) > 2)
	{
		m_flappingAnimTime = 0;
	}

	int frameNumber = static_cast<int>(m_flappingAnimTime);
	float frameWidth = m_body->getContentSize().width;
	float frameHeight = m_body->getContentSize().height;

	cocos2d::Rect textureArea(frameNumber * frameWidth, 0, frameWidth, frameHeight);
	m_body->setTextureRect(textureArea);
}

PhysicsBody* Bird::GetBody()
{
	return m_body->getPhysicsBody();
}

void Bird::Reset()
{
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	m_status = BirdStatus::IDLE;
	m_idleAnimTime = 0;

	m_body->setRotation(0);
	m_body->setPosition(BIRD_POS_X_FACTOR * visibleSize.x, visibleSize.y / 2.0f);
}

void Bird::RotateBird(float elapsedTime)
{

}