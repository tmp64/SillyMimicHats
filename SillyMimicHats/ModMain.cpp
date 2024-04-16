#include <Prey/CryScriptSystem/IScriptSystem.h>
#include <Prey/CryScriptSystem/ScriptHelpers.h>
#include <Chairloader/ModSDK/ChairGlobalModName.h>
#include "ArkNpcSpawner.h"
#include "ModMain.h"

ModMain* gMod = nullptr;

auto g_CArkNpcSpawner_GetEntityArchetype_Hook = CArkNpcSpawner::FGetEntityArchetype.MakeHook();

IEntityArchetype* CArkNpcSpawner_GetEntityArchetype_Hook(const CArkNpcSpawner* const _this)
{
	IScriptTable* pScript = _this->GetEntity()->GetScriptTable();
	Script::CallMethod(pScript, "Mod_PreSpawn");
	IEntityArchetype* res = g_CArkNpcSpawner_GetEntityArchetype_Hook.InvokeOrig(_this);
	Script::CallMethod(pScript, "Mod_PostSpawn");

	return res;
}

void ModMain::FillModInfo(ModDllInfoEx& info)
{
	info.modName = "tmp64.SillyMimicHats"; // CHANGE ME
	info.logTag = "SillyMimicHats"; // CHANGE ME
	info.supportsHotReload = true; // TODO: Add comment/wiki link
}

void ModMain::InitHooks()
{
	// g_CArkNpcSpawner_SetupSpawnedNpcCharacter_Hook.SetHookFunc(&SetupSpawnedNpcCharacter_Hook);
	g_CArkNpcSpawner_GetEntityArchetype_Hook.SetHookFunc(&CArkNpcSpawner_GetEntityArchetype_Hook);
}

void ModMain::InitSystem(const ModInitInfo& initInfo, ModDllInfo& dllInfo)
{
	BaseClass::InitSystem(initInfo, dllInfo);
    ChairSetGlobalModName("tmp64.SillyMimicHats"); // CHANGE ME
}

void ModMain::InitGame(bool isHotReloading)
{
	BaseClass::InitGame(isHotReloading);
	// Your code goes here
}

void ModMain::ShutdownGame(bool isHotUnloading)
{
	// Your code goes here
	BaseClass::ShutdownGame(isHotUnloading);
}

void ModMain::ShutdownSystem(bool isHotUnloading)
{
	// Your code goes here
	BaseClass::ShutdownSystem(isHotUnloading);
}

void ModMain::Draw()
{
}

void ModMain::MainUpdate(unsigned updateFlags)
{
	// Your code goes here
}



void *ModMain::QueryInterface(const char *ifaceName) {
    return nullptr;
}

void ModMain::Connect(const std::vector<IChairloaderMod *> &mods) {
}

extern "C" DLL_EXPORT IChairloaderMod* ClMod_Initialize()
{
	CRY_ASSERT(!gMod);
	gMod = new ModMain();
	return gMod;
}

extern "C" DLL_EXPORT void ClMod_Shutdown()
{
	CRY_ASSERT(gMod);
	delete gMod;
	gMod = nullptr;
}

// Validate that declarations haven't changed
static_assert(std::is_same_v<decltype(ClMod_Initialize), IChairloaderMod::ProcInitialize>);
static_assert(std::is_same_v<decltype(ClMod_Shutdown), IChairloaderMod::ProcShutdown>);
