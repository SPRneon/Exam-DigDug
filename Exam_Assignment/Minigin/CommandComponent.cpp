#include "MiniginPCH.h"
#include "CommandComponent.h"
#include "BaseCommand.h"


dae::CommandComponent::CommandComponent()
{
}


dae::CommandComponent::~CommandComponent()
{
}

void dae::CommandComponent::AddToCommandStream(std::shared_ptr<BaseCommand> pCommand)
{
	m_pCommandStream.push(m_pCommandStream.front);
}

void dae::CommandComponent::PerformAllCommands()
{
	while(!m_pCommandStream.empty())
	{
		m_pCommandStream.front()->execute();
		m_pCommandStream.pop();
	}
}

