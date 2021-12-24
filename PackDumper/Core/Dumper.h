#pragma once

class CDumper
{
public:
	static void        InitMenu ();

	static void        Log               ( std::string m, uint8_t LogType );
	static std::string GetFilePath       ( std::string c_szFileName );
	static std::string GetFileDir        ( std::string FilePath );
	static std::string GetFileName       ( std::string FilePath );
	static void        CreateDir         ( std::string Path );
	static DWORD       GetMappedFileSize ( void* rMappedFile );
	static void        DumpMappedFile    ( std::string Path, LPVOID* pData, DWORD MappedFileSize );

private:
	static void        Init ();
	static void        Quit ();

	static bool        SetCfg ();

	static std::vector <std::string> GetPathList ();

	static bool        DumpByPathList ();
	static bool        DumpOnLoad ();
};

// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

bool __fastcall hk_CEterPackManagerGet_1 ( void* This, void* EDX, void* rMappedFile, const char* c_szFileName, LPVOID* pData ); // Default
bool __fastcall hk_CEterPackManagerGet_2 ( void* This, void* EDX, const char* c_szFileName, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, LPVOID* pData, void* rMappedFile ); // https://www.origins2.global/ -> 22/12/2021
bool __fastcall hk_CEterPackManagerGet_3 ( void* This, void* EDX, void* rMappedFile, const char* c_szFileName, LPVOID* pData );

// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

void CDumper::InitMenu ()
{
#ifdef ENABLE_CONSOLE
	AllocConsole ();
	SetConsoleTitleA ( uf::GetRandomString ( uf::GetRandomNumber ( 8, 12 ) ).c_str () );
	FILE* pFile = nullptr;

	freopen_s ( &pFile, XOR ( "CONOUT$" ), XOR ( "w" ), stdout );
#endif

	gb::LogFile.open ( LOG_FILE_DIR, std::ofstream::trunc ); gb::LogFile.close ();

	if ( !CDumper::SetCfg () ) CDumper::Quit (); // For DumpMethod == AUTO_HOOK Check
	
	CDumper::Log ( XOR ( "[+] Hello, Friend =)" ), ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "[+] PackDumper Version -> " ) + PACK_DUMPER_VERSION, ELOGTYPE::LOG_BOTH );

	if ( cfg::DumpMethod == EDUMPMETHOD::BY_PATH_LIST )
	{
		CDumper::Log ( XOR ( "" ), ELOGTYPE::LOG_BOTH );
		CDumper::Log ( XOR ( "[+] Dump -> INSERT" ), ELOGTYPE::LOG_BOTH );
	}

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	if ( cfg::DumpMethod == EDUMPMETHOD::AUTO_HOOK )
	{
#ifdef ENABLE_CONSOLE
		system ( XOR ( "cls" ) );
#endif
		gb::LogFile.open ( LOG_FILE_DIR, std::ofstream::trunc ); gb::LogFile.close ();

		CDumper::Init ();
	}

	else
	{
		while ( true )
		{
			if ( GetAsyncKeyState ( VK_INSERT ) )
			{
#ifdef ENABLE_CONSOLE
				system ( XOR ( "cls" ) );
#endif
				gb::LogFile.open ( LOG_FILE_DIR, std::ofstream::trunc ); gb::LogFile.close ();

				CDumper::Init ();

				Sleep ( 1000 );
			}
		
			Sleep ( 100 );
		}
	}
}

void CDumper::Log ( std::string m, uint8_t LogType )
{
#ifdef ENABLE_CONSOLE
	if ( LogType == ELOGTYPE::LOG_BOTH || LogType == ELOGTYPE::MENU_LOG )
	{
		printf ( XOR ( "%s\n" ), m.c_str () );
	}
#endif

	if ( LogType == ELOGTYPE::LOG_BOTH || LogType == ELOGTYPE::FILE_LOG )
	{
		gb::LogFile.open ( LOG_FILE_DIR, std::ios::app );

		if ( !gb::LogFile.is_open () ) return;

		gb::LogFile << m << XOR ( "\n" );

		gb::LogFile.close ();
	}
}

