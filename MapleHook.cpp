#include "Global.h"
#include <intrin.h>
#include <map>
#include <string>
#include "MapleType.h"

std::map<int, std::string>	g_mStringPool;



typedef ZXString<char>* (__fastcall* StringPool__GetString_t)(void* ecx, void* edx, ZXString<char>* result, unsigned int nIdx, char formal);
auto StringPool__GetString = reinterpret_cast<StringPool__GetString_t>(0x00EC3BF0);  
typedef void(__fastcall* ZXString_char__Assign_t)(void* pThis, void* edx, const char* s, int n);
auto ZXString_char__Assign = reinterpret_cast<ZXString_char__Assign_t>(0x0047EDD0);


ZXString<char>* __fastcall StringPool__GetString_Hook(void* pThis, void* edx, ZXString<char>* result, unsigned int nIdx, char formal)
{
	if (g_mStringPool.count(nIdx) > 0)
	{
		auto szEntry = g_mStringPool[nIdx];

		result->m_pStr = 0;
		ZXString_char__Assign(result, edx, szEntry.c_str(), -1);

		return result;
	}

	return StringPool__GetString(pThis, edx, result, nIdx, formal);
}


void InitStringPool()
{
	g_mStringPool[4479] = std::string("Poki v176"); //Login Version
	g_mStringPool[29] = std::string("Ayame"); // Manager Job to Ayame
	g_mStringPool[1547] = std::string("[Welcome] Welcome to Poki v176 !!"); //Welcome message
	g_mStringPool[2352] = std::string(""); // Video Skipper

}

void FuckMaple()
{
	PatchRetZero(0x01960B00); // NGS Bypass
	PatchJmp(0x019DD7AD, 0x019DD844); // CRC Bypass

	PatchDMGCap(0x000EB8C35); // No Damage Cap
	PatchDMGCap(0x00EB512A); // No Damage Cap
	PatchNop(0x0074CE30, 6); // Drop Cash Items
	PatchNop(0x0074CE3F, 6); // Drop Cash Items
	PatchChat(0x0064E09B, 6); // Bypass Chat Spam
	PatchChat(0x0064DFA1, 1); // Bypass Chat Spam

	

		//PatchNop(0x00B31B3D, 2); // Wizet Logo Skip



	InitStringPool();

	SetHook(TRUE, reinterpret_cast<void**>(&StringPool__GetString), StringPool__GetString_Hook);

}
