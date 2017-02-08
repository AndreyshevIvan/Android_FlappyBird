#include "bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


void Bird::Init(Layer* layer)
{
	//m_log.open("out.txt");

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
	//m_log << m_body->getRotation() << "\n";
	if (m_status == BirdStatus::IDLE)
	{
		Idle(elapsedTime);
	}
	else if (m_status == BirdStatus::FLAPPING)
	{
		UpdateGravity(elapsedTime);
	}

	FlappingAnimate(elapsedTime);
}

void Bird::UpdateGravity(float elapsedTime)
{
	Vec2 movement = Vec2(0, m_speed);

	m_speed = m_speed + G * elapsedTime;
	movement.y = m_speed * elapsedTime;
	movement.y *= IMPULSE;

	if (m_body->getPosition().y > BIRD_MAX_HEIGHT)
	{
		m_body->setPosition(m_body->getPosition().x, BIRD_MAX_HEIGHT);
	}

	m_body->setPosition(m_body->getPosition() - movement);

	RotateBird(elapsedTime, movement);
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
	m_speed = -BIRD_JUMP_SPEED;
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
	m_log << "===RESET===\n";
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	m_status = BirdStatus::IDLE;
	m_speed = 0;
	m_idleAnimTime = 0;
	m_body->setRotation(0);

	m_body->setPosition(BIRD_POS_X_FACTOR * visibleSize.x, visibleSize.y / 2.0f);
}

void Bird::RotateBird(float elapsedTime, Vec2 const& movement)
{
	if (movement.y < 0)
	{
		m_body->setRotation(UP_ROT_ANGALE);
	}
	else if (m_body->getRotation() != DOWN_ROT_ANGLE)
	{
		auto rotation = DOWN_ROT_SPEED * elapsedTime;
		m_body->setRotation(m_body->getRotation() + rotation);
		const float bodyRotation = m_body->getRotation();

		if (bodyRotation < 360 + UP_ROT_ANGALE && bodyRotation > DOWN_ROT_ANGLE)
		{
			m_body->setRotation(DOWN_ROT_ANGLE);
		}
	}
}