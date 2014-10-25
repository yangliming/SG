#include "GameTime.h"

GameTime::GameTime()
{
	QueryPerformanceFrequency(&m_frequency);
	reset();
}

GameTime::~GameTime()
{
}

float GameTime::getElapsedTime() const
{
	return m_delta;
}

float GameTime::getTotalTime() const
{
	return m_total;
}

void GameTime::reset()
{
	update();
	m_startTime = m_currentTime;
	m_total = 0.0f;
}

void GameTime::update()
{
	QueryPerformanceCounter(&m_currentTime);

	m_total = static_cast<float>(
		static_cast<double>(m_currentTime.QuadPart - m_startTime.QuadPart) /
		static_cast<double>(m_frequency.QuadPart)
	);

	if (m_lastTime.QuadPart == m_startTime.QuadPart)
	{
		// If the timer was just reset, report a time delta equivalent to 60Hz frame time.
		m_delta = 1.0f / 60.0f;
	}
	else
	{
		m_delta = static_cast<float>(
			static_cast<double>(m_currentTime.QuadPart - m_lastTime.QuadPart) /
			static_cast<double>(m_frequency.QuadPart)
		);
	}

	m_lastTime = m_currentTime;
}