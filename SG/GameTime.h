#ifndef GAMETIME_H
#define GAMETIME_H

#include <Windows.h>

class GameTime
{
public:
	GameTime();
	~GameTime();

	float getElapsedTime() const;
	float getTotalTime() const;

	void reset();
	void update();
private:
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_lastTime;
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_frequency;

	float m_total;
	float m_delta;
};

#endif // GAMETIME_H