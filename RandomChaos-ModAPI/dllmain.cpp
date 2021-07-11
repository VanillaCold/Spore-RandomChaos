// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "RandomTool.h"
#include <Spore\Clock.h>
#include "CheckClock.h"
#include "RandomTravelRadius.h"
#include "RandomChaos_TimerObject.h"


void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
	//CheatManager.AddCheat("randomtool", new RandomTool);
	//CheatManager.AddCheat("removeItem", new RemoveItem);#
	//float time = t.GetElapsed();
	//Clock t = Clock::Clock(Clock::Mode::Seconds);
	//t.Start();
	//float time = t.GetElapsed();
	//for (int i = 0; i = 5; i += 5) { string stime = to_string(time); const char* ctime = stime.c_str();  App::ConsolePrintF(ctime); };
	//t.Reset();
	//SimulatorSystem.AddStrategy(new ClockVars(), ClockVars::NOUN_ID);
	CheatManager.AddCheat("toggleChaos",new CheckClock());
	CheatManager.AddCheat("randomtscore", new RandomTool());
	CheatManager.AddCheat("randomtravel", new RandomTravelRadius());
	
	RandomChaos_TimerObject * chaos = new RandomChaos_TimerObject();
	App::AddUpdateFunction(chaos);
	//auto thingy = ClockVars::Get();
//	thingy->ClockVar.Start();
}

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

