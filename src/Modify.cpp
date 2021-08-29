
#include "Modify.h"
#include "Logger.h"

//#include <include/capi/cef_urlrequest_capi.h>



/*
* 
* Black banner still show even libcef hooked.
* 
*/

/*
using _cef_urlrequest_create = cef_urlrequest_t * (*)(struct _cef_request_t* request,
													  struct _cef_urlrequest_client_t* client,
													  struct _cef_request_context_t* request_context);

static _cef_urlrequest_create cef_urlrequest_create_orig;

static constexpr std::array<std::string_view, 3> block_list = { "/ads/", "/ad-logic/", "/gabo-receiver-service/" };

cef_urlrequest_t* cef_urlrequest_create_hook (struct _cef_request_t* request,
											  struct _cef_urlrequest_client_t* client,
											  struct _cef_request_context_t* request_context)
{

	cef_string_userfree_utf16_t  url_utf16 = request->get_url (request);

	char* c_url = new char[url_utf16->length + 1];
	c_url[url_utf16->length] = '\0';

	for (size_t i = 0; i < url_utf16->length; i++) {
		c_url[i] = *reinterpret_cast<char*>(url_utf16->str + i);
	}

	std::string url (c_url);

	delete[] c_url;
	cef_string_userfree_utf16_free (url_utf16);

	for (const auto& blockurl : block_list) {
		if (std::string::npos != url.find (blockurl)) {
			g_Logger.Log ("blocked - " + url);
			return nullptr;
		}
	}
	g_Logger.Log ("allow - " + url);
	return cef_urlrequest_create_orig (request, client, request_context);
}
*/

// https://www.unknowncheats.me/forum/1064672-post23.html
bool DataCompare (BYTE* pData, BYTE* bSig, char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bSig)
	{
		if (*szMask == 'x' && *pData != *bSig)
			return false;
	}
	return (*szMask) == NULL;
}

BYTE* FindPattern (BYTE* dwAddress, const DWORD dwSize, BYTE* pbSig, char* szMask)
{
	DWORD length = strlen (szMask);
	for (DWORD i = NULL; i < dwSize - length; i++)
	{
		__try
		{
			if (DataCompare (dwAddress + i, pbSig, szMask))
				return dwAddress + i;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return nullptr;
		}
	}
	return 0;
}


DWORD WINAPI KillBanner (LPVOID)
{
	Logger g_Logger;
	HMODULE hModule = GetModuleHandle (NULL);
	MODULEINFO mInfo = { 0 };
	if (GetModuleInformation (GetCurrentProcess (), hModule, &mInfo, sizeof (MODULEINFO))) {
		g_Logger.Log ("GetModuleInformation OK!");
		auto skipPod = FindPattern ((uint8_t*)hModule, mInfo.SizeOfImage, (BYTE*)"\x83\xC4\x08\x84\xC0\x0F\x84\xE5\x03\x00\x00", "xxxxxxxxxxx");

		if (skipPod)
		{
			DWORD oldProtect;
			VirtualProtect ((char*)skipPod + 5, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
			memset ((char*)skipPod + 5, 0x90, 1);
			VirtualProtect ((char*)skipPod + 5, 1, oldProtect, &oldProtect);

			VirtualProtect ((char*)skipPod + 6, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
			memset ((char*)skipPod + 6, 0xE9, 1);
			VirtualProtect ((char*)skipPod + 6, 1, oldProtect, &oldProtect);
			g_Logger.Log ("main process - patch success!");
		}
		else {
			g_Logger.Log ("main process - patch failed!");

			skipPod = FindPattern ((uint8_t*)hModule, mInfo.SizeOfImage, (BYTE*)"\x83\xC4\x08\x84\xC0\x0F\x84\xED\x03\x00\x00", "xxxxxxxxxxx");
			if (skipPod)
			{
				DWORD oldProtect;
				VirtualProtect ((char*)skipPod + 5, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
				memset ((char*)skipPod + 5, 0x90, 1);
				VirtualProtect ((char*)skipPod + 5, 1, oldProtect, &oldProtect);

				VirtualProtect ((char*)skipPod + 6, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
				memset ((char*)skipPod + 6, 0xE9, 1);
				VirtualProtect ((char*)skipPod + 6, 1, oldProtect, &oldProtect);
				g_Logger.Log ("main process 1.1.66.578.gc54d0f69-a - patch success!");
			}
			else {
				g_Logger.Log ("main process 1.1.66.578.gc54d0f69-a - patch failed!");
			}
		}

	}
	else {
		g_Logger.Log ("GetModuleInformation failed!");
	}

	/*
	hModule = GetModuleHandle ("libcef.dll");
	if (!hModule)
		hModule = LoadLibrary ("libcef.dll");

	if (hModule)
	{
		cef_urlrequest_create_orig = cef_urlrequest_create;//(_cef_urlrequest_create)GetProcAddress (hModule, "cef_urlrequest_create");

		if (cef_urlrequest_create_orig) {
			Mhook_SetHook ((PVOID*)&cef_urlrequest_create_orig, cef_urlrequest_create_hook);
		}
	}
	*/


	return 0;
}
