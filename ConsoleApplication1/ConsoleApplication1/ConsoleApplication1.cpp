

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

struct Taska1 {
	int num;
	char seat[30];
	int houro;
	int houri;
	int minuteo;
	int minutei;
};

int setX();
int menu(int);
HANDLE createOrOpen();
void read(HANDLE);
void write(HANDLE);
void resScreen(HANDLE);
void resFile(HANDLE);
void update(HANDLE);

int main(int n,char** s)
{
	int z = atoi(s[1]);
	menu(z);
	return 0;
}

int setX() {
	int x;
	cout << "\n 1-write\n 2-read\n 3-resScreen\n 4-resFile\n 5-Update\n 6 - Exit\n";
	cin >> x;
	return x;
}

HANDLE createOrOpen() {
	LPCTSTR fn = L"File_New.dat";
	HANDLE myFile = CreateFile(fn,			// Указатель на имя файла (устройства) 
		GENERIC_READ | GENERIC_WRITE,		// Параметры доступа 
		FILE_SHARE_READ | FILE_SHARE_WRITE,	// Режим совместного доступа 
		NULL,								// указатель на дескриптор защиты 
		OPEN_ALWAYS,						// Режим открытия 
		FILE_ATTRIBUTE_NORMAL,				// Атрибуты файла 
		NULL);								// Файл шаблона 
	if (myFile == INVALID_HANDLE_VALUE)
		cout << "Error";
	else  cout << "\n File is created";
	return myFile;
}

void read(HANDLE mf) {
	Taska1 k;
	DWORD n;
	SetFilePointer(mf, 0, 0, FILE_BEGIN);
	while (ReadFile(mf,						 // Идентификатор файла 
		&k,									 // Адрес буфера данных 
		sizeof(k),							 // Количество байт 
		&n,									 // Адрес слова, в котором  хранится количество байт
		NULL)								 // Адрес структуры OVERLAPPED 
		&& n != 0)
		cout << k.num << k.seat << k.houri << k.minutei << k.houro << k.minuteo << endl;
}

void write(HANDLE mf) {
	DWORD n;
	Taska1 p;
	cout << "\nEnter num=";
	cin >> p.num;
	cout << "Enter seat=";
	cin >> p.seat;
	cout << "Enter timeout(hour,minute)=";
	cin >> p.houro >> p.minuteo;
	cout << "Enter timein(hour,minute)=";
	cin >> p.houri >> p.minutei;
	WriteFile(mf,
		&p,
		sizeof(p),
		&n,
		NULL);
	FlushFileBuffers(mf);
}

void resScreen(HANDLE mf) {
	int h, m;
	cout << "Enter time(hour and minute)=";
	cin >> h >> m;
	Taska1 k;
	DWORD n;
	SetFilePointer(mf,			// Идентификатор файла
		0,					//кол-во байт , на которое будет перемещена текущая позиция
		0,					// Адрес старшего слова, содержащего расстояние для перемещения позиции  
		FILE_BEGIN);		// Способ перемещения позиции
	while (ReadFile(mf, &k, sizeof(k), &n, NULL) && n != 0)
		if (k.houri < h || (k.houri == h && k.minutei < m)) {
			cout << k.num << k.seat << k.houri << k.minutei << k.houro << k.minuteo << endl;
		}
}

void resFile(HANDLE mf) {
	//cпросить как приводить String name = "sts.txt" к LPCTSTR 
	LPCTSTR fn = L"Result.txt";
	HANDLE myFile = CreateFile(fn,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (myFile == INVALID_HANDLE_VALUE)
		cout << "Error";
	else  cout << " \nFile is created\n";
	int h, m;
	cout << "\nEnter time(hour and minute)=";
	cin >> h >> m;
	Taska1 k;
	DWORD n;
	SetFilePointer(mf, 0, 0, FILE_BEGIN);
	while (ReadFile(mf, &k, sizeof(k), &n, NULL) && n != 0)
		if (k.houri < h || (k.houri == h && k.minutei < m)) {
			WriteFile(myFile, &k, sizeof(k), &n, NULL);
			FlushFileBuffers(myFile);
		}
}

int menu(int x) {
	HANDLE myFile = createOrOpen();
	while (true) {
		if (x == NULL)
			x = setX();

		switch (x)
		{
		case 1:
			write(myFile);
			x = NULL;
			break;
		case 2:
			read(myFile);
			x = NULL;
			break;
		case 3:
			resScreen(myFile);
			x = NULL;
			break;
		case 4:
			resFile(myFile);
			x = NULL;
			break;
		case 5:
			update(myFile);
			x = NULL;
			break;
		case 6:
			CloseHandle(myFile);
			x = NULL;
			exit(0);
			break;
		default:
			break;
		}
	}
}

void update(HANDLE mf) {
	cout << "How to change the entry?" << endl;
	int l;
	cin >> l;
	if(l!=0)
	SetFilePointer(mf,			// Идентификатор файла
		sizeof(Taska1),					//кол-во байт , на которое будет перемещена текущая позиция
		0,					// Адрес старшего слова, содержащего расстояние для перемещения позиции  
		FILE_BEGIN);
	SetFilePointer(mf,			// Идентификатор файла
		0,					//кол-во байт , на которое будет перемещена текущая позиция
		0,					// Адрес старшего слова, содержащего расстояние для перемещения позиции  
		FILE_BEGIN);
	DWORD n;
	Taska1 p;
	cout << "\nEnter num=";
	cin >> p.num;
	cout << "Enter seat=";
	cin >> p.seat;
	cout << "Enter timeout(hour,minute)=";
	cin >> p.houro >> p.minuteo;
	cout << "Enter timein(hour,minute)=";
	cin >> p.houri >> p.minutei;
	WriteFile(mf,
		&p,
		sizeof(p)*l,
		&n,
		NULL);
	FlushFileBuffers(mf);

}