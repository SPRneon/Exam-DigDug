#pragma once
#define COMMAND_STREAM_MAX_COUNT 25

namespace dae{

	class GameObject;
	class BaseCommand;

class Player
{
public:
	Player();
	~Player();


	GameObject* GetGameObject() const { return m_pGameObject;}
	void PerformAllCommands();
	void PerformCommands(int nrOfCommands = 1);
	void UndoCommand(int nrOfUndos = 1);
private:
	GameObject* m_pGameObject;

	//Commands
	std::vector<std::shared_ptr<BaseCommand>> m_pCommandStream;
};
}

