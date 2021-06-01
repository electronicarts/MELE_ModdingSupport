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

struct DLCMountingInfo
{
    // Latest global package version
    int VersionPackage;

    // Latest licensee global package version
    int VersionLicensee;

    // Latest cooked file version (combination of global package version and licensee package versions)
    int VersionCooked;

    // Unique ID for the DLC module, also used to determine mounting order (ascending)
    int ModuleID;

    // DLCMountingInfo file version
    int VersionDLCMountingInfo;

    // Guid of the TFC for this DLC, if non-zero the guid needs to match the TFC guid in the DLC
    Guid TextureCacheGuid;

    // Development DLC version
    int VersionDLC;

    // 0x00 - None
    // 0x01 - Cerberus DLC
    // 0x02 - Save Locked, if set the DLC must be present to load a savegame that was saved while this was mounted
    int Flags;

    // String name of the DLC
    FString FriendlyName;

    // Strref name of the DLC
    STRREF srFriendlyName;

    // Folder name of the DLC
    FString CodeName;

    // Min build version required in order to mount the DLC
    int MinBuildVersion;
    
    // Strref name of the DLC package
    STRREF srPackageName;
};