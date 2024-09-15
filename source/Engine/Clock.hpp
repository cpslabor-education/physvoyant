#ifndef CLOCK
#define CLOCK

#include <chrono>
#include "../defines.hpp"
#include INCL_INTERFACES

class Clock : public IUpdateable
{
	std::chrono::steady_clock::time_point lastTimePoint;
	timeValue_t delta;
	timeValue_t physicsTimeStep;
	realStandard_t timeScale;
	realStandard_t physicsTimeScale;
	std::chrono::steady_clock::time_point currentTimePoint;
public:
	Clock();

	// Inherited via IUpdateable
	void Update() override;
	timeValue_t DeltaTime(); // Delta time
	timeValue_t ScaledDeltaTime(); // Delta time
	timeValue_t PhysicsDeltaTime(); // Delta time for fixed step calculations
	timeValue_t ScaledPhysicsDeltaTime(); // Scaledelta time for fixed step calculations

	void SetPhysicsTimeStep(const timeValue_t value)
	{
		physicsTimeStep = value;
	}

	realStandard_t GetTimeScale() const
	{
		return timeScale;
	}

	void SetTimeScale(const realStandard_t& value)
	{
		timeScale = value;
	}

	realStandard_t GetPhysicsTimeScale() const
	{
		return physicsTimeScale;
	}

	void SetPhysicsTimeScale(const realStandard_t& value)
	{
		physicsTimeScale = value;
	}




};


#endif
