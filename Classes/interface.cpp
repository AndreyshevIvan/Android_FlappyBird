#include "interface.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const int INTERFACE_Z_INDEX = 100;

const int FONT_POINTS_SIZE = 90;
const int FONST_SCORE_SIZE = 60;

const Vec2 SCORE_OFFSET = Vec2(238, 32);
const Vec2 SCORE_BEST_OFFSET = Vec2(238, -78);
const Vec2 MEDAL_OFFSET = Vec2(-172, -19);
const Vec2 NEWTAB_OFFSET = Vec2(115, -21);
const float GAMENAME_OFFSET_Y = 360;
const float GAMEOVER_OFFSET_Y = 360;
const float POINTS_OFFSET_Y = 512;

const int ACTION_MOVE_GAMEOVER_UI_TAG = 1;

const float GAMEOVER_INIT_DURATION = 0.8f;

const int MEDALS_COUNT = 4;

const char* HIGHTSCORE_KEY = "FB_BY_IVAN_HIGHTSCORE";

void GameInterface::Init(Layer* layer)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	Point center = Point(winSize.width / 2.0f, winSize.height / 2.0f);

	m_points = Label::createWithTTF("", "fonts/FlappyBird.ttf", FONT_POINTS_SIZE);
	m_points->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	m_points->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_points->setPosition(Point(center.x, center.y + POINTS_OFFSET_Y));

	m_gameOver = Sprite::create("textures/gameOver.png");
	m_gameOver->setPosition(Point(center.x, center.y + GAMEOVER_OFFSET_Y));

	m_scoreTab = Sprite::create("textures/gameOverMenu.png");
	m_scoreTab->setPosition(center);

	m_score = Label::createWithTTF("", "fonts/FlappyBird.ttf", FONST_SCORE_SIZE);
	m_score->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	m_score->setAnchorPoint(Vec2(1, 0.5f));
	m_score->setPosition(center + SCORE_OFFSET);

	m_bestScore = Label::createWithTTF("1337", "fonts/FlappyBird.ttf", FONST_SCORE_SIZE);
	m_bestScore->enableOutline(FONT_OUTLINE_COLOR, FONT_OUTLINE_THICKNESS);
	m_bestScore->setAnchorPoint(Vec2(1, 0.5f));
	m_bestScore->setPosition(center + SCORE_BEST_OFFSET);

	m_guide = Sprite::create("textures/guide.png");
	m_guide->setPosition(center);

	m_gameName = Sprite::create("textures/title.png");
	m_gameName->setPosition(Point(center.x, center.y + GAMENAME_OFFSET_Y));

	m_medal = Sprite::create("textures/medals.png");
	const float medalWidth = m_medal->getContentSize().width / MEDALS_COUNT;
	const float medalHeight = m_medal->getContentSize().height;
	m_medal->setContentSize(Size(medalWidth, medalHeight));
	m_medal->setPosition(center + MEDAL_OFFSET);
	m_medal->setTextureRect(Rect(0, 0, medalWidth, medalHeight));

	m_newHighScoreTab = Sprite::create("textures/newScore.png");
	m_newHighScoreTab->setPosition(center + NEWTAB_OFFSET);

	UserDefault* memory = UserDefault::getInstance();
	auto highScore = memory->getIntegerForKey(HIGHTSCORE_KEY, 0);
	memory->flush();

	layer->addChild(m_points, INTERFACE_Z_INDEX);
	layer->addChild(m_guide, INTERFACE_Z_INDEX);
	layer->addChild(m_gameName, INTERFACE_Z_INDEX);
	layer->addChild(m_gameOver, INTERFACE_Z_INDEX);
	layer->addChild(m_scoreTab, INTERFACE_Z_INDEX);
	layer->addChild(m_score, INTERFACE_Z_INDEX);
	layer->addChild(m_bestScore, INTERFACE_Z_INDEX);
	layer->addChild(m_newHighScoreTab, INTERFACE_Z_INDEX);
	layer->addChild(m_medal, INTERFACE_Z_INDEX);
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

	SetMedal();
	m_audio.Swooshing();
	m_score->setVisible(true);
	m_scoreTab->setVisible(true);
	m_gameOver->setVisible(true);
	m_bestScore->setVisible(true);
	if (IsScoreNew())
	{
		m_newHighScoreTab->setVisible(true);
		SetNewHightScore();
	}

	auto moveElemets = MoveBy::create(GAMEOVER_INIT_DURATION, Vec2(0, -center.y));
	moveElemets->setTag(ACTION_MOVE_GAMEOVER_UI_TAG);
	auto easeCircle = EaseCircleActionOut::create(moveElemets->clone());

	m_score->runAction(easeCircle->clone());
	m_bestScore->runAction(easeCircle->clone());
	m_scoreTab->runAction(easeCircle->clone());
	m_gameOver->runAction(easeCircle->clone());
	m_medal->runAction(easeCircle->clone());
	m_newHighScoreTab->runAction(easeCircle->clone());

	m_score->setString(PointsToStr(m_pointsCount));
	m_bestScore->setString(GetHighScoreStr());
}

