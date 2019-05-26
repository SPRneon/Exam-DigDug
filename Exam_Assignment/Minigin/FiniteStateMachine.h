#pragma once
#include "Singleton.h"
#include "States.h"
#include "LevelGrid.h"

namespace dae{

	class GameObject;
	class State;
	class Player;

	

	

	class FiniteStateMachine 
	{
	public:
		FiniteStateMachine() = default;
		void Initialize(std::shared_ptr<State> initState, std::shared_ptr<GameObject> actor, std::shared_ptr<Player> target, std::shared_ptr<LevelGrid> grid)
		{
			if(m_IsInitialized)
				return;
			m_pState = initState;
			m_pTarget =target;
			m_pActor = actor;
			m_pLevelGrid = grid;
			m_pState->OnEnter();
			m_IsInitialized = true;
		}
		
		~FiniteStateMachine() = default;

		

		std::shared_ptr<State> GetState() const {return m_pState;}
		void SetState(std::shared_ptr<State> newState){m_pState = newState;}
		void GoToState(std::shared_ptr<State> newState);

		void Update();
		std::shared_ptr<GameObject> GetActor() const { return m_pActor; }
		std::shared_ptr<Player> GetTarget() const { return m_pTarget; }
		std::shared_ptr<LevelGrid> GetGrid() const { return m_pLevelGrid; }

		FiniteStateMachine(const FiniteStateMachine &) = delete;
		FiniteStateMachine(FiniteStateMachine &&) = delete;
		FiniteStateMachine & operator= (const FiniteStateMachine &) = delete;
		FiniteStateMachine & operator= (const FiniteStateMachine &&) = delete;
	private:
		bool m_IsInitialized = false;

		std::shared_ptr<State> m_pState = nullptr;
		std::shared_ptr<GameObject> m_pActor= nullptr;
		std::shared_ptr<LevelGrid> m_pLevelGrid = nullptr;
		std::shared_ptr<Player> m_pTarget= nullptr;
		float m_deltaTime = 0;
		float m_ChargeTime = 5.f;
	};

}