std::string CDumper::GetFilePath ( std::string c_szFileName )
{
	c_szFileName = uf::StrFromTo ( c_szFileName, std::string ( XOR ( "d:/" ) ),  std::string ( "" ) );
	c_szFileName = uf::StrFromTo ( c_szFileName, std::string ( XOR ( "d:\\" ) ), std::string ( "" ) );
	c_szFileName = uf::StrFromTo ( c_szFileName, std::string ( XOR ( "D:/" ) ),  std::string ( "" ) );
	c_szFileName = uf::StrFromTo ( c_szFileName, std::string ( XOR ( "D:\\" ) ), std::string ( "" ) );
	c_szFileName = uf::StrFromTo ( c_szFileName, std::string ( XOR ( "\\" ) ),   std::string ( XOR ( "/" ) ) );

	return c_szFileName;
}

std::string CDumper::GetFileDir ( std::string FilePath )
{
	std::string FileDir;

	size_t Div = FilePath.find_last_of ( XOR ( "/" ) );
	Div != std::string::npos ? FileDir = FilePath.substr ( 0, Div + 1 ) : FileDir = "";

	return FileDir;
}

std::string CDumper::GetFileName ( std::string FilePath )
{
	std::string FileName;

	size_t Div = FilePath.find_last_of ( XOR ( "/" ) );
	Div != std::string::npos ? FileName = FilePath.substr ( Div + 1, FilePath.size () ) : FileName = FilePath;

	return FileName;
}

void CDumper::CreateDir ( std::string Path )
{
	if ( std::filesystem::exists ( Path ) ) return;

	std::filesystem::create_directories ( Path );
	std::filesystem::permissions ( Path, std::filesystem::perms::others_all, std::filesystem::perm_options::remove );
}

DWORD CDumper::GetMappedFileSize ( void* rMappedFile )
{
	if ( cfg::DumpMethod == EDUMPMETHOD::BY_PATH_LIST && cfg::CMappedFileSize_RVA == 1 )
	{
		return *( uintptr_t* ) ( ( uintptr_t ) ( rMappedFile ) + gb::OFST_MappedFileSize );
	}

	return CMappedFileSize ( rMappedFile );
}

void CDumper::DumpMappedFile ( std::string Path, LPVOID* pData, DWORD MappedFileSize )
{
	std::ofstream OutFile;

	OutFile.open ( Path, std::ios::binary );

	if ( OutFile.is_open () )
	{
		DWORD dwData = *reinterpret_cast< DWORD* >( pData );
		const char* Data = ( const char* ) dwData;

		OutFile.write ( Data, MappedFileSize );
		OutFile.close ();
	}
}

void CDumper::Init ()
{
	if ( !CDumper::SetCfg () ) CDumper::Quit ();

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	CDumper::Log ( XOR ( "[+] Hello, Friend =)"               ),                                         ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "[+] PackDumper Version -> "         ) + PACK_DUMPER_VERSION,                   ELOGTYPE::LOG_BOTH );

	if ( cfg::DumpMethod != EDUMPMETHOD::AUTO_HOOK )
	{
		CDumper::Log ( XOR ( ""                               ),                                         ELOGTYPE::LOG_BOTH );
		CDumper::Log ( XOR ( "[+] Dump -> INSERT"             ),                                         ELOGTYPE::LOG_BOTH );
	}

	CDumper::Log ( XOR ( ""                                   ),                                         ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "[+] Current Cfg"                    ),                                         ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "- DumpMethod -> "                   ) + cfg::Str_DumpMethod,                   ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "- CEterPackManagerGet_CallType -> " ) + cfg::Str_CEterPackManagerGet_CallType, ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "- pCEterPackManager_RVA -> "        ) + cfg::Str_pCEterPackManager_RVA,        ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "- CEterPackManagerGet_RVA -> "      ) + cfg::Str_CEterPackManagerGet_RVA,      ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "- MappedFileLoad_RVA -> "           ) + cfg::Str_MappedFileLoad_RVA,           ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "- CMappedFileSize_RVA -> "          ) + cfg::Str_CMappedFileSize_RVA,          ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( ""                                   ),                                         ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "[+] Init"                           ),                                         ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( ""                                   ),                                         ELOGTYPE::LOG_BOTH );

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	gb::CEterPackManager         = *( uintptr_t* ) ( gb::m + cfg::pCEterPackManager_RVA );
	gb::ADDR_CEterPackManagerGet = gb::m + cfg::CEterPackManagerGet_RVA;
	gb::ADDR_MappedFileLoad      = gb::m + cfg::MappedFileLoad_RVA;
	gb::ADDR_CMappedFileSize     = gb::m + cfg::CMappedFileSize_RVA;

	CEterPackManagerGet_1 = ( tCEterPackManagerGet_1 ) gb::ADDR_CEterPackManagerGet;
	CEterPackManagerGet_2 = ( tCEterPackManagerGet_2 ) gb::ADDR_CEterPackManagerGet;
	CEterPackManagerGet_3 = ( tCEterPackManagerGet_3 ) gb::ADDR_CEterPackManagerGet;

	CMappedFileSize       = ( tCMappedFileSize ) gb::ADDR_CMappedFileSize;

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	if ( cfg::DumpMethod == EDUMPMETHOD::BY_PATH_LIST )
	{
		if ( !CDumper::DumpByPathList () ) CDumper::Quit ();
	}

	else if ( cfg::DumpMethod == EDUMPMETHOD::ON_LOAD || cfg::DumpMethod == EDUMPMETHOD::AUTO_HOOK )
	{
		if ( !CDumper::DumpOnLoad () ) CDumper::Quit ();
	}
}

