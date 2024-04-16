// Header file automatically created from a PDB.
#pragma once

class ArkNpc;
enum EEntityAspects;
class ICrySizer;
struct IEntity;
struct IEntityArchetype;
struct IGameObject;
struct ISerializableInfo;
struct SEntityEvent;
struct SEntitySpawnParams;
struct SEntityUpdateContext;
struct SGameObjectEvent;

// IArkSaveLoadListener
// Header:  _unknown/IArkSaveLoadListener.h
class IArkSaveLoadListener
{ // Size=8 (0x8)
public:
	virtual void OnFirstTimeInLevel() = 0;
};

// CArkNpcSpawner
// Header:  Prey/GameDll/ark/npc/ArkNpcSpawner.h
class CArkNpcSpawner : public CGameObjectExtensionHelper<CArkNpcSpawner, IGameObjectExtension>, public IArkSaveLoadListener
{ // Size=96 (0x60)
public:
	uint64_t m_pendingSpawnCount;
	unsigned m_lastSpawnedEntityId;
	string m_ManagedByEncounter;
	
	CArkNpcSpawner();
	virtual ~CArkNpcSpawner();
	virtual void GetMemoryUsage(ICrySizer* _pSizer) const;
	virtual bool Init(IGameObject* _pGameObject);
	virtual void PostInit(IGameObject* _pGameObject);
	virtual void InitClient(int _channelId);
	virtual void PostInitClient(int _channelId);
	virtual bool ReloadExtension(IGameObject* _pGameObject, const SEntitySpawnParams& _rParams);
	virtual void PostReloadExtension(IGameObject* _pGameObject, const SEntitySpawnParams& _rParams);
	virtual bool GetEntityPoolSignature(TSerialize _signature);
	virtual void Release();
	virtual void FullSerialize(TSerialize _ser);
	virtual bool NetSerialize(TSerialize _ser, EEntityAspects _aspect, uint8_t profile, int _pflags);
	virtual void PostSerialize();
	virtual void SerializeSpawnInfo(TSerialize _ser);
	virtual _smart_ptr<ISerializableInfo> GetSpawnInfo();
	virtual void Update(SEntityUpdateContext& _rCtx, int _updateSlot);
	virtual void HandleEvent(const SGameObjectEvent& _event);
	virtual void ProcessEvent(SEntityEvent& _event);
	virtual void SetChannelId(uint16_t _id);
	virtual void SetAuthority(bool _auth);
	virtual void PostUpdate(float _frameTime);
	virtual void PostRemoteSpawn();
	virtual void OnFirstTimeInLevel();
	IEntity* SpawnNpcEntity(unsigned _fromStartGameEntityId) { return FSpawnNpcEntity(this, _fromStartGameEntityId); }
	void RequestSpawn() { FRequestSpawn(this); }
	void SetManagedByEncounter(const string& encounter_name) { FSetManagedByEncounter(this, encounter_name); }
	IEntityArchetype* GetEntityArchetype() const { return FGetEntityArchetype(this); }
	void InitializeNpc(ArkNpc& _npc) const { FInitializeNpc(this, _npc); }
	void SetupSpawnedNpcCharacter() { FSetupSpawnedNpcCharacter(this); }
	
#if 0
	void TrackSpawnedEntity(IEntity* _arg0_);
	const string& GetManagingEncounter() const;
	const unsigned GetLastSpawnedEntityId() const;
	IEntity* DoSpawnNpcEntity(unsigned _arg0_);
	void ProcessEditorPropertyChangedEvent(SEntityEvent& _arg0_);
	void ProcessResetEvent(SEntityEvent& _arg0_);
	void ProcessScriptEvent(SEntityEvent& _arg0_);
	void ProcessSpawnScriptEvent(SEntityEvent& _arg0_);
	void ProcessSpawnForEncounterScriptEvent(SEntityEvent& _arg0_);
	void ProcessStartGameEvent(SEntityEvent& _arg0_);
#endif
	
