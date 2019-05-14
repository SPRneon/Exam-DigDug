#include "MiniginPCH.h"
#include "Player.h"
#include "GameObject.h"
#include "BaseCommand.h"
#include <memory>
#include "vector"

dae::Player::Player()
	:m_pGameObject(nullptr)
{
	m_pGameObject = new GameObject();
}


dae::Player::~Player()
{
}

void dae::Player::PerformAllCommands()
{
	for(auto command : m_pCommandStream)
		command->execute();
}

void dae::Player::PerformCommands(int nrOfCommands)
{
	UNREFERENCED_PARAMETER(nrOfCommands);
}

void dae::Player::UndoCommand(int nrOfUndos)
{
	UNREFERENCED_PARAMETER(nrOfUndos);
}