void CDumper::Quit ()
{
	CDumper::Log ( XOR ( "[!] Error Detected -> Exiting Dumper" ), ELOGTYPE::LOG_BOTH );
#ifdef ENABLE_CONSOLE
	CDumper::Log ( XOR ( "" ), ELOGTYPE::MENU_LOG );

	system ( XOR ( "Pause" ) );
#endif

	PostMessage ( GetConsoleWindow (), WM_QUIT, 0, 0 );
	FreeConsole ();
	FreeLibraryAndExitThread ( gb::hLibMod, 0 );
}

bool CDumper::SetCfg ()
{
	std::ifstream CfgFile;

	CfgFile.open ( CFG_FILE_DIR );

	if ( !CfgFile.is_open () )
	{
		CDumper::Log ( XOR ( "[!] Failed to Open -> C:/PackDumperCfg.txt" ), ELOGTYPE::LOG_BOTH );
		return false;
	}

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	std::vector <std::string> CfgFileLines;
	std::string CurLine;

	while ( std::getline ( CfgFile, CurLine ) )
	{
		if ( CurLine.empty () || ( CurLine[0] == '-' && CurLine[1] == '-' ) ) continue;

		CfgFileLines.push_back ( CurLine );
	}

	CfgFile.close ();

	if ( CfgFileLines.empty () )
	{
		CDumper::Log ( XOR ( "[!] Empty File -> C:/PackDumperCfg.txt" ), ELOGTYPE::LOG_BOTH );
		return false;
	}

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	for ( auto Line : CfgFileLines )
	{
		std::string EntryVal = Line.substr ( Line.find ( XOR ( "\t" ), 0 ) + 1, Line.size () );

		uintptr_t i_EntryVal = atoi ( EntryVal.c_str () );

		uintptr_t i_HexVal;
		std::stringstream HexVal;
		HexVal << std::hex << EntryVal;
		HexVal >> i_HexVal;

		// + + + //

		if ( Line.find ( XOR ( "DumpMethod" ), 0 ) != std::string::npos )
		{
			if ( EntryVal == "" || ( i_EntryVal != 1 && i_EntryVal != 2 && i_EntryVal != 3 ) )
			{
				CDumper::Log ( XOR ( "[!] Cfg Error Detected -> DumpMethod Error" ), ELOGTYPE::LOG_BOTH );
				return false;
			}

			cfg::Str_DumpMethod = EntryVal;
			cfg::DumpMethod = i_EntryVal;
			continue;
		}

		// + + + //

		if ( Line.find ( XOR ( "CEterPackManagerGet_CallType" ), 0 ) != std::string::npos )
		{
			if ( EntryVal == "" || i_EntryVal < 1 || i_EntryVal > 20 )
			{
				CDumper::Log ( XOR ( "[!] Cfg Error Detected -> CEterPackManagerGet_CallType Error" ), ELOGTYPE::LOG_BOTH );
				return false;
			}

			cfg::Str_CEterPackManagerGet_CallType = EntryVal;
			cfg::CEterPackManagerGet_CallType = i_EntryVal;
			continue;
		}

		// + + + //

		if ( Line.find ( XOR ( "pCEterPackManager_RVA" ), 0 ) != std::string::npos )
		{
			if ( EntryVal == "" || i_HexVal == 0 )
			{
				CDumper::Log ( XOR ( "[!] Cfg Error Detected -> pCEterPackManager_RVA Error" ), ELOGTYPE::LOG_BOTH );
				return false;
			}

			cfg::Str_pCEterPackManager_RVA = EntryVal;
			cfg::pCEterPackManager_RVA = i_HexVal;
			continue;
		}

		// + + + //

		if ( Line.find ( XOR ( "CEterPackManagerGet_RVA" ), 0 ) != std::string::npos )
		{
			if ( EntryVal == "" || i_HexVal == 0 )
			{
				CDumper::Log ( XOR ( "[!] Cfg Error Detected -> CEterPackManagerGet_RVA Error" ), ELOGTYPE::LOG_BOTH );
				return false;
			}

			cfg::Str_CEterPackManagerGet_RVA = EntryVal;
			cfg::CEterPackManagerGet_RVA = i_HexVal;
			continue;
		}

		// + + + //

		if ( Line.find ( XOR ( "MappedFileLoad_RVA" ), 0 ) != std::string::npos )
		{
			if ( EntryVal == "" || i_HexVal == 0 )
			{
				CDumper::Log ( XOR ( "[!] Cfg Error Detected -> MappedFileLoad_RVA Error" ), ELOGTYPE::LOG_BOTH );
				return false;
			}

			cfg::Str_MappedFileLoad_RVA = EntryVal;
			cfg::MappedFileLoad_RVA = i_HexVal;
			continue;
		}

		// + + + //

		if ( Line.find ( XOR ( "CMappedFileSize_RVA" ), 0 ) != std::string::npos )
		{
			if ( EntryVal == "" || i_HexVal == 0 )
			{
				CDumper::Log ( XOR ( "[!] Cfg Error Detected -> CMappedFileSize_RVA Error" ), ELOGTYPE::LOG_BOTH );
				return false;
			}

			cfg::Str_CMappedFileSize_RVA = EntryVal;
			cfg::CMappedFileSize_RVA = i_HexVal;
			continue;
		}
	}

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	if ( cfg::DumpMethod != EDUMPMETHOD::BY_PATH_LIST && cfg::CMappedFileSize_RVA == 1 )
	{
		CDumper::Log ( XOR ( "[!] Cfg Error Detected -> CMappedFileSize_RVA Error -> Auto Discover is only allowed if DumpMethod == 1 (BY_PATH_LIST)" ), ELOGTYPE::LOG_BOTH );
		return false;
	}

	return true;
}

