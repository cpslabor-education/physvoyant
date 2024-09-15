#include "Clock.hpp"


Clock::Clock() : lastTimePoint(std::chrono::steady_clock::now()), delta(0), physicsTimeStep(0), timeScale(1.0), physicsTimeScale(1.0), currentTimePoint()
{
	
}

void Clock::Update()
{
	currentTimePoint = std::chrono::steady_clock::now();
	delta = std::chrono::duration_cast<TIME_CAST_SIZE>(currentTimePoint - lastTimePoint).count();
	lastTimePoint = currentTimePoint;
}

timeValue_t Clock::DeltaTime()
{
	return delta;
}

timeValue_t Clock::ScaledDeltaTime()
{
	return delta * timeScale;
}

timeValue_t Clock::PhysicsDeltaTime()
{
	if (physicsTimeStep == 0)
	{
		return DeltaTime();
	}
	else
	{
		return physicsTimeStep;
	}
}

timeValue_t Clock::ScaledPhysicsDeltaTime()
{
	return PhysicsDeltaTime() * physicsTimeScale;
}
