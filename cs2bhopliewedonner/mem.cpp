#include "mem.h"
#include <tlhelp32.h>

mem::mem(const char* procName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (Process32Next(snapshot, &entry))
	{
		if (!strcmp(procName, entry.szExeFile))
		{
			this->ID = entry.th32ProcessID;
			this->process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->ID);
			break;
		}
	}

	if (snapshot)
		CloseHandle(snapshot);
}

mem::~mem()
{
	if (this->process)
		CloseHandle(this->process);
}

DWORD mem::getProcId()
{
	return this->ID;
	CloseHandle(this->process);
}

HANDLE mem::getProcHandle()
{
	return this->process;
}

uintptr_t mem::GetModuleBaseAddress(const char* moduleName)
{
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);

	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->ID);

	uintptr_t result = 0;

	while (Module32Next(snapshot, &entry))
	{
		if (!strcmp(moduleName, entry.szModule))
		{
			result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			break;
		}
	}

	if (snapshot)
		CloseHandle(snapshot);

	return result;
}