	static inline auto FCArkNpcSpawnerOv1 = PreyFunction<void(CArkNpcSpawner* const _this)>(0x151BED0);
	static inline auto FGetMemoryUsage = PreyFunction<void(const CArkNpcSpawner* const _this, ICrySizer* _pSizer)>(0xA13080);
	static inline auto FInit = PreyFunction<bool(CArkNpcSpawner* const _this, IGameObject* _pGameObject)>(0x13CACC0);
	static inline auto FPostInit = PreyFunction<void(CArkNpcSpawner* const _this, IGameObject* _pGameObject)>(0xA13080);
	static inline auto FInitClient = PreyFunction<void(CArkNpcSpawner* const _this, int _channelId)>(0xA13080);
	static inline auto FPostInitClient = PreyFunction<void(CArkNpcSpawner* const _this, int _channelId)>(0xA13080);
	static inline auto FReloadExtension = PreyFunction<bool(CArkNpcSpawner* const _this, IGameObject* _pGameObject, const SEntitySpawnParams& _rParams)>(0x1B933B0);
	static inline auto FPostReloadExtension = PreyFunction<void(CArkNpcSpawner* const _this, IGameObject* _pGameObject, const SEntitySpawnParams& _rParams)>(0xA13080);
	static inline auto FGetEntityPoolSignature = PreyFunction<bool(CArkNpcSpawner* const _this, TSerialize _signature)>(0x151C8D0);
	static inline auto FRelease = PreyFunction<void(CArkNpcSpawner* const _this)>(0xA97D40);
	static inline auto FFullSerialize = PreyFunction<void(CArkNpcSpawner* const _this, TSerialize _ser)>(0x151C550);
	static inline auto FNetSerialize = PreyFunction<bool(CArkNpcSpawner* const _this, TSerialize _ser, EEntityAspects _aspect, uint8_t profile, int _pflags)>(0x1B933B0);
	static inline auto FPostSerialize = PreyFunction<void(CArkNpcSpawner* const _this)>(0xA13080);
	static inline auto FSerializeSpawnInfo = PreyFunction<void(CArkNpcSpawner* const _this, TSerialize _ser)>(0xA13080);
	static inline auto FGetSpawnInfo = PreyFunction<_smart_ptr<ISerializableInfo>*(CArkNpcSpawner* const _this, _smart_ptr<ISerializableInfo>* _return_value_)>(0x13883F0);
	static inline auto FUpdate = PreyFunction<void(CArkNpcSpawner* const _this, SEntityUpdateContext& _rCtx, int _updateSlot)>(0x151D240);
	static inline auto FHandleEvent = PreyFunction<void(CArkNpcSpawner* const _this, const SGameObjectEvent& _event)>(0xA13080);
	static inline auto FProcessEvent = PreyFunction<void(CArkNpcSpawner* const _this, SEntityEvent& _event)>(0x151CC10);
	static inline auto FSetChannelId = PreyFunction<void(CArkNpcSpawner* const _this, uint16_t _id)>(0xA13080);
	static inline auto FSetAuthority = PreyFunction<void(CArkNpcSpawner* const _this, bool _auth)>(0xA13080);
	static inline auto FPostUpdate = PreyFunction<void(CArkNpcSpawner* const _this, float _frameTime)>(0xA13080);
	static inline auto FPostRemoteSpawn = PreyFunction<void(CArkNpcSpawner* const _this)>(0xA13080);
	static inline auto FOnFirstTimeInLevel = PreyFunction<void(IArkSaveLoadListener* const _this)>(0x151CB50);
	static inline auto FSpawnNpcEntity = PreyFunction<IEntity* (CArkNpcSpawner* const _this, unsigned _fromStartGameEntityId)>(0x151D050);
	static inline auto FRequestSpawn = PreyFunction<void(CArkNpcSpawner* const _this)>(0x151CD80);
	static inline auto FSetManagedByEncounter = PreyFunction<void(CArkNpcSpawner* const _this, const string& encounter_name)>(0x151CDF0);
	static inline auto FGetEntityArchetype = PreyFunction<IEntityArchetype* (const CArkNpcSpawner* const _this)>(0x151C800);
	static inline auto FInitializeNpc = PreyFunction<void(const CArkNpcSpawner* const _this, ArkNpc& _npc)>(0x151C910);
	static inline auto FSetupSpawnedNpcCharacter = PreyFunction<void(CArkNpcSpawner* const _this)>(0x151CE00);
};


