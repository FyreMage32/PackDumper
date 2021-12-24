# PackDumper
Metin2 Resource Dumper/Extractor Tool. Dump 100% of the resources from almost any Metin2 Client

# How to Compile
✔️ Clone the project and compile as x86

✔️ You need to re-target if not in Visual Studio 2022. I tested it in Visual Studio 2019 and it works fine too

✔️ If you want to re-target manually:

```
Configuration Type -> Dynamic Library (.dll)
Plataform Toolset -> Visual Studio 2022 (v143) or Visual Studio 2019 (v142)
C++ Language Standard -> ISO C++ 20 Standard
Character Set -> Multi-Byte
Include Library Directories -> $(ProjectDir)_Extern
Safe Exception Handlers -> No (/SAFESEH:NO)
```

# How to Use
✔️ Configure the ``PackDumperCfg.txt`` file with the required informations. Check [PackDumperCfg File Explanations](https://github.com/FyreMage32/PackDumper/blob/main/README.md#packdumpercfg-file-explanations)

✔️ If you've set DumpMethod = 1 (BY_PATH_LIST), you also need to make a ``PackDumperPathList.txt`` first. Check [PackDumperPathList File Explanations](https://github.com/FyreMage32/PackDumper/blob/main/README.md#packdumperpathlist-file-explanations)

✔️ Move ``PackDumperCfg.txt`` and ``PackDumperPathList.txt`` (the last, just in case you made one) to your ``Local Disk (C:\)``

✔️ Inject ``PackDumper.dll`` into the client

✔️ Unless you've set DumpMethod = 3 (AUTO_HOOK), you need to ``press INSERT`` to start dumping

📌 Files are dumped to ``C:\PackDumper``

📌 A ``PackDumperLog.txt`` file will be generated to your ``Local Disk (C:\)``. It contains useful informations, always check it!

📌 Check [Hints you Should Know](https://github.com/FyreMage32/PackDumper/blob/main/README.md#hints-you-should-know) to get extra tips

# Hints you Should Know
✔️ The PackDumperCfg.txt file is loaded everytime before you start dumping something. It means you don't need to close the client to update some configuration

✔️ If you've set DumpMethod = 1 (BY_PATH_LIST) and you didn't enabled the console window in the source, a way to know the dumper finished it's work is by checking if the PackDumperLog.txt size stopped increasing (or just open it xD)

✔️ Once the game is hooked (DumpMethod 2 and 3), the dumper will never finish. If you want to stop, close the client

# PackDumperCfg File Explanations
✔️ PackDumperCfg.txt is always read from your Local Disk (C:\\)

✔️ PackDumperCfg file follows the following patterns:
* Property Entry -> Property[TAB]Value
* Comment Line -> Starts with "--"

✔️ Check [Getting the Cfg Properties](https://github.com/FyreMage32/PackDumper/blob/main/README.md#getting-the-cfg-properties) to get hints about how to get RVA's from functions and classes

-------------
``Property -> DumpMethod`` 
* DumpMethod = 1 (BY_PATH_LIST) -> Works by calling CEterPackManager::Get() with a specific path as c_szFileName argument. You can make a PackDumperPathList.txt with PathListDumper.CT (CheatEngine Script). It's 100% automated and you can get ALL paths for ALL files inside the "pack" folder of your client. Check [PackDumperPathList File Explanations](https://github.com/FyreMage32/PackDumper/blob/main/README.md#packdumperpathlist-file-explanations)
* DumpMethod = 2 (ON_LOAD) -> Works by hooking CEterPackManager::Get() to intercept (and copy) every file being loaded by the game
* DumpMethod = 3 (AUTO_HOOK) -> Same as DumpMethod 2 (ON_LOAD), but the hook is automatically placed at the same time you inject the dll. Use it in case you want to dump a file thats loaded only when the client starts (e.g. some files from root)
* Example -> DumpMethod[TAB]1
* Example -> DumpMethod[TAB]2
* Example -> DumpMethod[TAB]3
-------------
``Property -> CEterPackManagerGet_CallType`` 
* The number of the CEterPackManagerGet_NumX function prototype you want to use (e.g., if you want to use the default call type that common Metin2 clients uses, set it to 1, or if you made another custom Get() function prototype, set the number from your custom)
* Example -> CEterPackManagerGet_CallType[TAB]1
* Example -> CEterPackManagerGet_CallType[TAB]2
-------------
``Property -> pCEterPackManager_RVA``
* RVA (Relative Virtual Address) from a pointer to CEterPackManager class
* Example -> pCEterPackManager_RVA[TAB]10ABCD
* Example -> pCEterPackManager_RVA[TAB]0x10ABCD
-------------
``Property -> CEterPackManagerGet_RVA``
* RVA (Relative Virtual Address) from CEterPackManagerGet function
* Example -> CEterPackManagerGet_RVA[TAB]10ABCD
* Example -> CEterPackManagerGet_RVA[TAB]0x10ABCD
-------------
``Property -> MappedFileLoad_RVA``
* RVA (Relative Virtual Address) from MappedFileLoad function
* Example -> MappedFileLoad_RVA[TAB]10ABCD
* Example -> MappedFileLoad_RVA[TAB]0x10ABCD
-------------
``Property -> CMappedFileSize_RVA``
* RVA (Relative Virtual Address) from CMappedFileSize function OR set it to 1 if you want PackDumper try to auto discover the file size by itself. Important: auto discover is only allowed if you've set DumpMethod = 1 (BY_PATH_LIST). If something is going wrong, don't use auto discover!
* Example -> CMappedFileSize_RVA[TAB]1
* Example -> CMappedFileSize_RVA[TAB]10ABCD
* Example -> CMappedFileSize_RVA[TAB]0x10ABCD

# PackDumperPathList File Explanations
✔️ PackDumperPathList.txt is always read from your Local Disk (C:\\)

✔️ You need a PackDumperPathList.txt file just in case you've set DumpMethod = 1 (BY_PATH_LIST). Here you can put the full paths for every file you want to dump

✔️ You can make a list with the paths from ALL files from "pack" folder by using PathListDumper.CT (CheatEngine Script) that's also provided in this repository. Check [PathListDumper Script Explanations](https://github.com/FyreMage32/PackDumper/blob/main/README.md#pathlistdumper-script-explanations)

✔️ PackDumperPathList.txt file example:

```
d:/ymir work/effect/etc/direction/direction_land.mse
d:/ymir work/item/12727.msm
d:/ymir work/item/etc/item_bag.gr2
d:/ymir work/special/error.tga
d:/ymir work/special/snow.dds
d:/ymir work/tree/christmastree1.spt
d:/ymir work/ui/minimap/playermark.sub
game.py
icon/hair/conv.py
locale/x/ui/webwindow.py
metin2_map_spiderdungeon_02/003003/attr.atr
plechi_summer2019_dungeon/002003/water.wtr
property/b/ambience/warp.pra
season1/metin2_map_skipia_dungeon_01/skipia_dungeon.msenv
season1/monster/ch_bowman/shape.msm
serverinfo.py
sound/monster2/zombie_soldier_bow/30_1.mss
system.py
uiscript/mallwindow.py
```

# PathListDumper Script Explanations
✔️ PathListDumper.CT is a CheatEngine Lua Script used to get paths from ALL files inside the "pack" folder of your client

✔️ How to Use:
* Download and install CheatEngine 7.0 or higger (https://www.cheatengine.org/)
* Open PathListDumper.CT into CheatEngine (e.g., by draging and droping it into CE)
* Login your character to some map (if you dump paths while in login or in character selection window, much paths won't be dumped to the list)
* "Active" the script and wait till finish
* A file called "PackDumperPathList.txt" will be generated to your desktop. Just move it too the Local Disk (C:\\)
* Done!

# Getting the Cfg Properties
✔️ Patterns (Default Client):

``pCEterPackManager [+2]`` -> 8B 0D ? ? ? ? 8D 85 ? ? ? ? 83 C4 ? 50 56

``CEterPackManagerGet`` -> 55 8B EC 53 8B 5D ? 56 57 8B 7D ? 8B F1 57 53 FF 75 ? 83 7E 08

``MappedFileLoad`` -> 55 8B EC 51 56 8B F1 89 75 ? E8 ? ? ? ? C7 06 ? ? ? ? 8B C6 C7 86 18 01 00 00

``CMappedFileSize`` -> 8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 55 8B EC 56 FF 75 ? 8B F1 FF 15

✔️ Useful Strings:

``CPythonNonPlayer::LoadNonPlayerData: %s, sizeof(TMobTable)=%u\n``

``CResource::Load file not exist %s\n``

``CResource::Reload %s\n``

✔️ Assembly Examples (Default Client):
<details>
  <summary>Region with references to pCEterPackManager, CEterPackManagerGet & MappedFileLoad</summary>

```assembly
metin2client.bin+BED20 - 55                    - push ebp
metin2client.bin+BED21 - 8B EC                 - mov ebp,esp
metin2client.bin+BED23 - 6A FF                 - push -01 { 255 }
metin2client.bin+BED25 - 68 A6857B00           - push metin2client.bin+3585A6 { (144) }
metin2client.bin+BED2A - 64 A1 00000000        - mov eax,fs:[00000000] { 0 }
metin2client.bin+BED30 - 50                    - push eax
metin2client.bin+BED31 - 81 EC A8020000        - sub esp,000002A8 { 680 }
metin2client.bin+BED37 - A1 94D28900           - mov eax,[metin2client.bin+43D294] { (598628477) }
metin2client.bin+BED3C - 33 C5                 - xor eax,ebp
metin2client.bin+BED3E - 89 45 F0              - mov [ebp-10],eax
metin2client.bin+BED41 - 53                    - push ebx
metin2client.bin+BED42 - 56                    - push esi
metin2client.bin+BED43 - 57                    - push edi
metin2client.bin+BED44 - 50                    - push eax
metin2client.bin+BED45 - 8D 45 F4              - lea eax,[ebp-0C]
metin2client.bin+BED48 - 64 A3 00000000        - mov fs:[00000000],eax { 0 }
metin2client.bin+BED4E - 89 8D 9CFDFFFF        - mov [ebp-00000264],ecx
metin2client.bin+BED54 - 8B 75 08              - mov esi,[ebp+08]
metin2client.bin+BED57 - 8D 8D ACFEFFFF        - lea ecx,[ebp-00000154]
metin2client.bin+BED5D - E8 3E2E0800           - call metin2client.bin+MappedFileLoad_RVA
metin2client.bin+BED62 - 68 FF000000           - push 000000FF { 255 }
metin2client.bin+BED67 - 56                    - push esi
metin2client.bin+BED68 - 68 80A87E00           - push metin2client.bin+38A880 { ("CPythonNonPlayer::LoadNonPlayerData: %s, sizeof(TMobTable)=%u") }
metin2client.bin+BED6D - C7 45 FC 00000000     - mov [ebp-04],00000000 { 0 }
metin2client.bin+BED74 - E8 D7020800           - call metin2client.bin+13F050
metin2client.bin+BED79 - 8B 0D 6C868B00        - mov ecx,[metin2client.bin+pCEterPackManager_RVA] { (008BAD00) }
metin2client.bin+BED7F - 8D 85 64FDFFFF        - lea eax,[ebp-0000029C]
metin2client.bin+BED85 - 83 C4 0C              - add esp,0C { 12 }
metin2client.bin+BED88 - 50                    - push eax
metin2client.bin+BED89 - 56                    - push esi
metin2client.bin+BED8A - 8D 85 ACFEFFFF        - lea eax,[ebp-00000154]
metin2client.bin+BED90 - 50                    - push eax
metin2client.bin+BED91 - E8 BA6D0C00           - call metin2client.bin+CEterPackManagerGet_RVA
metin2client.bin+BED96 - 84 C0                 - test al,al
metin2client.bin+BED98 - 74 2E                 - je metin2client.bin+BEDC8
metin2client.bin+BED9A - 6A 04                 - push 04 { 4 }
metin2client.bin+BED9C - 8D 85 A0FDFFFF        - lea eax,[ebp-00000260]
metin2client.bin+BEDA2 - 50                    - push eax
metin2client.bin+BEDA3 - 8D 8D ACFEFFFF        - lea ecx,[ebp-00000154]
metin2client.bin+BEDA9 - E8 82320800           - call metin2client.bin+142030
metin2client.bin+BEDAE - 81 BD A0FDFFFF 4D4D5054 - cmp [ebp-00000260],54504D4D { "MMPT" }
metin2client.bin+BEDB8 - 74 3B                 - je metin2client.bin+BEDF5
metin2client.bin+BEDBA - 56                    - push esi
metin2client.bin+BEDBB - 68 C0A87E00           - push metin2client.bin+38A8C0 { ("CPythonNonPlayer::LoadNonPlayerData: invalid Mob proto type %s") }
metin2client.bin+BEDC0 - E8 0B000800           - call metin2client.bin+13EDD0
metin2client.bin+BEDC5 - 83 C4 08              - add esp,08 { 8 }
metin2client.bin+BEDC8 - 32 DB                 - xor bl,bl
metin2client.bin+BEDCA - 8D 8D ACFEFFFF        - lea ecx,[ebp-00000154]
metin2client.bin+BEDD0 - E8 4B2E0800           - call metin2client.bin+141C20
metin2client.bin+BEDD5 - 8A C3                 - mov al,bl
metin2client.bin+BEDD7 - 8B 4D F4              - mov ecx,[ebp-0C]
metin2client.bin+BEDDA - 64 89 0D 00000000     - mov fs:[00000000],ecx { 0 }
metin2client.bin+BEDE1 - 59                    - pop ecx
metin2client.bin+BEDE2 - 5F                    - pop edi
metin2client.bin+BEDE3 - 5E                    - pop esi
metin2client.bin+BEDE4 - 5B                    - pop ebx
metin2client.bin+BEDE5 - 8B 4D F0              - mov ecx,[ebp-10]
metin2client.bin+BEDE8 - 33 CD                 - xor ecx,ebp
metin2client.bin+BEDEA - E8 3B9C1700           - call metin2client.bin+238A2A
metin2client.bin+BEDEF - 8B E5                 - mov esp,ebp
metin2client.bin+BEDF1 - 5D                    - pop ebp
metin2client.bin+BEDF2 - C2 0400               - ret 0004 { 4 }
```

</details>

<details>
  <summary>Region with references to pCEterPackManager, CEterPackManagerGet, MappedFileLoad & CMappedFileSize</summary>

```assembly
metin2client.bin+16EA40 - 55                    - push ebp
metin2client.bin+16EA41 - 8B EC                 - mov ebp,esp
metin2client.bin+16EA43 - 6A FF                 - push -01 { 255 }
metin2client.bin+16EA45 - 68 40FBF700           - push metin2client.bin+35FB40 { (1418432656) }
metin2client.bin+16EA4A - 64 A1 00000000        - mov eax,fs:[00000000] { 0 }
metin2client.bin+16EA50 - 50                    - push eax
metin2client.bin+16EA51 - 81 EC 4C010000        - sub esp,0000014C { 332 }
metin2client.bin+16EA57 - A1 94D20501           - mov eax,[metin2client.bin+43D294] { (472644414) }
metin2client.bin+16EA5C - 33 C5                 - xor eax,ebp
metin2client.bin+16EA5E - 89 45 F0              - mov [ebp-10],eax
metin2client.bin+16EA61 - 53                    - push ebx
metin2client.bin+16EA62 - 56                    - push esi
metin2client.bin+16EA63 - 57                    - push edi
metin2client.bin+16EA64 - 50                    - push eax
metin2client.bin+16EA65 - 8D 45 F4              - lea eax,[ebp-0C]
metin2client.bin+16EA68 - 64 A3 00000000        - mov fs:[00000000],eax { 0 }
metin2client.bin+16EA6E - 8B F9                 - mov edi,ecx
metin2client.bin+16EA70 - E8 9BFDFFFF           - call metin2client.bin+16E810
metin2client.bin+16EA75 - 83 7F 20 10           - cmp dword ptr [edi+20],10 { 16 }
metin2client.bin+16EA79 - 8D 77 0C              - lea esi,[edi+0C]
metin2client.bin+16EA7C - 8B C6                 - mov eax,esi
metin2client.bin+16EA7E - 72 02                 - jb metin2client.bin+16EA82
metin2client.bin+16EA80 - 8B 06                 - mov eax,[esi]
metin2client.bin+16EA82 - 50                    - push eax
metin2client.bin+16EA83 - 68 68D7FB00           - push metin2client.bin+39D768 { ("CResource::Reload %s") }
metin2client.bin+16EA88 - E8 C305FDFF           - call metin2client.bin+13F050
metin2client.bin+16EA8D - 83 C4 08              - add esp,08 { 8 }
metin2client.bin+16EA90 - 8D 8D ACFEFFFF        - lea ecx,[ebp-00000154]
metin2client.bin+16EA96 - E8 0531FDFF           - call metin2client.bin+MappedFileLoad_RVA
metin2client.bin+16EA9B - 83 7E 14 10           - cmp dword ptr [esi+14],10 { 16 }
metin2client.bin+16EA9F - C7 45 FC 00000000     - mov [ebp-04],00000000 { 0 }
metin2client.bin+16EAA6 - 72 02                 - jb metin2client.bin+16EAAA
metin2client.bin+16EAA8 - 8B 36                 - mov esi,[esi]
metin2client.bin+16EAAA - 8B 0D 6C860701        - mov ecx,[metin2client.bin+pCEterPackManager_RVA] { (0107AD00) }
metin2client.bin+16EAB0 - 8D 85 A8FEFFFF        - lea eax,[ebp-00000158]
metin2client.bin+16EAB6 - 50                    - push eax
metin2client.bin+16EAB7 - 56                    - push esi
metin2client.bin+16EAB8 - 8D 85 ACFEFFFF        - lea eax,[ebp-00000154]
metin2client.bin+16EABE - 50                    - push eax
metin2client.bin+16EABF - E8 8C700100           - call metin2client.bin+CEterPackManagerGet_RVA
metin2client.bin+16EAC4 - 8B 1F                 - mov ebx,[edi]
metin2client.bin+16EAC6 - 84 C0                 - test al,al
metin2client.bin+16EAC8 - 74 14                 - je metin2client.bin+16EADE
metin2client.bin+16EACA - FF B5 A8FEFFFF        - push [ebp-00000158]
metin2client.bin+16EAD0 - 8D 8D ACFEFFFF        - lea ecx,[ebp-00000154]
metin2client.bin+16EAD6 - E8 2536FDFF           - call metin2client.bin+CMappedFileSize_RVA
metin2client.bin+16EADB - 50                    - push eax
metin2client.bin+16EADC - EB 04                 - jmp metin2client.bin+16EAE2
metin2client.bin+16EADE - 6A 00                 - push 00 { 0 }
metin2client.bin+16EAE0 - 6A 00                 - push 00 { 0 }
metin2client.bin+16EAE2 - 8B 43 14              - mov eax,[ebx+14]
metin2client.bin+16EAE5 - 8B CF                 - mov ecx,edi
metin2client.bin+16EAE7 - FF D0                 - call eax
metin2client.bin+16EAE9 - 84 C0                 - test al,al
metin2client.bin+16EAEB - B8 02000000           - mov eax,00000002 { 2 }
metin2client.bin+16EAF0 - 75 05                 - jne metin2client.bin+16EAF7
metin2client.bin+16EAF2 - B8 01000000           - mov eax,00000001 { 1 }
metin2client.bin+16EAF7 - 8D 8D ACFEFFFF        - lea ecx,[ebp-00000154]
metin2client.bin+16EAFD - 89 47 28              - mov [edi+28],eax
metin2client.bin+16EB00 - E8 1B31FDFF           - call metin2client.bin+141C20
metin2client.bin+16EB05 - 8B 4D F4              - mov ecx,[ebp-0C]
metin2client.bin+16EB08 - 64 89 0D 00000000     - mov fs:[00000000],ecx { 0 }
metin2client.bin+16EB0F - 59                    - pop ecx
metin2client.bin+16EB10 - 5F                    - pop edi
metin2client.bin+16EB11 - 5E                    - pop esi
metin2client.bin+16EB12 - 5B                    - pop ebx
metin2client.bin+16EB13 - 8B 4D F0              - mov ecx,[ebp-10]
metin2client.bin+16EB16 - 33 CD                 - xor ecx,ebp
metin2client.bin+16EB18 - E8 0D9F0C00           - call metin2client.bin+238A2A
metin2client.bin+16EB1D - 8B E5                 - mov esp,ebp
metin2client.bin+16EB1F - 5D                    - pop ebp
metin2client.bin+16EB20 - C3                    - ret 
```

</details>

<details>
  <summary>CEterPackManagerGet Function</summary>

```assembly
metin2client.bin+CEterPackManagerGet_RVA - 55                    - push ebp
metin2client.bin+185B51 - 8B EC                 - mov ebp,esp
metin2client.bin+185B53 - 53                    - push ebx
metin2client.bin+185B54 - 8B 5D 0C              - mov ebx,[ebp+0C]
metin2client.bin+185B57 - 56                    - push esi
metin2client.bin+185B58 - 57                    - push edi
metin2client.bin+185B59 - 8B 7D 10              - mov edi,[ebp+10]
metin2client.bin+185B5C - 8B F1                 - mov esi,ecx
metin2client.bin+185B5E - 57                    - push edi
metin2client.bin+185B5F - 53                    - push ebx
metin2client.bin+185B60 - FF 75 08              - push [ebp+08]
metin2client.bin+185B63 - 83 7E 08 00           - cmp dword ptr [esi+08],00 { 0 }
metin2client.bin+185B67 - 75 1C                 - jne metin2client.bin+185B85
metin2client.bin+185B69 - E8 42000000           - call metin2client.bin+185BB0
metin2client.bin+185B6E - 84 C0                 - test al,al
metin2client.bin+185B70 - 75 1C                 - jne metin2client.bin+185B8E
metin2client.bin+185B72 - 57                    - push edi
metin2client.bin+185B73 - 53                    - push ebx
metin2client.bin+185B74 - FF 75 08              - push [ebp+08]
metin2client.bin+185B77 - 8B CE                 - mov ecx,esi
metin2client.bin+185B79 - E8 52000000           - call metin2client.bin+185BD0
metin2client.bin+185B7E - 5F                    - pop edi
metin2client.bin+185B7F - 5E                    - pop esi
metin2client.bin+185B80 - 5B                    - pop ebx
metin2client.bin+185B81 - 5D                    - pop ebp
metin2client.bin+185B82 - C2 0C00               - ret 000C { 12 }
metin2client.bin+185B85 - E8 46000000           - call metin2client.bin+185BD0
metin2client.bin+185B8A - 84 C0                 - test al,al
metin2client.bin+185B8C - 74 09                 - je metin2client.bin+185B97
metin2client.bin+185B8E - 5F                    - pop edi
metin2client.bin+185B8F - 5E                    - pop esi
metin2client.bin+185B90 - B0 01                 - mov al,01 { 1 }
metin2client.bin+185B92 - 5B                    - pop ebx
metin2client.bin+185B93 - 5D                    - pop ebp
metin2client.bin+185B94 - C2 0C00               - ret 000C { 12 }
metin2client.bin+185B97 - 57                    - push edi
metin2client.bin+185B98 - 53                    - push ebx
metin2client.bin+185B99 - FF 75 08              - push [ebp+08]
metin2client.bin+185B9C - 8B CE                 - mov ecx,esi
metin2client.bin+185B9E - E8 0D000000           - call metin2client.bin+185BB0
metin2client.bin+185BA3 - 5F                    - pop edi
metin2client.bin+185BA4 - 5E                    - pop esi
metin2client.bin+185BA5 - 5B                    - pop ebx
metin2client.bin+185BA6 - 5D                    - pop ebp
metin2client.bin+185BA7 - C2 0C00               - ret 000C { 12 }
```

</details>

<details>
  <summary>MappedFileLoad Function</summary>

```assembly
metin2client.bin+MappedFileLoad_RVA - 55                    - push ebp
metin2client.bin+141BA1 - 8B EC                 - mov ebp,esp
metin2client.bin+141BA3 - 51                    - push ecx
metin2client.bin+141BA4 - 56                    - push esi
metin2client.bin+141BA5 - 8B F1                 - mov esi,ecx
metin2client.bin+141BA7 - 89 75 FC              - mov [ebp-04],esi
metin2client.bin+141BAA - E8 918B0000           - call metin2client.bin+14A740
metin2client.bin+141BAF - C7 06 28C27F00        - mov [esi],metin2client.bin+39C228 { (005A1C70) }
metin2client.bin+141BB5 - 8B C6                 - mov eax,esi
metin2client.bin+141BB7 - C7 86 18010000 00000000 - mov [esi+00000118],00000000 { 0 }
metin2client.bin+141BC1 - C7 86 1C010000 00000000 - mov [esi+0000011C],00000000 { 0 }
metin2client.bin+141BCB - C7 86 20010000 00000000 - mov [esi+00000120],00000000 { 0 }
metin2client.bin+141BD5 - C7 86 24010000 00000000 - mov [esi+00000124],00000000 { 0 }
metin2client.bin+141BDF - C7 86 28010000 00000000 - mov [esi+00000128],00000000 { 0 }
metin2client.bin+141BE9 - C7 86 2C010000 00000000 - mov [esi+0000012C],00000000 { 0 }
metin2client.bin+141BF3 - C7 86 30010000 00000000 - mov [esi+00000130],00000000 { 0 }
metin2client.bin+141BFD - C7 86 34010000 00000000 - mov [esi+00000134],00000000 { 0 }
metin2client.bin+141C07 - C7 86 38010000 00000000 - mov [esi+00000138],00000000 { 0 }
metin2client.bin+141C11 - C7 86 40010000 00000000 - mov [esi+00000140],00000000 { 0 }
metin2client.bin+141C1B - 5E                    - pop esi
metin2client.bin+141C1C - 8B E5                 - mov esp,ebp
metin2client.bin+141C1E - 5D                    - pop ebp
metin2client.bin+141C1F - C3                    - ret 
```

</details>

<details>
  <summary>CMappedFileSize Function</summary>

```assembly
metin2client.bin+CMappedFileSize_RVA - 8B 81 1C010000        - mov eax,[ecx+0000011C]
```

</details>

# Special Thanks
CORKY - Helped me with lots of ideas, tests and fix some bugs

# Credits
FyreMage32 ❤️
