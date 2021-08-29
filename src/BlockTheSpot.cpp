// BlockTheSpot.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

bool AddDllToBlacklist (const wchar_t* dll_name) { return true; }
void ClearReportsBetween_ExportThunk (time_t begin, time_t end) {}

int CrashForException_ExportThunk (EXCEPTION_POINTERS* info) {
	return EXCEPTION_CONTINUE_SEARCH;
}
void DisableHook () {}

UINT32 DrainLog (UINT8* buffer,
				 UINT32 buffer_size,
				 UINT32* log_remaining) {

	return 0;
}

bool DumpHungProcessWithPtype_ExportThunk (HANDLE process_handle,
										   const char* ptype) {
	return false;
}

void DumpProcessWithoutCrash (void* task_port) {}

INT32 GetApplyHookResult () { return 0; }
UINT32 GetBlockedModulesCount () { return 0; }

size_t GetCrashReports_ExportThunk (void* reports,
									size_t reports_size) {
	return 0;
}

const wchar_t* GetCrashpadDatabasePath_ExportThunk () {
	return nullptr;
}
void* GetHandleVerifier () {
	return nullptr;
}
UINT32 GetInstallDetailsPayload () { return 0; }
UINT32 GetUniqueBlockedModulesCount () { return 0; }
bool GetUserDataDirectoryThunk (wchar_t* user_data_dir,
								size_t user_data_dir_length,
								wchar_t* invalid_user_data_dir,
								size_t invalid_user_data_dir_length) {
	return true;
}
HANDLE InjectDumpForHungInput_ExportThunk (HANDLE process) {
	return nullptr;
}
bool IsBlacklistInitialized () {
	return false;
}
bool IsCrashReportingEnabledImpl () {
	return false;
}
bool IsThirdPartyInitialized () {
	return false;
}
bool RegisterLogNotification (HANDLE event_handle) {
	return false;
}
void RequestSingleCrashUpload_ExportThunk (const char* local_id) {}
void SetCrashKeyValueImpl () {}
void SetMetricsClientId (const char* client_id) {}
void SetUploadConsent_ExportThunk (bool consent) {}
void SignalChromeElf () {}
void SignalInitializeCrashReporting () {}
void SuccessfullyBlocked (const wchar_t** blocked_dlls, int* size) {}