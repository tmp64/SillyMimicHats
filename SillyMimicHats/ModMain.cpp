#include <Prey/CryScriptSystem/IScriptSystem.h>
#include <Prey/CryScriptSystem/ScriptHelpers.h>
#include <Prey/GameDll/ark/ArkScriptTable.h>
#include <Chairloader/ModSDK/ChairGlobalModName.h>
#include "ArkNpcSpawner.h"
#include "ModMain.h"

ModMain* gMod = nullptr;

//---------------------------------------------------------------------------------
// Function Hooks
//---------------------------------------------------------------------------------
auto g_CArkNpcSpawner_GetEntityArchetype_Hook = CArkNpcSpawner::FGetEntityArchetype.MakeHook();

IEntityArchetype* GetArchetypeOverride(const CArkNpcSpawner* const _this)
{
    SmartScriptTable pScript = _this->GetEntity()->GetScriptTable();
    if (!pScript)
        return nullptr;

    ArkSafeScriptTable pScriptSafe = pScript;
    ArkSafeScriptTable pProps = pScriptSafe.GetSafeSubTable("Properties");
    if (!pProps.m_pScriptTable)
        return nullptr;

    const char* archetypeName = pProps.GetString("sNpcArchetype", nullptr);
    if (!archetypeName)
        return nullptr;

    const std::string* pNewName = gMod->GetReplacementArchetype(archetypeName);
    if (!pNewName)
        return nullptr;

    IEntityArchetype* pArchetype = gEnv->pEntitySystem->LoadEntityArchetype(pNewName->c_str());
    if (!pArchetype)
    {
        CryError("Archetype '{}' not found", *pNewName);
        return nullptr;
    }

    return pArchetype;
}

IEntityArchetype* CArkNpcSpawner_GetEntityArchetype_Hook(const CArkNpcSpawner* const _this)
{
    IEntityArchetype* pOverride = GetArchetypeOverride(_this);

    if (pOverride)
        return pOverride;

    return g_CArkNpcSpawner_GetEntityArchetype_Hook.InvokeOrig(_this);;
}

//---------------------------------------------------------------------------------
// Mod Methods
//---------------------------------------------------------------------------------
const std::string* ModMain::GetReplacementArchetype(std::string_view originalArchetype)
{
    auto it = m_ArchetypeMap.find(originalArchetype);

    if (it == m_ArchetypeMap.end())
        return nullptr;

    const std::vector<std::string>& list = it->second;
    CRY_ASSERT(!list.empty());
    std::uniform_int_distribution<int> distribution(0, (int)list.size() - 1);
    int idx = distribution(m_Rng);
    return &list[idx];
}

void ModMain::RegisterArchetype(std::string_view originalName, std::string_view newName)
{
    auto it = m_ArchetypeMap.find(originalName);

    if (it != m_ArchetypeMap.end())
    {
        // Append to the exsting list
        it->second.push_back(std::string(newName));
    }
    else
    {
        // Create a new list
        m_ArchetypeMap.emplace(std::string(originalName), std::vector<std::string> { std::string(newName) });
    }
}

//---------------------------------------------------------------------------------
// Mod Initialization
//---------------------------------------------------------------------------------
void ModMain::FillModInfo(ModDllInfoEx& info)
{
    info.modName = "tmp64.SillyMimicHats";
    info.logTag = "SillyMimicHats";
    info.supportsHotReload = true;
}

void ModMain::InitHooks()
{
    g_CArkNpcSpawner_GetEntityArchetype_Hook.SetHookFunc(&CArkNpcSpawner_GetEntityArchetype_Hook);
}

void ModMain::InitSystem(const ModInitInfo& initInfo, ModDllInfo& dllInfo)
{
    BaseClass::InitSystem(initInfo, dllInfo);

    m_Rng = std::mt19937(gEnv->bNoRandomSeed ? 0u : std::random_device()());

    // Default archetypes
    const std::string MIMIC = "ArkNpcs.Mimics.Mimic";
    RegisterArchetype(MIMIC, MIMIC + ".BucketHat");
    RegisterArchetype(MIMIC, MIMIC + ".CrownHat");
    RegisterArchetype(MIMIC, MIMIC + ".RiceHat");
    RegisterArchetype(MIMIC, MIMIC + ".Sombrero");
    RegisterArchetype(MIMIC, MIMIC + ".StripedHat");
    RegisterArchetype(MIMIC, MIMIC + ".TopHat");
    RegisterArchetype(MIMIC, MIMIC + ".WitchHat");
}

void ModMain::InitGame(bool isHotReloading)
{
    BaseClass::InitGame(isHotReloading);
    // Your code goes here
}

//---------------------------------------------------------------------------------
// Mod Shutdown
//---------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------
// GUI
//---------------------------------------------------------------------------------
void ModMain::Draw()
{
}

//---------------------------------------------------------------------------------
// Main Update Loop
//---------------------------------------------------------------------------------
void ModMain::MainUpdate(unsigned updateFlags)
{
    // Your code goes here
}

//---------------------------------------------------------------------------------
// Mod Interfacing
//---------------------------------------------------------------------------------
#ifdef EXAMPLE
void* ModMain::QueryInterface(const char* ifaceName)
{
    // This function is called by other mods to get interfaces.
    // Check if you implement the interface. If so, return a pointer to it.
    // This example assumes ModMain inherits from the interface class. You may choose a different object if you want.
    if (!strcmp(ifaceName, IModName::IFACE_NAME))
        return static_cast<IModName*>(this);

    return nullptr;
}

void ModMain::Connect(const std::vector<IChairloaderMod*>& mods)
{
    IModName* pModName = nullptr; // Add this to ModMain

    // You can use one of these helper functions. They will handle finding and version checking.
    pModName = GetInterfaceFromModList<IModName>(mods, "Other Mod Name");
    pModName = GetRequiredInterfaceFromModList<IModName>(mods, "Other Mod Name");
}
#endif

//---------------------------------------------------------------------------------
// Exported Functions
//---------------------------------------------------------------------------------
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