std::vector <std::string> CDumper::GetPathList ()
{
	std::vector <std::string> PathList;
	std::vector <std::string> TempPathList;

	std::ifstream PathListFile;

	PathListFile.open ( PATH_LIST_DIR );

	if ( !PathListFile.is_open () )
	{
		CDumper::Log ( XOR ( "[!] Failed to Open -> C:/PackDumperPathList.txt" ), ELOGTYPE::LOG_BOTH );
		return PathList;
	}

	PathList.reserve ( 80 * 10000 );
	TempPathList.reserve ( 80 * 10000 );

	CDumper::Log ( XOR ( "[+] Getting Lines and Removing Dupes From -> C:/PackDumperPathList.txt\n" ), ELOGTYPE::LOG_BOTH );

	std::string CurLine;

	while ( std::getline ( PathListFile, CurLine ) )
	{
		if ( CurLine.empty () || ( CurLine[0] == '-' && CurLine[1] == '-' ) ) continue;

		bool IsValidPath = true;

		for ( auto c : CurLine )
		{
			if ( static_cast< unsigned char >( c ) < 32 ) // Check Bad ASCII Character
			{
				CDumper::Log ( XOR ( "[Fail] Path Error - Bad ASCII Character Found -> " ) + CurLine, ELOGTYPE::LOG_BOTH );
				IsValidPath = false;
				break;
			}
		}

		if ( IsValidPath ) TempPathList.push_back ( CurLine );
	}

	PathListFile.close ();

	if ( TempPathList.empty () )
	{
		CDumper::Log ( XOR ( "[!] Empty File -> C:/PackDumperPathList.txt" ), ELOGTYPE::LOG_BOTH );
		return PathList;
	}

	std::sort ( TempPathList.begin (), TempPathList.end () );

	for ( const std::string& TempPath : TempPathList ) // Remove Dupes
	{
		if ( !std::binary_search ( PathList.begin (), PathList.end (), TempPath ) )
		{
			PathList.push_back ( TempPath );
		}
	}

	PathList.shrink_to_fit ();

	return PathList;
}

