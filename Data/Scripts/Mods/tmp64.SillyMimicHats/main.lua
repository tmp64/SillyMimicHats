local MIMIC = "ArkNpcs.Mimics.Mimic"

-- Maps NPC archetype to an array of hats.
local g_HatMap = {}

local function SelectRandomHat(origName)
	local list = g_HatMap[origName]

	if not list then
		return nil
	end

	local count = #list
	local idx = math.random(count)
	return list[idx]
end

local function ArkNpcSpawner_Mod_PreSpawn(nextHandler, self, ...)
	nextHandler(self, ...)

	local rngHat = SelectRandomHat(self.Properties.sNpcArchetype)
	if rngHat then
		ChairWarn("PreSpawn: %s, %s", self.Properties.sNpcArchetype, rngHat)

		-- Save original NPC
		self.sSavedNpcArchetype = self.Properties.sNpcArchetype

		-- Set the new NPC
		self.Properties.sNpcArchetype = rngHat
	end
end

local function ArkNpcSpawner_Mod_PostSpawn(nextHandler, self, ...)
	nextHandler(self, ...)

	-- Restore original NPC
	if self.sSavedNpcArchetype then
		ChairWarn("PostSpawn: %s, %s", self.Properties.sNpcArchetype, self.sSavedNpcArchetype)
		self.Properties.sNpcArchetype = self.sSavedNpcArchetype
		self.sSavedNpcArchetype = nil
	end
end

-- Main mod table.
local gMod = {
	-- This table is available to other mods using Chairloader.GetMod.
	PublicExport = {}
}

function gMod.PublicExport:AddHatArchetype(origName, hattedName)
	local list = g_HatMap[origName]
	if not list then
		list = {}
		g_HatMap[origName] = list
	end

	table.insert(list, hattedName)
end

function gMod.PublicExport:SelectRandomHatArchetype(origName)
	return SelectRandomHat(origName)
end

-- Called when the mod is first loaded.
function gMod:OnRegister()
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".BeanieHat")
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".BucketHat")
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".CrownHat")
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".RiceHat")
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".Sombrero")
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".StripedHat")
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".TopHat")
	self.PublicExport:AddHatArchetype(MIMIC, MIMIC .. ".WitchHat")
end

-- Called after all mods have been loaded.
function gMod:OnInit()
end

-- Called after the game has been initialized.
function gMod:OnGameInit()
end

-- Called when the game is shutting down.
function gMod:OnShutdown()
end

-- Hooks entity callbacks. May be called multiple times when reloading mods and scripts.
function gMod:HookEntities()
	Chairloader.HookEntityCallback("ArkNpcSpawner", "Mod_PreSpawn", ArkNpcSpawner_Mod_PreSpawn)
	Chairloader.HookEntityCallback("ArkNpcSpawner", "Mod_PostSpawn", ArkNpcSpawner_Mod_PostSpawn)
end

-- DO NOT RENAME!
-- Chairloader uses this variable to get the mod table.
-- The variable will be set to nil after the mod has loaded.
ChairloaderCurrentMod = gMod
