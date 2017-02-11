#include "interface.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const int INTERFACE_Z_INDEX = 100;

const int FONT_POINTS_SIZE = 90;
const int FONST_SCORE_SIZE = 60;

const Vec2 GAMEOVER_UI_OFFSET = Vec2(0, 700);
const Vec2 SCORE_OFFSET = Vec2(238, 32);
const float GAMENAME_OFFSET_Y = 360;
const float GAMEOVER_OFFSET_Y = 360;
const float POINTS_OFFSET_Y = 512;

const int ACTION_MOVE_GAMEOVER_UI_TAG = 1;

const float GAMEOVER_INIT_DURATION = 0.8f;

void GameInterface::Init(Layer* layer)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	Point center = Point(winSize.width / 2.0f, winSize.height / 2.0f);

	m_points = Label::createWithTTF("", "fonts/FlappyBird.ttf", FONT_POINTS_SIZE);
	m_points->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	m_points->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_points->setPosition(Point(center.x, center.y + POINTS_OFFSET_Y));

	m_gameOver = Sprite::create("gameOver.png");
	m_gameOver->setPosition(Point(center.x, center.y + GAMEOVER_OFFSET_Y));

	m_scoreTab = Sprite::create("gameOverMenu.png");
	m_scoreTab->setPosition(center);

	m_score = Label::createWithTTF("", "fonts/FlappyBird.ttf", FONST_SCORE_SIZE);
	m_score->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	m_score->setAnchorPoint(Vec2(1, 0.5f));
	m_score->setPosition(center + SCORE_OFFSET);

	m_guide = Sprite::create("guide.png");
	m_guide->setPosition(center);

	m_gameName = Sprite::create("title.png");
	m_gameName->setPosition(Point(center.x, center.y + GAMENAME_OFFSET_Y));

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

	Point center = Director::getInstance()->getVisibleSize() * 0.5f;

	m_audio.Swooshing();
	m_score->setVisible(true);
	m_scoreTab->setVisible(true);
	m_gameOver->setVisible(true);

	auto moveElemets = MoveBy::create(GAMEOVER_INIT_DURATION, -GAMEOVER_UI_OFFSET);
	moveElemets->setTag(ACTION_MOVE_GAMEOVER_UI_TAG);
	auto easeCircle = EaseCircleActionOut::create(moveElemets->clone());

	m_score->runAction(easeCircle->clone());
	m_scoreTab->runAction(easeCircle->clone());
	m_gameOver->runAction(easeCircle->clone());
}

void GameInterface::ResetUI()
{
	Point center = Director::getInstance()->getVisibleSize() * 0.5f;

	m_points->setVisible(false);
	m_score->setVisible(false);
	m_scoreTab->setVisible(false);
	m_gameOver->setVisible(false);
	m_gameName->setVisible(false);
	m_guide->setVisible(false);

	m_score->stopAllActions();
	m_scoreTab->stopAllActions();
	m_gameOver->stopAllActions();

	m_score->setPositionY(center.y + SCORE_OFFSET.y + GAMEOVER_UI_OFFSET.y);
	m_scoreTab->setPositionY(center.y + GAMEOVER_UI_OFFSET.y);
	m_gameOver->setPositionY(center.y + GAMEOVER_OFFSET_Y + GAMEOVER_UI_OFFSET.y);
}

void GameInterface::Reset()
{
	SetStartUI();

	m_pointsCount = 0;
}

void GameInterface::Update(Vec2 const& birdPosition)
{
	m_points->setString(GetPointsStr());
	m_score->setString(GetPointsStr());
	UpdateIdleInterface(birdPosition);
}

bool GameInterface::IsGameoverInit()
{
	if (m_score->getNumberOfRunningActions() == 0)
	{
		return true;
	}

	return false;
}

std::string GameInterface::GetPointsStr()
{
	std::string pointsStr;
	std::stringstream stream;
	stream << m_pointsCount;
	pointsStr = stream.str();

	return pointsStr;
}

void GameInterface::AddPoint()
{
	m_audio.Point();
	m_pointsCount = (m_pointsCount - POINTS_MAX == 0) ? 0 : m_pointsCount + 1;
}

unsigned GameInterface::GetPointsCount()
{
	return m_pointsCount;
}

void GameInterface::UpdateIdleInterface(Vec2 const& birdPosition)
{
	auto guidePosX = m_guide->getPositionX();
	auto namePosX = m_gameName->getPositionX();

	m_guide->setPosition(Point(guidePosX, birdPosition.y));
	m_gameName->setPosition(Point(namePosX, birdPosition.y + GAMENAME_OFFSET_Y));
}