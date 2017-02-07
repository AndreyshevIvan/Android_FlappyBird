#include "bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

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

void Bird::Update(float dt)
{

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