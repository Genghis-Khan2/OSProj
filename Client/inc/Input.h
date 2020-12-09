#pragma once
#include <cstdio>
#include <cstring>

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