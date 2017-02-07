#include "background.h"

USING_NS_CC;


void Background::Init(Layer* layer)
{
	Size visibleSize = layer->getContentSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	auto bgSprite = Sprite::create("background.png");
	bgSprite->setPosition(center);

	auto citySprite = Sprite::create("city.png");
	citySprite->setAnchorPoint(Vec2(0.5f, 0));
	citySprite->setPosition(center.x, GROUND_HEIGHT);

	layer->addChild(bgSprite, SKY_Z_INDEX);
	layer->addChild(citySprite, CITY_Z_INDEX);

	InitGrounds(layer);
}

void Background::InitGrounds(Layer* layer)
{
	//for (size_t i = 0; i != 1; i++)
	//{
		auto ground = Sprite::create("ground.png");
		ground->setAnchorPoint(Vec2(0, 0));
		ground->setPosition(GROUND_OFFSET * 0, 0);

		m_grounds.push_back(ground);
		layer->addChild(ground, GROUND_Z_INDEX);
//	}
}

void Background::Update(float elapsedTime)
{
	//UpdateGround(elapsedTime);
	//UpdateTubes(elapsedTime);
}

void Background::UpdateGround(float elapsedTime)
{
	Vec2 movement(-SPEED * elapsedTime, 0);

	for (auto& ground : m_grounds)
	{
		const Vec2 position = ground->getPosition();

		if (position.x + ground->getContentSize().width <= 0)
		{
			ground->setPosition(GROUND_OFFSET * GROUNDS_COUNT + position.x, position.y);
		}

		ground->setPosition(ground->getPosition() + movement);
	}
}