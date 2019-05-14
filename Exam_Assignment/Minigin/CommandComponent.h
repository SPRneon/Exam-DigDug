#pragma once
#include "BaseComponent.h"
#include <queue>



namespace dae{

	class BaseCommand;

class CommandComponent :
	public BaseComponent
{
public:
	CommandComponent();
	virtual ~CommandComponent() override;

	void AddToCommandStream(std::shared_ptr<BaseCommand> pCommand);
	void PerformAllCommands();
	void PerformCommands(int nrOfCommands = 1);
	void UndoCommand(int nrOfUndos = 1);

	CommandComponent(const CommandComponent& other) = delete;
	CommandComponent(CommandComponent&& other) noexcept = delete;
	CommandComponent& operator=(const CommandComponent& other) = delete;
	CommandComponent& operator=(CommandComponent&& other) noexcept = delete;

private:
	std::queue<std::shared_ptr<BaseCommand>> m_pCommandStream;

};
}

