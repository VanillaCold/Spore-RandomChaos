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
	void spg_randomTool();
	void spg_randomHealthEnergy(float amount, bool healthOrEnergy, float energyamount);
	void spg_randomMoney(bool highOrLow);
	void spg_randomPlanet();
	void spg_randomTScore();
	void spg_randomTravelDistance();
	void crg_randomEpic();
	//void newrandomplanet();
	static RandomChaos_TimerObject* Get();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

private:
	static RandomChaos_TimerObject * sInstance;
};
