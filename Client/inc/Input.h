#pragma once
#include <cstdio>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

constexpr const char* BINARY_PATH = R"(D:\Course Programming\OS\Server.exe)";
constexpr int DEFAULT_BUFLEN = 512;

void getInput(char* buf, int bufLength)
{
	printf("Please enter next command: ");
	fgets(buf, bufLength, stdin);
	for (int i = 0; i < bufLength; ++i)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			break;
		}
	}

	buf[bufLength - 1] = '\0';
}

bool isUpdate(const char* sendbuf, int sendBufLen)
{
	return _strnicmp(sendbuf, "UPDATE", 6) == 0;
}

bool SendFile(SOCKET Socket)
{
	HANDLE hFile = CreateFileA(
		BINARY_PATH,
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	DWORD iBytesRead;
	BOOL bResult;

	char sendbuf[DEFAULT_BUFLEN] = { 0 };

	do
	{
		bResult = ReadFile(
			hFile,
			sendbuf,
			DEFAULT_BUFLEN,
			&iBytesRead,
			NULL
		);

		if (iBytesRead == 0 && bResult)
		{
			for (int k = 0; k < DEFAULT_BUFLEN; ++k)
			{
				sendbuf[k] = EOF;
			}
			break;
		}

		int iResult = send(Socket, sendbuf, static_cast<int>(iBytesRead), 0);

		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(Socket);
			WSACleanup();
			return false;
		}

	} while (iBytesRead != 0 || !bResult);

	CloseHandle(hFile);
	return true;
}