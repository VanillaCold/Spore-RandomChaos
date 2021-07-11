#include "stdafx.h"
#include <Spore\Simulator\SubSystem\CommManager.h>
#include "RandomTravelRadius.h"

RandomTravelRadius::RandomTravelRadius()
{
}


RandomTravelRadius::~RandomTravelRadius()
{
}


void RandomTravelRadius::ParseLine(const ArgScript::Line& line)
{
	//auto ev = CommManager.CreateSpaceCommEvent(Simulator::GetPlayerEmpireID(), Simulator::GetPlayerEmpire()->mHomePlanet, id("event_biosphere_collapse"), id("mission_assign"));
	//CommManager.ShowCommEvent(ev);

	//auto empire = Simulator::GetPlayerEmpire();
	//empire->mTravelDistance = Math::rand(24) + 6;

}

const char* RandomTravelRadius::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "RandomTravelRadius: Elaborate description of what this cheat does.";
	}
}
