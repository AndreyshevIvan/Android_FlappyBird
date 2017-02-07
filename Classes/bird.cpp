#include "bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Bird::Bird()
{
	m_status = BirdStatus::FLAPPING;
	m_speed = 0;
	m_idleAnimTime = 0;
}

Bird* Bird::CreateWithFileName(char* fileName)
{
	auto sprite = new Bird;
	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Bird::Update(float elapsedTime)
{
	if (m_status == BirdStatus::IDLE)
	{
		Idle(elapsedTime);
	}
	else if (m_status == BirdStatus::FLAPPING)
	{
		UpdateGravity(elapsedTime);
	}

	//FlappingAnimate(elapsedTime);
}

void Bird::UpdateGravity(float elapsedTime)
{
	Vec2 movement = Vec2(0, m_speed);

	m_speed = m_speed + G * elapsedTime;
	movement.y = m_speed * elapsedTime;
	movement.y *= IMPULSE;

	if (this->getPosition().y > BIRD_MAX_HEIGHT)
	{
		this->setPosition(this->getPosition().x, BIRD_MAX_HEIGHT);
	}

	this->setPosition(this->getPosition() - movement);

	this->RotateBird(elapsedTime, movement);
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
	this->setPosition(this->getPosition() - movement);
}

void Bird::Jump()
{
	m_status = BirdStatus::FLAPPING;
	m_speed = -BIRD_JUMP_SPEED;
}

void Bird::Reset()
{

}

void Bird::SetStartSpeed()
{

}

void Bird::SetParams(float tos)
{

}

cocos2d::Rect Bird::TubeCollisionBox()
{
	return this->getBoundingBox();
}

void Bird::RotateBird(float elapsedTime, Vec2 const& movement)
{
	if (movement.y < 0)
	{
		this->setRotation(UP_ROT_ANGALE);
	}
	else if (this->getRotation() != DOWN_ROT_ANGLE)
	{
		auto rotation = DOWN_ROT_SPEED * elapsedTime;
		this->setRotation(this->getRotation() + rotation);
		const float bodyRotation = this->getRotation();

		if (bodyRotation < 360 + UP_ROT_ANGALE && bodyRotation > DOWN_ROT_ANGLE)
		{
			this->setRotation(DOWN_ROT_ANGLE);
		}
	}
}