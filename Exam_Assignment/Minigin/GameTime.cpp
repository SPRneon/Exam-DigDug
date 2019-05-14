#include "MiniginPCH.h"
#include "GameTime.h"
#include <chrono>
//Partly inspired by the overlord engine and Unity


dae::GameTime::GameTime()
	: m_TotalGameTime(0.f),
	 m_PausedTime(0.f),
	m_SecPerCount(0.f),
	m_IsPaused(false),
	m_FPS(0),
	m_ElapsedGameTime(0.f)	
{
	m_CurrTime = std::chrono::high_resolution_clock::now();
	m_BeginTime = m_CurrTime;
	m_PrevTime = m_CurrTime;
	m_StartTime = m_CurrTime;
	m_StopTime = m_CurrTime;
}

void dae::GameTime::Reset()
{
	m_CurrTime = std::chrono::high_resolution_clock::now();
	m_BeginTime = m_CurrTime;
	m_PrevTime = m_CurrTime;
	m_StartTime = m_CurrTime;
	m_StopTime = m_CurrTime;
	m_IsPaused = false;
}


void dae::GameTime::Update()
{
	if(m_IsPaused)
	{
		m_FPS = 0;
		m_ElapsedGameTime = 0;
		m_TotalGameTime = (std::chrono::duration_cast<std::chrono::seconds>(m_StopTime - m_BeginTime)).count() - m_PausedTime;
		return;
	}

	m_CurrTime = std::chrono::high_resolution_clock::now();
	m_ElapsedGameTime = static_cast<float>((std::chrono::duration_cast<std::chrono::microseconds>(m_CurrTime - m_PrevTime)).count());
	m_PrevTime = m_CurrTime;

	if(m_ElapsedGameTime < 0.f)
		m_ElapsedGameTime = 0;

	m_TotalGameTime = std::chrono::duration_cast<std::chrono::seconds>(m_CurrTime - m_BeginTime).count() - m_PausedTime;

	
	m_FpsTimer += (m_ElapsedGameTime / 1000000.f);
	++m_FpsCount;
	if((m_FpsTimer)  >= 1.0)
	{
		m_FPS = m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= 1.0f;
	}
}


void dae::GameTime::Start()
{
	if(m_IsPaused)
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
		m_PausedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(m_StartTime - m_StopTime).count());
		m_IsPaused = false;
	}
}

void dae::GameTime::Stop()
{
	if(!m_IsPaused)
	{
		m_StopTime = std::chrono::high_resolution_clock::now();
		m_IsPaused = true;
	}
}

