#include "Socket.h"
#include "Registry.h"

int main()
{

	AddPathToRegistryAutoboot(R"(Software\Microsoft\Windows\CurrentVersion\Run)",
		"TechnicianServer",
		R"(D:\Course Programming\OS\Server\target\Debug\windows\x86_64\Server\Server.exe)");


	HANDLE hMutex = IsProgramRunning("TechnicianServer");
	if (hMutex == NULL)
	{
		return -1;
	}

	int returnCode = setupServerSocket();
	return 0;
}