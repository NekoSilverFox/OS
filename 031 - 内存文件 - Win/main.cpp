/*
����էԧ���ӧڧ�� �ڧ���էߧ�� ��ѧۧ� �� ���է֧�اڧާ�� (�ߧѧ��ڧާ֧�, abcdefghij��). ������ݧ�٧�� ����ҧ�ѧاѧ֧ާ�� �� ��ѧާ��� ��ѧۧ�,
����ѧҧ��ѧ�� �� �ڧ���էߧ�� ��ѧۧݧ��, ��ڧ�ѧ� �� �٧ѧ�ڧ��ӧѧ� �� ��ѧާ���. ���ҧ֧էڧ��� �� ����, ���� �ڧ���էߧ�� ���է֧�اڧާ�� ��ѧۧݧ� �ڧ٧ާ֧ߧڧݧ���
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
	// ����ṹΪ�ܶຯ����������ʱ�ṩ��ȫ�����á��磺CreateFile��CreatePipe��CreateProcess��RegCreateKeyEx,RegSaveKeyEx
	SECURITY_ATTRIBUTES sa; // �����ѧߧ�ӧڧ�� �ҧ֧٧��ѧ�ߧ���� ��ҧ�֧ܧ��
	sa.bInheritHandle = FALSE;  // ��ȫ�����Ķ����ܷ��´����Ľ��̼̳У��ߧѧ�ݧ֧է�ӧѧ�
	sa.lpSecurityDescriptor = NULL;  // ��ȫ������
	sa.nLength = sizeof(sa); // �ṹ���С

	// ��ҧ�ѧҧ��ѧ�� - ����			...
	HANDLE hFile = CreateFile(L"communication.txt", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);  // ����ܧ�

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("File can't be open! Error: %d\n", GetLastError());
		exit(0);
	}
	else
	{
		printf("File has been opened...\n");
	}

	// �ڴ�ӳ�䣨���������ڴ棩 �����ҧ�ѧا֧ߧڧ� ��ѧۧݧ� �� ��ѧާ���			...
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

	// �ڴ����ļ�ӳ�����󣬿��Ե���MapViewOfFile����ӳ�䵽�����̵ĵ�ַ�ռ��ڣ�����ҧ�ѧ٧ڧ�� - ӳ�䣩
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
	printf("\nContent of the file %s :\n", IN_FILE);  // �ļ����� - ����է֧�اѧߧڧ� �է�ܧ�ާ֧ߧ��
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
	// ����ӧ�ҧ�اէ֧ߧڧ� ��֧������
#endif
	// �ӽ��̵ĵ�ַ�ռ䳷���ļ����ݵ�ӳ��
	// ���ߧڧ���ا֧ߧڧ� ��ѧۧݧ�ӧ�� �էѧߧߧ�� �ڧ� �ѧէ�֧�ߧ�ԧ� �������ѧߧ��ӧ� �����֧���
	if (!UnmapViewOfFile(MapView))
	{
		printf("Error unmapping file! Code: %d\n", GetLastError());
	}

	// �ر�ǰ�洴�����ļ�ӳ�������ļ����󣨧����ҧ�ѧا֧ߧڧ� - ӳ�䣩
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