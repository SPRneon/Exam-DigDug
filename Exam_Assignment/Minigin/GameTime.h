#pragma once
#include "Singleton.h"
#include <chrono>
//Partly inspired by the overlord engine and Unity
namespace dae
{

	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime(void);
		~GameTime(void) = default;

		void Reset();
		void Update();

		const float GetElapsed(){return m_ElapsedGameTime / 1000000.f;}
		const float GetTotal() { return m_TotalGameTime;}
		const int GetFps(){return m_FPS;}
		const bool IsPaused()const {return m_IsPaused;}

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

