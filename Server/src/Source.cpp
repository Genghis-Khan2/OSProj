#include "Registry.h"

int main()
{

	AddPathToRegistryAutoboot(R"(Software\Microsoft\Windows\CurrentVersion\Run)",
		"TechnicianServer",
		R"(D:\Course Programming\OS\Server\target\Debug\windows\x86_64\Server\Server.exe)");


	return 0;
}