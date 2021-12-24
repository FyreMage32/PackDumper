#pragma once

typedef bool ( __thiscall* tCEterPackManagerGet_1 )( void* This, void* rMappedFile, const char* c_szFileName, LPVOID* pData ); // Default
typedef bool ( __thiscall* tCEterPackManagerGet_2 )( void* This, const char* c_szFileName, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, LPVOID* pData, void* rMappedFile ); // https://www.origins2.global/ -> 22/12/2021
typedef bool ( __thiscall* tCEterPackManagerGet_3 )( void* This, void* rMappedFile, const char* c_szFileName, LPVOID* pData );

tCEterPackManagerGet_1 CEterPackManagerGet_1 = NULL;
tCEterPackManagerGet_2 CEterPackManagerGet_2 = NULL;
tCEterPackManagerGet_3 CEterPackManagerGet_3 = NULL;

// + + + //

typedef void* ( __thiscall* tMappedFileLoad )( void* This );

// + + + //

typedef DWORD ( __thiscall* tCMappedFileSize )( void* This );
tCMappedFileSize CMappedFileSize = NULL;

// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

enum ELOGTYPE
{
	MENU_LOG = 1,
	FILE_LOG = 2,
	LOG_BOTH = 3,
};

enum EDUMPMETHOD
{
	BY_PATH_LIST = 1,
	ON_LOAD = 2,
	AUTO_HOOK = 3,
};

// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

#define ENABLE_CONSOLE

const std::string PACK_DUMPER_VERSION_MAJOR = XOR ( "1" );
const std::string PACK_DUMPER_VERSION_MINOR = XOR ( "0" );
const std::string PACK_DUMPER_VERSION_PATCH = XOR ( "0" );
const std::string PACK_DUMPER_VERSION = PACK_DUMPER_VERSION_MAJOR + "." + PACK_DUMPER_VERSION_MINOR + "." + PACK_DUMPER_VERSION_PATCH;

#define OUTPUT_FILE_DIR XOR ( "C:/PackDumper/" )
#define LOG_FILE_DIR    XOR ( "C:/PackDumperLog.txt" )
#define CFG_FILE_DIR    XOR ( "C:/PackDumperCfg.txt" )
#define PATH_LIST_DIR   XOR ( "C:/PackDumperPathList.txt" )

// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

namespace gb
{
	HINSTANCE hLibMod;
	const auto m = ( uintptr_t ) GetModuleHandle ( NULL );

	std::ofstream LogFile;

	uintptr_t CEterPackManager         = 0; // INSTANCE
	uintptr_t ADDR_CEterPackManagerGet = 0;
	uintptr_t ADDR_MappedFileLoad      = 0;
	uintptr_t ADDR_CMappedFileSize     = 0;
	uintptr_t OFST_MappedFileSize      = 0; // Auto Search

	std::vector <uint8_t> v_MappedFileBuffer ( 0x4000 );
}
