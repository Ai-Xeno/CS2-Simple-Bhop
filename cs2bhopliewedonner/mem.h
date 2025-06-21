#pragma once

#include <Windows.h>
#include <iostream>

class mem
{
private:
	DWORD ID = 0;
	HANDLE process = NULL;

public:
	mem(const char* procName);
	~mem();

	DWORD getProcId();
	HANDLE getProcHandle();

	uintptr_t GetModuleBaseAddress(const char* moduleName);

	template <typename T>
	T Read(uintptr_t address)
	{
		T value;
		ReadProcessMemory(this->process, (LPCVOID)address, &value, sizeof(T), NULL);
		return value;
	}

	template <typename T>
	T Write(uintptr_t address, T value)
	{
		return WriteProcessMemory(this->process, (LPVOID)address, &value, sizeof(T), NULL);
	}
};