bool CDumper::DumpByPathList ()
{
	bool bRet;

	std::vector <std::string> PathList = CDumper::GetPathList ();

	if ( PathList.empty () ) return false;

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	reinterpret_cast< tMappedFileLoad >( gb::ADDR_MappedFileLoad )( &gb::v_MappedFileBuffer[0] );

	if ( gb::v_MappedFileBuffer.empty () )
	{
		CDumper::Log ( XOR ( "[!] Empty -> v_MappedFileBuffer" ), ELOGTYPE::LOG_BOTH );
		return false;
	}

	// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

	for ( auto& Path : PathList )
	{
		std::string FilePath = CDumper::GetFilePath ( Path ); // Get Fixed Path
		void* pData = nullptr;

		switch ( cfg::CEterPackManagerGet_CallType )
		{
			case 1: // Default
			{
				bRet = CEterPackManagerGet_1 ( ( void* ) gb::CEterPackManager, &gb::v_MappedFileBuffer[0], Path.c_str (), &pData );
				break;
			}

			case 2: // https://www.origins2.global/ -> 22/12/2021
			{
				bRet = CEterPackManagerGet_2 ( ( void* ) gb::CEterPackManager, Path.c_str (), 1, 1, 1, 1, 1, 63754643, 1, 1, 0x18C5CF4, &pData, &gb::v_MappedFileBuffer[0] );
				break;
			}

			case 3:
			{
				bRet = CEterPackManagerGet_3 ( ( void* ) gb::CEterPackManager, &gb::v_MappedFileBuffer[0], Path.c_str (), &pData );
				break;
			}

			default:
			{
				CDumper::Log ( XOR ( "[!] CEterPackManagerGet_CallType Error Detected -> CallType Not Found" ), ELOGTYPE::LOG_BOTH );
				return false;
			}
		}

		if ( !bRet || !pData )
		{
			CDumper::Log ( XOR ( "[Fail] !bRet || !pData -> " ) + FilePath, ELOGTYPE::LOG_BOTH );
			continue;
		}

		// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

		if ( cfg::CMappedFileSize_RVA == 1 && !gb::OFST_MappedFileSize ) // Try Auto Discover MappedFile Size
		{
			auto pStart = reinterpret_cast< uintptr_t >( &gb::v_MappedFileBuffer[0] );

			while ( !gb::OFST_MappedFileSize )
			{
				if ( *( uintptr_t* ) pStart == reinterpret_cast< uintptr_t >( pData ) )
				{
					gb::OFST_MappedFileSize = ( pStart - ( uintptr_t ) ( &gb::v_MappedFileBuffer[0] ) ) + sizeof ( uintptr_t );
					break;
				}

				++pStart;
			}
		}

		DWORD MappedFileSize = CDumper::GetMappedFileSize ( &gb::v_MappedFileBuffer[0] );

		if ( !MappedFileSize )
		{
			CDumper::Log ( XOR ( "[Fail] !MappedFileSize -> " ) + FilePath, ELOGTYPE::LOG_BOTH );
			continue;
		}

		// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

		uf::EraseInStr ( FilePath, XOR ( "ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "YMIR WORK/" ) );

		CDumper::CreateDir ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) );

		CDumper::DumpMappedFile ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) + CDumper::GetFileName ( FilePath ), &pData, MappedFileSize );

		// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

		std::stringstream Temp;

		Temp << std::hex << ( uintptr_t ) ( &gb::v_MappedFileBuffer[0] );
		std::string Str_rMappedFile = Temp.str ();
		Temp.str ( "" );

		Temp << std::hex << pData;
		std::string Str_pData = Temp.str ();
		Temp.str ( "" );

		Temp << std::setfill ( '0' ) << std::setw ( 7 ) << std::to_string ( MappedFileSize );
		std::string Str_MappedFileSize = Temp.str ();
		Temp.str ( "" );

		CDumper::Log ( XOR ( "[Dumped] rMappedFile -> " ) + Str_rMappedFile + XOR ( " | pData -> " ) + Str_pData + XOR ( " [" ) + Str_MappedFileSize + XOR ( "]\t " ) + FilePath, ELOGTYPE::LOG_BOTH );
	}

	CDumper::Log ( XOR ( "" ), ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "[+] Dump Finished !" ), ELOGTYPE::LOG_BOTH );

	return true;
}

