#include "pch.h"
#include <windows.h> 
#include <iostream>   
#include <string>

using namespace std;
wchar_t setX();
int main() {
	cout << "\n2\n"<<endl;
	wchar_t x = setX();
	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);
	
	PROCESS_INFORMATION ProcInfo; ZeroMemory(&ProcInfo, sizeof(ProcInfo));
	wchar_t appname[100] = L"ConsoleApplication1.exe";
	wcscat_s(appname, L" ");
	wcscat_s(appname, &x);
	cout << "\nflag\n";
	if (!CreateProcess( L"..\\..\\ConsoleApplication1\\Debug\\ConsoleApplication1.exe",
		appname, 
		NULL, 
		NULL, 
		FALSE, 
		0, 
		NULL, 
		NULL, 
		&StartupInfo, 
		&ProcInfo))   return 0;

	WaitForSingleObject(ProcInfo.hProcess, INFINITE);
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);
}
wchar_t setX() {
	wchar_t x;
	cout << "\n\n";
	cout << "\n 1-write\n 2-read\n 3-resScreen\n 4-resFile\n 5-Update\n";
	wcin >> x;
	return x;
}