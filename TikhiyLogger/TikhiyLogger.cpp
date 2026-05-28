#include "TikhiyLogger.h"

NTSYSAPI NTSTATUS NtUnmapViewOfSection(IN HANDLE process_handle, IN PVOID base_address);

int 
main(void)
{
	wchar_t executable_path[] = L"C:\\Windows\\System32\\notepad.exe";
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	PROCESS_BASIC_INFORMATION pbi_buffer;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&pbi_buffer, sizeof(pbi_buffer));
	si.cb = sizeof(si);

	if (!CreateProcessW(NULL, executable_path, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
		MessageBoxW(NULL, L"Failed to Create Process", L"ERROR", MB_OK | MB_ICONERROR);
		return -1;
	}

	NtQueryInformationProcess(pi.hProcess, ProcessBasicInformation, &pbi_buffer, sizeof(pbi_buffer), NULL);
	PEB local_peb;
	SIZE_T bytes_read;

	if (!ReadProcessMemory(pi.hProcess, pbi_buffer.PebBaseAddress, &local_peb, sizeof(local_peb), NULL)) {
		MessageBoxW(NULL, L"Failed to Read Remote address", L"ERROR", MB_OK | MB_ICONERROR);
		return -1;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
