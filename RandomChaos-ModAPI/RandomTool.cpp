#include "stdafx.h"
#include "RandomTool.h"

RandomTool::RandomTool()
{
}


RandomTool::~RandomTool()
{
}


void RandomTool::ParseLine(const ArgScript::Line& line)
{
	auto context = Simulator::SpacePlayerData::Get()->mCurrentContext;
	if (Simulator::GetActivePlanetRecord()) {
		if (context != Simulator::kSpaceContextPlanet)
		{
			Simulator::SpacePlayerData::Get()->mCurrentContext = Simulator::kSpaceContextPlanet;
			Simulator::GetActivePlanetRecord()->mAtmosphereScore = randf(-0.25, 1.25);
			Simulator::GetActivePlanetRecord()->mTemperatureScore = randf(-0.25, 1.25);
			Simulator::SpacePlayerData::Get()->mCurrentContext = context;
		}
		else
		{
			Simulator::GetActivePlanetRecord()->mAtmosphereScore = randf(-0.25, 1.25);
			Simulator::GetActivePlanetRecord()->mTemperatureScore = randf(-0.25, 1.25);
		}
	}
}

const char* RandomTool::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "RandomTool: Elaborate description of what this cheat does.";
	}
}
