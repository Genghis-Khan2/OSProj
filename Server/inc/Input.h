#pragma once
#include <cstdio>
#include <cstring>
#include <Windows.h>

constexpr const char* VERSION = "1.0.0"; // Longest version length is 8 (9 including null) since it can be 99.99.99
constexpr const char* PROGRAM_PATH = R"(D:\Course Programming\OS\Server\target\Debug\windows\x86_64\Server\Server.exe)";
constexpr const char* OLD_PROGRAM_PATH = R"(D:\Course Programming\OS\Server\target\Debug\windows\x86_64\Server\OldServer.exe)";
constexpr const char* FICTITIOUS = R"(D:\Course Programming\OS\Server\target\Debug\windows\x86_64\Server\Update.exe)";

bool parse(char* recvBuf, int recvBufLen, char* sendBuf, int sendBufLen, SOCKET ClientSocket)
{
	if (_strnicmp(recvBuf, "PING", 4) == 0)
	{
		strcpy_s(sendBuf, sendBufLen, "PONG");
		return false;
	}

	if (_strnicmp(recvBuf, "UPDATE", 6) == 0)
	{
		// Open the file
		// In a loop, receive chunk, and write chunk
		HANDLE hFile = CreateFileA(
			FICTITIOUS,
			GENERIC_WRITE,
			FILE_SHARE_DELETE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		int iResult;
		DWORD bytesWritten;

		do
		{
			iResult = recv(ClientSocket, recvBuf, recvBufLen, 0);

			if (iResult == BUFSIZ)
			{
				bool end_buf = true;
				for (int i = 0; i < BUFSIZ; ++i)
				{
					if (recvBuf[i] != EOF)
					{
						end_buf = false;
						break;
					}
				}

				if (end_buf)
				{
					break;
				}
			}

			if (!WriteFile(
				hFile,
				recvBuf,
				iResult,
				&bytesWritten,
				NULL
			))
			{
				printf("Problem writing to update file\n");
			}

		} while (iResult > 0);

		MoveFileA(
			PROGRAM_PATH,
			OLD_PROGRAM_PATH
		);

		MoveFileA(
			FICTITIOUS,
			PROGRAM_PATH
		);

		CloseHandle(hFile);

		strcpy_s(sendBuf, sendBufLen, "File read");
		return false;
	}

	if (_strnicmp(recvBuf, "EXIT", 4) == 0)
	{
		return true;
	}

	if (_strnicmp(recvBuf, "VERSION", 7) == 0)
	{
		strcpy_s(sendBuf, sendBufLen, VERSION);
		return false;
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