bool CDumper::DumpOnLoad ()
{
	switch ( cfg::CEterPackManagerGet_CallType )
	{
		case 1: // Default
		{
			CEterPackManagerGet_1 = ( tCEterPackManagerGet_1 ) DetourFunction ( ( PBYTE ) gb::ADDR_CEterPackManagerGet, ( PBYTE ) hk_CEterPackManagerGet_1 );
			break;
		}

		case 2: // https://www.origins2.global/ -> 22/12/2021
		{
			CEterPackManagerGet_2 = ( tCEterPackManagerGet_2 ) DetourFunction ( ( PBYTE ) gb::ADDR_CEterPackManagerGet, ( PBYTE ) hk_CEterPackManagerGet_2 );
			break;
		}

		case 3:
		{
			CEterPackManagerGet_3 = ( tCEterPackManagerGet_3 ) DetourFunction ( ( PBYTE ) gb::ADDR_CEterPackManagerGet, ( PBYTE ) hk_CEterPackManagerGet_3 );
			break;
		}
		
		default:
		{
			CDumper::Log ( XOR ( "[!] CEterPackManagerGet_CallType Error Detected -> CallType Not Found" ), ELOGTYPE::LOG_BOTH );
			return false;
		}
	}

	if ( *( BYTE* ) gb::ADDR_CEterPackManagerGet != 0xE9 ) // Jmp
	{
		CDumper::Log ( XOR ( "[!] Failed to Hook CEterPackManagerGet" ), ELOGTYPE::LOG_BOTH );
		return false;
	}

	CDumper::Log ( XOR ( "[+] CEterPackManagerGet Hooked" ), ELOGTYPE::LOG_BOTH );
	CDumper::Log ( XOR ( "" ), ELOGTYPE::LOG_BOTH );

	return true;
}

// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //
// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

bool __fastcall hk_CEterPackManagerGet_1 ( void* This, void* EDX, void* rMappedFile, const char* c_szFileName, LPVOID* pData )
{
	bool bRet; // Don't Define Directly !
	bRet = CEterPackManagerGet_1 ( This, rMappedFile, c_szFileName, pData );

	std::string FilePath = CDumper::GetFilePath ( c_szFileName ); // Get Fixed Path

	DWORD MappedFileSize = CDumper::GetMappedFileSize ( rMappedFile );

	if ( MappedFileSize )
	{
		uf::EraseInStr ( FilePath, XOR ( "ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "YMIR WORK/" ) );

		CDumper::CreateDir ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) );

		CDumper::DumpMappedFile ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) + CDumper::GetFileName ( FilePath ), pData, MappedFileSize );

		// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

		std::stringstream Temp;

		Temp << std::hex << rMappedFile;
		std::string Str_rMappedFile = Temp.str ();
		Temp.str ( "" );

		Temp << std::hex << pData;
		std::string Str_pData = Temp.str ();
		Temp.str ( "" );

		Temp << std::setfill ( '0' ) << std::setw ( 7 ) << std::to_string ( MappedFileSize );
		std::string Str_MappedFileSize = Temp.str ();
		Temp.str ( "" );

		CDumper::Log ( XOR ( "[Dumped] rMappedFile -> " ) + Str_rMappedFile + XOR ( " | pData -> " ) + Str_pData + XOR ( " [" ) + Str_MappedFileSize + XOR ( "]\t " ) + FilePath, ELOGTYPE::LOG_BOTH );
	}

	else
	{
		CDumper::Log ( XOR ( "[Fail] !MappedFileSize -> " ) + FilePath, ELOGTYPE::LOG_BOTH );
	}

	return bRet;
}

