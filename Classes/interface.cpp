#include "interface.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void GameInterface::Init(Layer* layer)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(winSize.width / 2.0f, winSize.height / 2.0f);

	m_points = Label::createWithTTF("0", "fonts/FlappyBird.ttf", POINTS_FONT_SIZE);
	m_points->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	m_points->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_points->setPosition(Vec2(center.x, winSize.height * POINTS_POS_FACTOR));

	m_gameOver = Sprite::create("gameOver.png");
	m_gameOver->setPosition(Vec2(center.x, center.y + GAMEOVER_OFFSET));
	m_scoreTab = Sprite::create("gameOverMenu.png");
	m_scoreTab->setPosition(center);
	m_score = Label::createWithTTF("1337", "fonts/FlappyBird.ttf", SCORE_FONT_SIZE);
	m_score->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	m_score->setAnchorPoint(Vec2(1, 0.5f));
	m_score->setPosition(center + SCORE_OFFSET);

	m_guide = Sprite::create("guide.png");
	m_guide->setPosition(center);
	m_gameName = Sprite::create("title.png");
	m_gameName->setPosition(Vec2(center.x, center.y + GAME_NAME_OFFSET));
	
	layer->addChild(m_points, INTERFACE_Z_INDEX);
	layer->addChild(m_guide, INTERFACE_Z_INDEX);
	layer->addChild(m_gameName, INTERFACE_Z_INDEX);
	layer->addChild(m_gameOver, INTERFACE_Z_INDEX);
	layer->addChild(m_scoreTab, INTERFACE_Z_INDEX);
	layer->addChild(m_score, INTERFACE_Z_INDEX);
}

void GameInterface::SetStartUI()
{
	ResetUI();

	m_gameName->setVisible(true);
	m_guide->setVisible(true);
}

void GameInterface::SetGameplayUI()
{
	ResetUI();

	m_points->setVisible(true);
}

void GameInterface::SetGameoverUI()
{
	ResetUI();

	m_score->setString(std::to_string(m_pointsCount));

	m_score->setVisible(true);
	m_scoreTab->setVisible(true);
	m_gameOver->setVisible(true);
}

void GameInterface::ResetUI()
{
	m_points->setVisible(false);
	m_score->setVisible(false);
	m_scoreTab->setVisible(false);
	m_gameOver->setVisible(false);
	m_gameName->setVisible(false);
	m_guide->setVisible(false);
}

void GameInterface::Reset()
{
	SetStartUI();

	m_pointsCount = 0;
}

void GameInterface::Update(float elapsedTime, Vec2 const& birdPosition)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(winSize.width / 2.0f, winSize.height / 2.0f);

	m_pointsCount += 1;

	m_points->setString(std::to_string(m_pointsCount));

	UpdateIdleInterface(elapsedTime, birdPosition);
}

void GameInterface::AddPoint()
{
	if (m_pointsCount - POINTS_MAX == 0)
	{
		m_pointsCount = 0;
	}
	else
	{
		m_pointsCount++;
	}
}

unsigned GameInterface::GetPointsCount()
{
	return m_pointsCount;
}

void GameInterface::UpdateIdleInterface(float elapsedTime, Vec2 const& birdPosition)
{
	m_guide->setPosition(Vec2(m_guide->getPositionX(), birdPosition.y));
	m_gameName->setPosition(Vec2(m_gameName->getPosition().x, birdPosition.y + GAME_NAME_OFFSET));
}