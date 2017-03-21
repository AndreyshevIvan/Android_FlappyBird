#include "gameBehavior.h"

USING_NS_CC;

void GameBehavior::Init(Bird* bird, GameMap* map, GameInterface* gameInterface)
{
	m_bird = bird;
	m_map = map;
	m_interface = gameInterface;
}

void StartGameBehavior::Start()
{
	m_bird->Reset();
	m_map->Reset();
	m_interface->Reset();
}

void StartGameBehavior::Update(float elapsedTime)
{
	m_interface->UpdateHelpPanel(m_bird->GetPosition());
}

bool StartGameBehavior::IsOnTouchChange()
{
	return true;
}

void GameplayBehavior::Start()
{
	m_interface->SetGameplayUI();
	m_map->StartMotion();
	m_bird->StartFlapping();
}

void GameplayBehavior::OnTouchEvent()
{
	m_bird->Jump();
}

void GameplayBehavior::CollideWithPointEvent()
{
	m_interface->AddPoint();
}

void GameoverBehavior::Start()
{
	m_interface->SetGameoverUI();
	m_bird->Death();
	m_map->StopMotion();
}

bool GameoverBehavior::IsOnTouchChange()
{
	bool isReadyToChange = m_interface->IsGameoverTableAppeared();

	return isReadyToChange;
}