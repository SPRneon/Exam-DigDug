#pragma once
#include "Helpers/Singleton.h"
#include <chrono>

namespace dae
{

	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime(void);
		~GameTime(void) = default;

		void Reset();
		void Update();

		float GetElapsed(){return m_ElapsedGameTime;}
		float GetTotal() { return m_TotalGameTime;}
		int GetFps(){return m_FPS;}

		void Start();
		void Stop();


	private:
		float m_TotalGameTime;
		float m_ElapsedGameTime;
		float m_SecPerCount;
		float m_PausedTime;

		std::chrono::time_point<std::chrono::steady_clock> m_BeginTime;
		std::chrono::time_point<std::chrono::steady_clock> m_CurrTime;
		std::chrono::time_point<std::chrono::steady_clock> m_PrevTime;

		std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
		std::chrono::time_point<std::chrono::steady_clock> m_StopTime;

		int m_FPS;
		float m_FpsTimer;
		int m_FpsCount;

		bool m_IsPaused;
	};


}