void GameInterface::ResetUI()
{
	Point center = Director::getInstance()->getVisibleSize() * 0.5f;

	m_points->setVisible(false);

	m_score->setVisible(false);
	m_scoreTab->setVisible(false);
	m_gameOver->setVisible(false);
	m_medal->setVisible(false);
	m_bestScore->setVisible(false);
	m_newHighScoreTab->setVisible(false);

	m_gameName->setVisible(false);
	m_guide->setVisible(false);

	m_score->stopAllActions();
	m_scoreTab->stopAllActions();
	m_gameOver->stopAllActions();

	m_score->setPositionY(center.y + SCORE_OFFSET.y + center.y);
	m_bestScore->setPositionY(center.y + SCORE_BEST_OFFSET.y + center.y);
	m_scoreTab->setPositionY(center.y + center.y);
	m_gameOver->setPositionY(center.y + GAMEOVER_OFFSET_Y + center.y);
	m_medal->setPositionY(center.y + MEDAL_OFFSET.y + center.y);
	m_newHighScoreTab->setPositionY(center.y + NEWTAB_OFFSET.y + center.y);
}

void GameInterface::SetMedal()
{
	int medalNumber = 0;

	if (m_pointsCount >= POINTS_BRONZE)
	{
		m_medal->setVisible(true);

		if (m_pointsCount >= POINTS_SILVER)
		{
			medalNumber = 1;
		}
		if (m_pointsCount >= POINTS_GOLD)
		{
			medalNumber = 2;
		}
		if (m_pointsCount >= POINTS_PLATINUM)
		{
			medalNumber = 3;
		}
	}

	const float size = m_medal->getContentSize().width;
	m_medal->setTextureRect(Rect(medalNumber * size, 0, size, size));
}

bool GameInterface::IsScoreNew()
{
	UserDefault* memory = UserDefault::getInstance();
	auto highScore = memory->getIntegerForKey(HIGHTSCORE_KEY, 0);

	return (m_pointsCount > static_cast<unsigned>(highScore));
}

void GameInterface::SetNewHightScore()
{
	UserDefault* memory = UserDefault::getInstance();
	auto highScore = memory->getIntegerForKey(HIGHTSCORE_KEY, 0);

	memory->setIntegerForKey(HIGHTSCORE_KEY, m_pointsCount);
}

std::string GameInterface::GetHighScoreStr()
{
	UserDefault* memory = UserDefault::getInstance();
	auto highScore = memory->getIntegerForKey(HIGHTSCORE_KEY, 0);

	return PointsToStr(highScore);
}

void GameInterface::Reset()
{
	SetStartUI();

	m_pointsCount = 0;
}

void GameInterface::Update(Vec2 const& birdPosition)
{
	m_points->setString(PointsToStr(m_pointsCount));
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

std::string PointsToStr(unsigned points)
{
	std::string pointsStr;
	std::stringstream stream;
	stream << points;
	pointsStr = stream.str();

	return pointsStr;
}