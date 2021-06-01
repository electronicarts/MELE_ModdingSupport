// (c) 2021 Electronic Arts Inc.  All rights reserved.
// 
// FOR REFERENCE PURPOSES ONLY. 
// Electronic Arts does not support or condone any specific mod for use with EA’s games. EA’s User Agreement applies and EA reserves all rights. Use mods with caution at your own risk.
//
// ME1 Savegame file format
// 
// All the data in these structs is laid out in the order in which data is serialized  the structs are mainly just used as 
// a way of organizing the data, and are not meant to indicate how the data is organized in memory
// 
// NOTES:
//   - All arrays are serialized with a preceeding integer denoting the number of elements in the array
//   - ME1 savegames are internally compressed using ZLIB
//   - Footer for save file contains:
//      - DWORD Checksum
//      - INT CompressionFlags (0x01 is ZLIB)
//      - INT UncompressedSize
// 

typedef byte unsigned char;
struct String;
struct Vector;
struct Rotator;

struct SaveTimeStamp
{
    int Seconds;
    int Day;
    int Month;
    int Year;
};

struct AppearanceSaveRecord
{
    int bHasMorphHead;
};

struct SimpleTalentSaveRecord
{
    int TalentID;
    int CurrentRank;
};

struct ComplexTalentSaveRecord
{
    int TalentID;
    int CurrentRank;
    int MaxRank;
    int LevelOffset;
    int LevelsPerRank;
    int VisualOrder;
    int PrereqIDs[];
    int PrereqRanks[];
};

struct PlayerRecord
{
    int bIsFemale;
    int PlayerClassName;
    byte PlayerClass;
    int Level;
    float CurrentXP;
    String FirstName;
    int LastName;
    byte Origin;
    byte Notoriety;
    int SpecializationBonusId;
    byte SpectreRank;
    int TalentPoints;
    int TalentPoolPoints;
    String MappedTalent;
    AppearanceSaveRecord Appearance;
};

struct ItemModSaveRecord
{
    int ItemId;
    byte Sophistication;
    int Manufacturer;
    int PlotConditionalId;
};

struct ItemSaveRecord
{
    int ItemId;
    byte Sophistication;
    int Manufacturer;
    int PlotConditionalId;
    int bNewItem;
    int bJunkItem;
    ItemModSaveRecord XMods[];
};

struct HenchmanSaveRecord
{
    String Tag;    
    SimpleTalentSaveRecord SimpleTalents[];
    ComplexTalentSaveRecord ComplexTalents[];
    ItemSaveRecord Equipment[];
    ItemSaveRecord Weapons[];
    int TalentPoints;
    int TalentPoolPoints;
    int AutoLevelUpTemplateID;
    int LastName;
    int ClassName;
    byte ClassBase;
    float HealthPerLevel;
    float StabilityCurrent;
    byte Gender;
    byte Race;
    float ToxicCurrent;
    int Stamina;
    int Focus;
    int Precision;
    int Coordination;
    byte AttributePrimary;
    byte AttributeSecondary;
    float HealthCurrent;
    float ShieldCurrent;
    int XPLevel;
    int bHelmetShown;
    byte CurrentQuickSlot;
    float HealthMax;
};

struct LEGACY_BaseObjectSaveRecord
{
    String OwnerName;
    int bHasOwnerClass;
    
    // Only serialized if bHasOwnerClass is true
    String OwnerClassName;
};

struct LEGACY_ActorSaveRecord : public LEGACY_BaseObjectSaveRecord
{
    Vector Location;
    Rotator Rotation;
    Vector Velocity;
    Vector Acceleration;
    int bScriptInitialized;
    int bHidden;
    int bStasis;
};

struct LEGACY_BioPawnSaveRecord : public LEGACY_ActorSaveRecord
{
    float GrimeLevel;
    float GrimeDirtLevel;
    int TalkedToCount;
    int bHeadGearVisiblePreference;
};

struct LEGACY_ActorBehaviorSaveRecord : public LEGACY_BaseObjectSaveRecord
{
    int bIsDead;
    int bGeneratedTreasure;
    int bChallengeScaled;
    int bHasOwner;
    // Only serialized if bHasOwner is true
    String ClassName;
    // Only serialized if bHasOwner is true, Owner is fully serialized into the actor behavior
    LEGACY_BaseObjectSaveRecord Owner;
};

