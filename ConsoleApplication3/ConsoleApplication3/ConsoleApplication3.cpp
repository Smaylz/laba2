// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h> 
#include <iostream>   
using namespace std;

int main() {
	cout << "\n1\n" << endl;
	STARTUPINFO StartupInfo;// структура для оконного режима терминала
	/*
	так как процесс с атрибутами по умолчанию, то в поле cb(устанавливает размер 
	структуры в байтах)должен быть занесен размер структуры
	*/
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);

	PROCESS_INFORMATION ProcInfo; //структура в которую помещаются возвращаемые фуункцией значения декскрипторов
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));

	if (!CreateProcess(L"..\\..\\ConsoleApplication2\\Debug\\ConsoleApplication2.exe", 
						NULL,				//параметры
						NULL,				//защита
						NULL,				//защита
						FALSE,				// дескриптор
						0,					//флаги управляющие классом приоритета
						NULL,				//указывает на блок конфигураций
						NULL,				//указатель на строку с каталогом для нового процесса
						&StartupInfo,		//указатель на структуру, которая создает оконный режим
						&ProcInfo))			//указатель на структуру, в которой помещаются возвращаемые функциией значения дескрипторов   
		return 0;

	WaitForSingleObject(ProcInfo.hProcess, INFINITE);//ожидание завершения процесса
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);
}