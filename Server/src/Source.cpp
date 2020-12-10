#include "Socket.h"
#include "Registry.h"

int main()
{

	AddPathToRegistryAutoboot(R"(Software\Microsoft\Windows\CurrentVersion\Run)",
		"TechnicianServer",
		PROGRAM_PATH);

	DeleteFileA(
		OLD_PROGRAM_PATH
	);


	HANDLE hMutex = IsProgramRunning("TechnicianServer");
	if (hMutex == NULL)
	{
		return -1;
	}

	int returnCode = setupServerSocket();

	system("pause");
	return 0;
}