struct LEGACY_ArtPlaceableSaveRecord : public LEGACY_ActorBehaviorSaveRecord
{
    float Health;
    float CurrentHealth;
    int bEnabled;
    String CurrentFSMStateName;
    int bIsDestroyed;
    String State0;
    String State1;
    byte UseCase;
    int bUseCaseOverride;
    int bPlayerOnly;
    byte SkillDifficulty;
    int bHasInventory;
    // Only serialized if bHasInventory is true
    String ClassName;
    // Only serialized if bHasInventory is true, Inventory is fully serialized into the art placeable
    LEGACY_BaseObjectSaveRecord Inventory;
    int bSkilGameFailed;
    int bSkillGameXPAwarded;
};

struct LEGACY_EpicPawnBehaviorSaveRecord : public LEGACY_ActorBehaviorSaveRecord
{
    float HealthCurrent;
    float ShieldCurrent;
    String FirstName;
    int LastName;
    float HealthMax;
    float HealthRegenRate;
    float RadarRange;
};

struct LEGACY_SimpleTalentSaveRecord
{
    int TalentId;
    int Ranks;
};

struct LEGACY_ComplexTalentSaveRecord
{
    int TalentId;
    int Ranks;
    int MaxRank;
    int LevelOffset;
    int LevelsPerRank;
    int VisualOrder;
    int PrereqTalendIdArray[];
    int PrereqTalentRankArray[];
};

struct LEGACY_QuickSlotSaveRecord
{
    int bHasQuickSlot;
    // Only serialized if bHasQuickSlot is true
    String ClassName;
    // Only serialized if bHasQuickSlot is true, quick slot item is fully serialized into the quickslot record
    LEGACY_BaseObjectSaveRecord Item;
};

struct LEGACY_EquipmentSaveRecord
{
    int bHasEquipment;
    // Only serialized if bHasEquipment is true
    String ClassName;
    // Only serialized if bHasEquipment is true
    LEGACY_BaseObjectSaveRecord Item;
};

struct LEGACY_BioPawnBehaviorSaveRecord : public LEGACY_EpicPawnBehaviorSaveRecord
{
    int XPLevel;
    float HealthPerLevel;
    float StabilityCurrent;
	byte Gender;
    byte Race;
    float ToxicCurrent;
    int Stamina;
    int Focus;
    int Precision;
    int Coordination;
    byte QuickSlotCurrent;
    int bHasSquad;
    // Only serialized if bHasSquad is true
    String ClassName;
    // Only serialized if bHasSquad is true    
    LEGACY_BaseObjectSaveRecord Squad;
    int bHasInventory;
    // Only serialized if bHasInventory is true
    String ClassName;
    // Only serialized if bHasInventory is true    
    LEGACY_BaseObjectSaveRecord Inventory;

    int Experience;
	int TalentPoints;
	int TalentPoolPoints;
	byte AttributePrimary;
	byte AttributeSecondary;
	byte ClassBase;
	int LocalizedClassName;
	int AutoLevelUpTemplateID;
	byte SpectreRank;
	byte BackgroundOrigin;
	byte BackgroundNotoriety;
	byte SpecializationBonusID;
    float SkillCharm;
    float SkillIntimidate;
    float SkillHaggle;
    float Audibility;
    float Blindness;
    float DamageDurationMult;
    float Deafness;
    int UnlootableGrenadeCount;
    int bHeadGearVisiblePreference;
    LEGACY_SimpleTalentSaveRecord SimpleTalents[];
    LEGACY_ComplexTalentSaveRecord ComplexTalents[];
    LEGACY_QuickSlotSaveRecord QuickSlots[];
    LEGACY_EquipmentSaveRecord Equipment[];
};

struct LEGACY_ItemSaveRecord : public LEGACY_BaseObjectSaveRecord
{
    String ClassName;
    int Id;
    byte Sophistication;
    int Manufacturer;
    int PlotConditionalId;
};

struct LEGACY_PlotItemSaveRecord
{
    int LocalizedName;
    int LocalizedDesc;
    int ExportId;
    int BasePrice;
    int ShopGUIImageId;
    int PlotConditionalId;
};

