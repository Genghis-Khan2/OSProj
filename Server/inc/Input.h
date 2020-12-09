#pragma once
#include <cstdio>
#include <cstring>

void parse(const char* recvBuf, int recvBufLen, char* sendBuf, int sendBufLen)
{
	if (strncmp(recvBuf, "PING", 4) == 0)
	{
		strcpy_s(sendBuf, sendBufLen, "PONG");
		return;
	}

	strcpy_s(sendBuf, sendBufLen, "\0");
}