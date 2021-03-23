/*
Подготовить исходный файл с содержимом (например, abcdefghijЕ). Используя отображаемый в память файл,
поработать с исходным файлом, читая и записывая в память. Убедится в том, что исходное содержимое файла изменилось
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

#define IN_FILE "communication.txt"

int main()
{
	// 这个结构为很多函数创建对象时提供安全性设置。如：CreateFile，CreatePipe，CreateProcess，RegCreateKeyEx,RegSaveKeyEx
	SECURITY_ATTRIBUTES sa; // Установить безопасность объекта
	sa.bInheritHandle = FALSE;  // 安全描述的对象能否被新创建的进程继承（наследовать）
	sa.lpSecurityDescriptor = NULL;  // 安全描述符
	sa.nLength = sizeof(sa); // 结构体大小

	// обработать - 处理			...
	HANDLE hFile = CreateFile(L"communication.txt", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);  // ручка

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("File can't be open! Error: %d\n", GetLastError());
		exit(0);
	}
	else
	{
		printf("File has been opened...\n");
	}

	// 内存映射（创建共享内存） Отображение файла в память			...
	HANDLE hFileMap = CreateFileMapping(hFile, &sa, PAGE_READWRITE, 0, 0, L"file_mapping");
	if (hFileMap == NULL)
	{
		printf("Error creating file mapping! Code: %d\n", GetLastError());
		exit(1);
	}
	else
	{
		printf("File mapping created successfully!\n");
	}

	// 在创建文件映射对象后，可以调用MapViewOfFile函数映射到本进程的地址空间内（отобразить - 映射）
	PVOID MapView = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (MapView == NULL)
	{
		printf("Error creating map view of file! Code: %d\n", GetLastError());
		exit(1);
	}
	else
	{
		printf("Map view of file created successfully!\n");
	}

	DWORD filesize = GetFileSize(hFile, NULL);
	PSTR pchANSI = (PSTR)MapView;
	printf("\nContent of the file %s :\n", IN_FILE);  // 文件内容 - Содержание документа
	for (int i = 0; i < filesize; i++)
	{
		printf("%c", pchANSI[i]);
	}

	printf("\n\nEnter new string (%d symbols): \n", filesize);
	for (int i = 0; i < filesize; i++)
	{
		scanf("%c", &pchANSI[i]);
	}

	printf("\nNew content of the file %s :\n", IN_FILE);
	for (int i = 0; i < filesize; i++)
	{
		printf("%c", pchANSI[i]);
	}

#if 0
	// Освобождение ресурсов
#endif
	// 从进程的地址空间撤消文件数据的映像
	// Уничтожение файловых данных из адресного пространства процесса
	if (!UnmapViewOfFile(MapView))
	{
		printf("Error unmapping file! Code: %d\n", GetLastError());
	}

	// 关闭前面创建的文件映射对象和文件对象（Отображение - 映射）
	if (!CloseHandle(hFile))
	{
		printf("Error closing file handler! Code: %d\n", GetLastError());
	}

	if (!CloseHandle(hFileMap))
	{
		printf("Error closing file mapping handler! Code: %d\n", GetLastError());
	}

	_getch();
	return 0;
}