// (c) 2021 Electronic Arts Inc.  All rights reserved.
// 
// FOR REFERENCE PURPOSES ONLY. 
// Electronic Arts does not support or condone any specific mod for use with EA’s games. EA’s User Agreement applies and EA reserves all rights. Use mods with caution at your own risk.
//
// ME2 Savegame file format
// 
// All the data in these structs is laid out in the order in which data is serialized the structs are mainly just used as 
// a way of organizing the data, and are not meant to indicate how the data is organized in memory
// 
// NOTES:
//   - All arrays are serialized with a preceeding integer denoting the number of elements in the array
//   - Footer for save file contains:
//      - DWORD Checksum

typedef unsigned char byte;
typedef int DWORD;
struct String {};
struct Vector {};
struct Rotator {};
struct Vector2D {};

struct SaveTimeStamp
{
    int Seconds;
    int Day;
    int Month;
    int Year;
};

struct Guid
{
    DWORD A, B, C, D;
};

struct LevelSaveRecord
{
    String LevelName;
    int bShouldBeLoaded;
    int bShouldBeVisible;
};

struct StreamingStateSaveRecord
{
    String Name;
    int bActive;
};

struct KismetBoolSaveRecord
{
    Guid BoolGUID;
    int bValue;
};

struct DoorSaveRecord
{
    Guid DoorGUID;
    byte CurrentState;
    byte OldState;
};

struct MorphFeatureSaveRecord
{
    String Feature;
    float Offset;
};

struct OffsetBoneSaveRecord
{
    String Name;
    Vector Offset;
};

struct ScalarParameterSaveRecord
{
    String Name;
    float Value;
};

struct LinearColor
{
    float R, G, B, A;
};

struct VectorParameterSaveRecord
{
    String Name;
    LinearColor Value;
};

struct TextureParameterSaveRecord
{
    String Name;
    String Texture;
};

struct MorphHeadSaveRecord
{
    String HairMesh;
    String AccessoryMeshes[];
    MorphFeatureSaveRecord MorphFeatures[];
    OffsetBoneSaveRecord OffsetBones[];
    Vector Lod0Vertices[];
    Vector Lod1Vertices[];
    Vector Lod2Vertices[];
    Vector Lod3Vertices[];
    ScalarParameterSaveRecord ScalarParameters[];
    VectorParameterSaveRecord VectorParameters[];
    TextureParameterSaveRecord TextureParameters[];
};

struct AppearanceSaveRecord
{
    byte CombatAppearance;
    int CasualID;
    int FullBodyID;
    int TorsoID;
    int ShoulderID;
    int ArmID;
    int LegID;
    int SpecID;
    int Tint1ID;
    int Tint2ID;
    int Tint3ID;
    int PatternID;
    int PatternColorID;
    int HelmetID;

    int bHasMorphHead;
    // Only serialized if bHasMorphHead is true
    MorphHeadSaveRecord MorphHead;
};

struct PowerSaveRecord
{
    String PowerName;
    float CurrentRank;
    String PowerClassName;
    int WheelDisplayIndex;
};

struct WeaponSaveRecord
{
    String WeaponClassName;
    int AmmoUsedCount;
    int TotalAmmo;
    int bLastWeapon;
    int bCurrentWeapon;
    String AmmoPowerName;
};

struct HotKeySaveRecord
{
    String PawnName;
    int PowerID;
};

struct ME1ImportBonusSaveRecord
{
    int IMportedME1Level;
    int StartingME2Level;
    float BonusXP;
    float BonusCredits;
    float BonusResources;
    float BonusParagon;
    float BonusRenegade;
};

struct PlayerRecord
{
    int bIsFemale;
    String PlayerClassName;
    int Level;
    float CurrentXP;
    String FirstName;
    
    // Stringref
    int LastName;

    byte Origin;
    byte Notoriety;

    int TalentPoints;
    String MappedPower1;
    String MappedPower2;
    String MappedPower3;

    AppearanceSaveRecord Appearance;

    PowerSaveRecord Powers[];
    WeaponSaveRecord Weapons[];
    String LoadoutWeapons[6];
    HotKeySaveRecord HotKeys[];

    int Credits;
    int Medigel;
    int Eezo;
    int Iridium;
    int Palladium;
    int Platinum;
    int Probes;
    float CurrentFuel;

    String FaceCode;
    // Stringref
    int ClassFriendlyName;

    ME1ImportBonusSaveRecord ME1ImportBonuses;
};

struct HenchmanSaveRecord
{
    String Tag;
    PowerSaveRecord Powers[];
    int CharacterLevel;
    int TalentPoints;
    String LoadoutWeapons[6];
    String MappedPower;
};

struct PlotQuestSaveRecord
{
    int QuestCounter;
    int bQuestUpdated;
    int History[];
};

struct PlotCodexPageSaveRecord
{
    int Page;
    int bNew;
};

struct PlotCodexSaveRecord
{
    PlotCodexPageSaveRecord Pages[];
};

struct PlotTableSaveRecord
{
    int BoolVariables[];
    int IntVariables[];
    float FloatVariables[];
    int QuestProgressCounter;
    PlotQuestSaveRecord QuestProgress[];
    int QuestIds[];
    PlotCodexSaveRecord CodexEntries[];
    int CodexIds[];
};

struct PlanetSaveRecord
{
    int PlanetID;
    int bVisited;
    Vector2D Probes[];
};

struct GalaxyMapSaveRecord
{
    PlanetSaveRecord Planets[];
};

struct ME1PlotTableRecord
{
    int BoolVariables[];
    int IntVariables[];
    float FloatVariables[];
};

struct DependentDLCRecord
{
    int ModuleID;
    String Name;
};

struct ME2Savegame
{
    // If the top 16 bits have any value set (is not 0), the serialization should be byte swapped. In practice this shouldn't be the case for the released version of the game
    // Valid shipping ME2 save version should be 30
    int Version;

    String DebugName;
    float SecondsPlayed;
    int Disc;
    String BaseLevelName;
    byte Difficulty;

    // 0 - Not finished
    // 1 - Out in a blaze of glory
    // 2 - Lived to fight again
    int EndGameState;

    // When was the savegame created
    SaveTimeStamp TimeStamp;
    Vector SaveLocation;
    Rotator SaveRotation;
    int CurrentLoadingTip;

    LevelSaveRecord LevelRecords[];
    StreamingStateSaveRecord StreamingRecords[];
    KismetBoolSaveRecord KismetRecords[];
    DoorSaveRecord DoorRecords[];
    
    // Dead pawn guids
    Guid PawnRecords[];

    PlayerRecord PlayerData;

    HenchmanSaveRecord HenchmanData[];

    PlotTableSaveRecord PlotRecord;
    ME1PlotTableRecord ME1PlotRecord;

    GalaxyMapSaveRecord GalaxyMapRecord;

    DependentDLCRecord DependentDLC[];
};