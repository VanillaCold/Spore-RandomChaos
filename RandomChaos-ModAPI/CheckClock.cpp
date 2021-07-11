#include "stdafx.h"
#include "CheckClock.h"
#include "RandomChaos_TimerObject.h"

CheckClock::CheckClock()
{
}


CheckClock::~CheckClock()
{
}


void CheckClock::ParseLine(const ArgScript::Line& line)
{
	auto Game = GameModeManager.GetActiveModeID();
	if (Game == kGGEMode){
		auto cv = RandomChaos_TimerObject::Get();
		if (cv->ClockVar.IsRunning()) { cv->ClockVar.Reset(); cv->ClockVar.Pause();  App::ConsolePrintF("Chaos disabled."); }
		else { cv->ClockVar.Start(); App::ConsolePrintF("Chaos enabled! WARNING: Chaos may cause chaotic things!"); }
	}
	else { App::ConsolePrintF("Can only toggle Chaos Mode in the Global Game Entry. (aka the main menu)"); }
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
//	ClockVariables clock;
//	string stime = to_string(clock.ClockVar.GetElapsed()); const char* ctime = stime.c_str();  App::ConsolePrintF(ctime);
}

const char* CheckClock::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Turns Chaos Mode on/off.";
	}
	else {
		return "toggleChaos - Toggles chaos mode.\n"
			"Chaos Mode makes random things happen every 10 seconds in-game.";
	}
}
