#pragma once

#include <Spore\BasicIncludes.h>

#define RandomChaos_TimerObjectPtr intrusive_ptr<RandomChaos_TimerObject>

class RandomChaos_TimerObject 
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{
	bool hasdoneeffect = false;
public:

	Clock ClockVar = Clock::Clock(Clock::Mode::Seconds);
	static const uint32_t TYPE = id("RandomChaos_TimerObject");
	
	RandomChaos_TimerObject();
	~RandomChaos_TimerObject();

	void Update() override;
	void randomTool(bool addorremove);
	void randomHealthEnergy(float amount, bool healthOrEnergy, float energyamount);
	void randomMoney(bool highOrLow);
	void randomPlanet();
	void randomTScore();
	void randomTravelDistance();
	//void newrandomplanet();
	static RandomChaos_TimerObject* Get();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

private:
	static RandomChaos_TimerObject * sInstance;
};