struct LEGACY_ItemXModSaveRecord : public LEGACY_ItemSaveRecord
{
    int bHasMod;
    // Only serialized if bHasMod is true
    String ClassName;
    // Only serialized if bHasMod is true
    int Type;
};

struct LEGACY_XModdableSlotSpecRecord
{
    int Type;
    LEGACY_ItemXModSaveRecord XMods[];
};

struct LEGACY_ItemXModdableSaveRecord : public LEGACY_ItemSaveRecord
{
    LEGACY_XModdableSlotSpecRecord SlotSpec[];
};

struct LEGACY_InventorySaveRecord : public LEGACY_BaseObjectSaveRecord
{
    LEGACY_ItemSaveRecord Items[];
    LEGACY_PlotItemSaveRecord PlotItems[];
    int Credits;
    int Grenades;
    float Medigel;
    float Salvage;
};

struct LEGACY_BaseSquadSaveRecord : public LEGACY_BaseObjectSaveRecord
{
    int bHasInventory;
    // Only serialized if bHasInventory is true
    String ClassName;
    // Only serialized if bHasInventory is true, Inventory is fully serialized into the squad
    LEGACY_BaseObjectSaveRecord Inventory;
};

struct LEGACY_BioSquadSaveRecord : public LEGACY_BaseSquadSaveRecord
{
    int SquadXP;
    int MaxLevel;
    int MinLevel;
    int SquadLevel;
};

struct LEGACY_PlayerVehicleSaveRecord : public LEGACY_BaseObjectSaveRecord
{
    String ActorType;
    int bPowertrainEnabled;
    int bVehicleFunctionEnabled;
};

struct LEGACY_ShopSaveRecord : public LEGACY_BaseObjectSaveRecord
{
    int LastPlayerLevel;
    int bIsInitialized;
    LEGACY_BaseObjectSaveRecord Inventory[];
};

struct LEGACY_WorldStreamingStateRecord
{
    String Name;
    int bEnabled;
};

struct LEGACY_WorldSaveRecord : public LEGACY_BaseObjectSaveRecord
{
    LEGACY_WorldStreamingStateRecord StreamingStates[];
    String DestinationAreaMap;
    Vector Destination;
    String CinematicsSeen[];
    int ScannedClusters[];
    int ScannedSystems[];
    int ScannedPlanets[];
    byte JournalSortMethod;
    int bJournalShowingMissions;
    int JournalLastSelectedMission;
    int JournalLastSelectedAssignment;
    int bCodexShowingPrimary;
    int CodexLastSelectedPrimary;
    int CodexLastSelectedSecondary;
    int CurrentTipID;
    int m_OverrideTip;
    byte BrowserAlerts[8];
    int bHasLoot;
    // Only serialized if bHasLoot is true
    String ClassName;
    // Only serailized if bHasLoot is true, Item is fully serialized into the world save object
    LEGACY_BaseObjectSaveRecord PendingLoot;
};

struct LEGACY_LevelSaveRecord
{
    String Name;
    LEGACY_BaseObjectSaveRecord LevelObjects[];
};

struct LEGACY_MapSaveRecord
{
    String Keys[];
    LEGACY_LevelSaveRecord LevelData[];
};

struct VehicleSaveRecord
{
    String FirstName;
    int LastName;
    float HealthCurrent;
    float ShieldCurrent;
};

struct ME1Savegame
{
    // If the top 16 bits have any value set (is not 0), the serialization should be byte swapped. In practice this shouldn't be the case for the released version of the game
    // Valid shipping ME1 save version should be 50
    int Version;

    String CharacterID;

    // When was the career created
    SaveTimeStamp CreatedDate;

    // When was the savegame created
    SaveTimeStamp TimeStamp;

    PlayerRecord PlayerData;

    String BaseLevelName;
    String MapName;
    String ParentMapName;

    Vector Location;
    Rotator Rotation;

    HenchmanSaveRecord HenchmanData[];

    String DisplayName;
    String Filename;

    // The rest of the data in the savegame only serialized for normal savegames, *not* for character export
    // This legacy data is largely unused but is included here for completeness
    LEGACY_MapSaveRecord MapData[];

    VehicleSaveRecord VehicleData;
};