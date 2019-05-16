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


	void Update() override;
	void Initialize() override{m_IsInitialized = true;}
	void Draw() const override{}

	CommandComponent(const CommandComponent& other) = delete;
	CommandComponent(CommandComponent&& other) noexcept = delete;
	CommandComponent& operator=(const CommandComponent& other) = delete;
	CommandComponent& operator=(CommandComponent&& other) noexcept = delete;

private:
	std::queue<std::shared_ptr<BaseCommand>> m_pCommandStream;

};
}

