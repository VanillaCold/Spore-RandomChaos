#include "stdafx.h"
#include "RandomChaos_TimerObject.h"

RandomChaos_TimerObject::RandomChaos_TimerObject()
{
	sInstance = this;
}


RandomChaos_TimerObject::~RandomChaos_TimerObject()
{
}

void RandomChaos_TimerObject::Update()
{
	auto clockelapsed = ClockVar.GetElapsedTime();
	if (clockelapsed > 10)
	{
		if (Simulator::IsSpaceGame() == 1) {
			int chosenone = Math::rand(4) + 1;
			hasdoneeffect = false;

			bool thingy = true;
			auto ufo = Simulator::GetPlayerUFO();
			bool healthorenergy = 0; float amount = 0; float enamount = 0;
			while (hasdoneeffect == false)
			{
				int chosenone = Math::rand(5) + 1;

				if (Math::randf(0, 1) > 0.49) { healthorenergy = 1; }
				if (healthorenergy == 1) { enamount = Math::randf(0, ufo->mMaxEnergy); }
				else { amount = Math::randf(0, ufo->GetMaxHitPoints()); }
				App::ConsolePrintF(to_string(clockelapsed).c_str());
				if (chosenone == 1) { spg_randomTool(); App::ConsolePrintF("tool"); }
				if (chosenone == 2) { App::ConsolePrintF("health/energy"); spg_randomHealthEnergy(amount, healthorenergy, enamount); }
				if (chosenone == 3) { App::ConsolePrintF("money"); spg_randomMoney(thingy); }
				if (chosenone == 4) { spg_randomPlanet(); App::ConsolePrintF("teleport"); }
				if (chosenone == 5) { spg_randomTScore(); App::ConsolePrintF("tscore"); }
				//if (chosenone == 6) { randomTravelDistance(); App::ConsolePrintF("travel distance"); }
			}

		}
		ClockVar.Reset(); ClockVar.Start();
	}
	
}

void RandomChaos_TimerObject::spg_randomTool()
{
	//0xa91269af
	cSpaceToolDataPtr tool;
	size_t count;
	vector<uint32_t> listIDs;
	PropertyListPtr propList;

	//PropManager.GetPropertyList(id("ToolConfig"), 0x30608F0B, propList);
	PropManager.GetAllListIDs(GroupIDs::SpaceTools, listIDs);
	//App::Property::GetArrayKey(propList.get(), 0x02C08E1E, count, listofparts);

 	uint32_t gen = Math::rand(listIDs.size());

	vector<uint32_t> bannedIDs{
	id("interplanetarydrive"), id("interstellardrive_upgrade1"), id("interstellardrive_upgrade2") , id("interstellardrive_upgrade3"),
	id("interstellardrive_upgrade4"), id("interstellardrive_upgrade5"), id("interstellardrive_upgrade6"), id("interplanetarydrive"), id("scan"), id("seti"),
	id("laserlevel1"), id("laserlevel2"), id("laserlevel3"), id("abduct"), id("protonmissilelevel1"), id("protonmissilelevel2"), id("protonmissilelevel3"), id("radar")};



	ResourceKey selectedTool = { listIDs[gen],0,0 };
	if (ToolManager.LoadTool(selectedTool, tool))
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		uint32_t eventID = UIEventLog.ShowEvent(id("WarDeclared"), GroupIDs::SpacePopups);

		bool addorremove = rand(1);

		//if (inventory->HasTool(selectedtool) == 0) { addorremove = true; }

		if (addorremove == true)
		{
			inventory->AddItem(tool.get());
			UIEventLog.SetDescription(eventID, u"You just got a random tool!");
		}
		else
		{
			cSpaceInventoryItemPtr item = nullptr;
			bool canExit = false;
			int cycles = 0;


			while (canExit == false)
			{
				cycles++;
				item = inventory->mInventoryItems[rand(inventory->mInventoryItems.size())];
				if (item->mpPropList == nullptr) { continue; }

				auto itemKey = item->mpPropList->GetResourceKey();
				if (eastl::find(bannedIDs.begin(), bannedIDs.end(), itemKey.instanceID ) != bannedIDs.end())
				{
					canExit = false;
				}

				else
				{
					canExit = true;
				}

				if (cycles > 1000)
				{
					hasdoneeffect = false;
					return;
				}
			}


			inventory->RemoveItem(item.get());

			//inventory->RemoveItem(inventory->GetTool(selectedtool)); 
			UIEventLog.SetDescription(eventID, u"You just lost a random tool! Oh no, anyway.");
		}

		hasdoneeffect = true;
	}
	else
	{
		SporeDebugPrint("AAAAAAAAAAAAAAAAAAAAAAAAAAA");
	}
}

