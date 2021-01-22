#pragma once

#include <Windows.h>

constexpr const char* REGISTRY_START_PATH = R"(Software\Microsoft\Windows\CurrentVersion\Run)";

// Returns a handle to the mutex if it is created. If the mutex exists, returns NULL
HANDLE IsProgramRunning(LPCSTR mutexName)
{
	HANDLE hMutex = CreateMutexA(NULL,
		FALSE,
		mutexName);

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		hMutex = NULL; // Program is already running, since the mutex already exists
	}

	return hMutex;
}

void AddPathToRegistryAutoboot(LPCSTR registryKeyPath, LPCSTR valueName, LPCSTR binPath)
{
	HKEY hKey;
	DWORD dwDisposition;
	LSTATUS lStat = RegOpenKeyExA(
		HKEY_CURRENT_USER,
		registryKeyPath,
		0,
		KEY_WRITE,
		&hKey
	);

	RegSetKeyValueA(
		hKey,
		NULL,
		valueName,
		REG_SZ,
		binPath,
		strlen(binPath) + 1
	);

	RegCloseKey(hKey);
}