// (c) 2021 Electronic Arts Inc.  All rights reserved.
// 
// FOR REFERENCE PURPOSES ONLY. 
// Electronic Arts does not support or condone any specific mod for use with EA’s games. EA’s User Agreement applies and EA reserves all rights. Use mods with caution at your own risk.
// 
// Mount DLC File Format
// 
// All the data is laid out in the order in which data is serialized and are not meant to indicate how the data is organized in memory
// 

typedef DWORD unsigned int;
typedef STRREF unsigned int;

class FString;

struct Guid
{
    DWORD A;
    DWORD B;
    DWORD C;
    DWORD D;
};

struct FFileVersion
{
    // Latest global package version    
    int PackageFileVersion;

    // Latest licensee global package version    
    int PackageFileLicenseeVersion;

    // Latest cooked file version (combination of global package version and licensee package versions)    
    int PackageFileCookedContentVersion;
};

struct FBuildVersion
{
    int MajorVersion;
    int MinorVersion;
};

struct FMountingInfo
{
    // Internal version for mount info struct
    int MountingInfoVersion;

    // File version information
    FFileVersion FileVersion;

    // Unique ID for the DLC module, also used to determine mounting order (ascending)
    int ModuleID;

    // Development DLC version
    int Version;

    // 0x00 - None
    // 0x01 - Save locked (savegames made while this module is mounted require it to be mounted in order to load again)
    // 0x02 - Mismatch
    // 0x04 - Multiplayer
    // 0x08 - Singleplayer
    // 0x10 - Matchmaking
    // 0x20 - GoBig
    DWORD Flags;

    // Strref description of the DLC
    STRREF ContentName;

    // Strref name of the package
    STRREF PackageName;

    // Minimum build version required to mount this DLC
    FBuildVersion MinBuildVersion;

    // Guids for TFCs included in this DLC, used to validate DLC - if zero guid then the validation checks are skipped
    Guid BaseTFCGuid;
    Guid CharacterTFCGuid;
    Guid LightingTFCGuid;
    Guid MovieTFCGuid;    
};