void RandomChaos_TimerObject::spg_randomHealthEnergy(float amount, bool healthOrEnergy, float energyamount)
{
	auto ufo = Simulator::GetPlayerUFO();
	if (healthOrEnergy == 0) {
		ufo->SetHealthPoints(amount);
		if (amount > ufo->GetMaxHitPoints()) { ufo->SetHealthPoints(ufo->GetMaxHitPoints()); }

		uint32_t eventID = UIEventLog.ShowEvent(id("WarDeclared"), GroupIDs::SpacePopups);
		UIEventLog.SetDescription(eventID, u"Your health just got randomized!");
	}
	else {
		ufo->mEnergy = energyamount;
		if (energyamount > ufo->mMaxEnergy) { ufo->mEnergy = ufo->mMaxEnergy; };

		uint32_t eventID = UIEventLog.ShowEvent(id("WarDeclared"), GroupIDs::SpacePopups);
		UIEventLog.SetDescription(eventID, u"Your energy just got randomized!");
	}
	hasdoneeffect = true;
}

void RandomChaos_TimerObject::spg_randomMoney(bool highOrLow)
{
	auto empire = Simulator::GetPlayerEmpire();
	int amounttoadd = 0;
	if (highOrLow == 1) { amounttoadd = Math::rand(9999); }
	else { amounttoadd = Math::rand(-9999); }
	//auto otheramount = Math::rand(amounttoadd);
	empire->mEmpireMoney += amounttoadd;
	hasdoneeffect = true;
	uint32_t eventID = UIEventLog.ShowEvent(id("WarDeclared"), GroupIDs::SpacePopups);
	UIEventLog.SetDescription(eventID, u"Your money just got randomized!");
}

void RandomChaos_TimerObject::spg_randomPlanet()
{
	auto context = Simulator::SpacePlayerData::Get()->mCurrentContext;
	if (context != Simulator::kSpaceContextPlanet) {
		//Simulator::SpacePlayerData::Get()->mCurrentContext = Simulator::kSpaceContextGalaxy;
		if (context == Simulator::kSpaceContextSolarSystem) { MessageManager.PostMSG(0x6527EAF, nullptr); }

		Simulator::cStarRecord* thing = Simulator::GetPlayerEmpire()->GetHomeStarRecord();
		auto gennum = Math::rand(2);
		if (gennum == 1) { thing = StarManager.GetSol(); }
		Simulator::SpaceTeleportTo(thing);
		hasdoneeffect = true;
	}
	uint32_t eventID = UIEventLog.ShowEvent(id("WarDeclared"), GroupIDs::SpacePopups);
	UIEventLog.SetDescription(eventID, u"You just got teleported!");
}

void RandomChaos_TimerObject::spg_randomTScore()
{
	auto context = Simulator::SpacePlayerData::Get()->mCurrentContext;
	if (Simulator::GetActivePlanetRecord()) {
		if (Simulator::GetActivePlanetRecord()->mbHomeWorld == true)
		{
			return;
		}
		
		if (context != Simulator::kSpaceContextPlanet)
		{
			//Simulator::SpacePlayerData::Get()->mCurrentContext = Simulator::kSpaceContextPlanet;
			Simulator::GetActivePlanetRecord()->mAtmosphereScore = randf(-0.25, 1.25);
			Simulator::GetActivePlanetRecord()->mTemperatureScore = randf(-0.25, 1.25);
			//Simulator::SpacePlayerData::Get()->mCurrentContext = context;
			hasdoneeffect = true;
		}
		else
		{
			Simulator::GetActivePlanetRecord()->mAtmosphereScore = randf(-0.25, 1.25);
			Simulator::GetActivePlanetRecord()->mTemperatureScore = randf(-0.25, 1.25);
			hasdoneeffect = true;
		}
	}
	uint32_t eventID = UIEventLog.ShowEvent(id("WarDeclared"), GroupIDs::SpacePopups);
	UIEventLog.SetDescription(eventID, u"The planet's T-Score just got randomized!");
}

void RandomChaos_TimerObject::spg_randomTravelDistance()
{
	//doesn't work, ignore this one
	auto empire = Simulator::GetPlayerEmpire();
	empire->mTravelDistance = Math::rand(24) + 6;
}

void RandomChaos_TimerObject::crg_randomEpic()
{
}

RandomChaos_TimerObject* RandomChaos_TimerObject::Get()
{
	return sInstance;
}

// For internal use, do not modify.
int RandomChaos_TimerObject::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int RandomChaos_TimerObject::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* RandomChaos_TimerObject::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(RandomChaos_TimerObject);
	return nullptr;
}

RandomChaos_TimerObject* RandomChaos_TimerObject::sInstance = nullptr;