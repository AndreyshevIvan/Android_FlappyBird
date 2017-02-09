#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_director = Director::getInstance();
	m_visibleSize = m_director->getVisibleSize();
	Vec2 origin = m_director->getVisibleOrigin();

	m_director = Director::getInstance();
	

	return true;
}

void GameOverScene::exitPause(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}