bool __fastcall hk_CEterPackManagerGet_2 ( void* This, void* EDX, const char* c_szFileName, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, LPVOID* pData, void* rMappedFile )
{
	bool bRet; // Don't Define Directly !
	bRet = CEterPackManagerGet_2 ( This, c_szFileName, a1, a2, a3, a4, a5, a6, a7, a8, a9, pData, rMappedFile );

	std::string FilePath = CDumper::GetFilePath ( c_szFileName ); // Get Fixed Path

	DWORD MappedFileSize = CDumper::GetMappedFileSize ( rMappedFile );

	if ( MappedFileSize )
	{
		uf::EraseInStr ( FilePath, XOR ( "ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "YMIR WORK/" ) );

		CDumper::CreateDir ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) );

		CDumper::DumpMappedFile ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) + CDumper::GetFileName ( FilePath ), pData, MappedFileSize );

		// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

		std::stringstream Temp;

		Temp << std::hex << rMappedFile;
		std::string Str_rMappedFile = Temp.str ();
		Temp.str ( "" );

		Temp << std::hex << pData;
		std::string Str_pData = Temp.str ();
		Temp.str ( "" );

		Temp << std::setfill ( '0' ) << std::setw ( 7 ) << std::to_string ( MappedFileSize );
		std::string Str_MappedFileSize = Temp.str ();
		Temp.str ( "" );

		CDumper::Log ( XOR ( "[Dumped] rMappedFile -> " ) + Str_rMappedFile + XOR ( " | pData -> " ) + Str_pData + XOR ( " [" ) + Str_MappedFileSize + XOR ( "]\t " ) + FilePath, ELOGTYPE::LOG_BOTH );
	}

	else
	{
		CDumper::Log ( XOR ( "[Fail] !MappedFileSize -> " ) + FilePath, ELOGTYPE::LOG_BOTH );
	}

	return bRet;
}

bool __fastcall hk_CEterPackManagerGet_3 ( void* This, void* EDX, void* rMappedFile, const char* c_szFileName, LPVOID* pData )
{
	bool bRet; // Don't Define Directly !
	bRet = CEterPackManagerGet_3 ( This, rMappedFile, c_szFileName, pData );

	std::string FilePath = CDumper::GetFilePath ( c_szFileName ); // Get Fixed Path

	DWORD MappedFileSize = CDumper::GetMappedFileSize ( rMappedFile );

	if ( MappedFileSize )
	{
		uf::EraseInStr ( FilePath, XOR ( "ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "Ymir work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "ymir Work/" ) );
		uf::EraseInStr ( FilePath, XOR ( "YMIR WORK/" ) );

		CDumper::CreateDir ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) );

		CDumper::DumpMappedFile ( OUTPUT_FILE_DIR + CDumper::GetFileDir ( FilePath ) + CDumper::GetFileName ( FilePath ), pData, MappedFileSize );

		// + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + //

		std::stringstream Temp;

		Temp << std::hex << rMappedFile;
		std::string Str_rMappedFile = Temp.str ();
		Temp.str ( "" );

		Temp << std::hex << pData;
		std::string Str_pData = Temp.str ();
		Temp.str ( "" );

		Temp << std::setfill ( '0' ) << std::setw ( 7 ) << std::to_string ( MappedFileSize );
		std::string Str_MappedFileSize = Temp.str ();
		Temp.str ( "" );

		CDumper::Log ( XOR ( "[Dumped] rMappedFile -> " ) + Str_rMappedFile + XOR ( " | pData -> " ) + Str_pData + XOR ( " [" ) + Str_MappedFileSize + XOR ( "]\t " ) + FilePath, ELOGTYPE::LOG_BOTH );
	}

	else
	{
		CDumper::Log ( XOR ( "[Fail] !MappedFileSize -> " ) + FilePath, ELOGTYPE::LOG_BOTH );
	}

	return bRet;
}
