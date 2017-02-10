#include "bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const int BIRD_Z_INDEX = 10;
const int BIRD_FRAMES = 4;
const float BIRD_ANIMATE_FPS = 10;

const float BIRD_POS_FACTOR_X = 0.2f;
const float BIRD_JUMP_VELOCITY = 1000;

const float UP_ROT_ANGALE = -50;
const float DOWN_ROT_ANGLE = 90;
const float DOWN_ROT_SPEED = 280;

void Bird::Init(Layer* layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point center = Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	m_body = Sprite::create("bird.png");
	const float bodyWidth = m_body->getContentSize().width / static_cast<float>(BIRD_FRAMES);
	const float bodyHeight = m_body->getContentSize().height;
	m_body->setContentSize(Size(bodyWidth, bodyHeight));

	auto physBody = PhysicsBody::createCircle(bodyHeight / 2.0f);
	physBody->setCollisionBitmask(BIRD_BITMASK);
	physBody->setContactTestBitmask(true);
	physBody->setRotationEnable(false);
	m_body->setPhysicsBody(physBody);

	Reset();

	layer->addChild(m_body, BIRD_Z_INDEX);
}

void Bird::Update(float elapsedTime)
{
	if (m_status == BirdStatus::IDLE)
	{
		Idle(elapsedTime);
	}
	else if (m_status == BirdStatus::FLAPPING)
	{
		RotateBird(elapsedTime);
	}

	if (m_status != BirdStatus::DEAD)
	{
		FlappingAnimate(elapsedTime);
	}
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
	m_body->setPosition(GetPosition() - movement);
}

void Bird::Jump()
{
	m_status = BirdStatus::FLAPPING;
	m_body->getPhysicsBody()->setGravityEnable(true);
	m_body->getPhysicsBody()->setVelocity(Vec2(0, BIRD_JUMP_VELOCITY));
}

void Bird::Death()
{
	m_status = BirdStatus::DEAD;

	float frameWidth = m_body->getContentSize().width;
	float frameHeight = m_body->getContentSize().height;
	Rect textureArea((BIRD_FRAMES - 1) * frameWidth, 0, frameWidth, frameHeight);
	m_body->setTextureRect(textureArea);

	m_body->getPhysicsBody()->setGravityEnable(false);
	m_body->getPhysicsBody()->onExit();
}

void Bird::FlappingAnimate(float elapsedTime)
{
	m_flappingAnimTime += elapsedTime;

	float frameWidth = m_body->getContentSize().width;
	float frameHeight = m_body->getContentSize().height;
	int currFrame = m_body->getTextureRect().getMinX() / frameWidth;

	if (m_flappingAnimTime >= 1 / BIRD_ANIMATE_FPS)
	{
		m_flappingAnimTime = 0;
		currFrame++;

		if (currFrame == BIRD_FRAMES - 1)
		{
			currFrame = 0;
		}

		Rect textureArea(currFrame * frameWidth, 0, frameWidth, frameHeight);
		m_body->setTextureRect(textureArea);
	}
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

	ResetTexture();
	m_body->setRotation(0);
	m_body->getPhysicsBody()->setGravityEnable(false);
	m_body->getPhysicsBody()->setVelocity(Vec2::ZERO);
	m_body->getPhysicsBody()->onEnter();
	m_body->setPosition(visibleSize.x * BIRD_POS_FACTOR_X, visibleSize.y / 2.0f);
}

void Bird::ResetTexture()
{
	float frameWidth = m_body->getContentSize().width;
	float frameHeight = m_body->getContentSize().height;
	Rect textureArea(0, 0, frameWidth, frameHeight);
	m_body->setTextureRect(textureArea);
}

void Bird::RotateBird(float elapsedTime)
{
	if (m_body->getPhysicsBody()->getVelocity().y > 0)
	{
		m_body->setRotation(UP_ROT_ANGALE);
	}
	else if (m_body->getRotation() <= DOWN_ROT_ANGLE)
	{
		const float rotation = DOWN_ROT_SPEED * elapsedTime;
		m_body->setRotation(m_body->getRotation() + rotation);
	}
}

Point Bird::GetPosition()
{
	return m_body->getPosition();
}