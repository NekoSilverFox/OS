#define _CRT_SECURE_NO_WARNINGS
/*
§±§â§à§è§Ö§ã§ã §Õ§à§Ý§Ø§Ö§ß §Ò§í§ä§î §ã §Õ§Ó§å§Þ§ñ §á§à§ä§à§Ü§Ñ§Þ§Ú. §±§Ö§â§Ó§í§Û §á§à§ä§à§Ü §é§Ú§ä§Ñ§Ö§ä §æ§Ñ§Û§Ý §ã§è§Ö§ß§Ñ§â§Ú§Û §Ú §Ó§í§á§à§Ý§ß§ñ§Ö§ä §Ù§Ñ§Õ§Ñ§ß§ß§í§Ö §Ó §ß§Ö§Þ §Õ§Ö§Û§ã§ä§Ó§Ú§ñ
§ã §Ó§Ú§â§ä§å§Ñ§Ý§î§ß§à§Û §á§Ñ§Þ§ñ§ä§î§ð, §Ñ §Ó§ä§à§â§à§Û §à§ä§ã§Ý§Ö§Ø§Ú§Ó§Ñ§Ö§ä §á§à§Ó§Ö§Õ§Ö§ß§Ú§Ö §á§Ö§â§Ó§à§Ô§à.
*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define IN_FILE "C:\\input.txt"
#define OUT_FILE "C:\\output.txt"

#define RESERVE		1
#define COMMIT		2
#define DECOMMIT	3
#define RESET		4
#define RELEASE		5
#define LOCK		6
#define UNLOCK		7

DWORD Time, PrevTime, OpCode, Size, Access;
LPVOID Block;

bool CheckOp(DWORD Op)
{
	if (Op < 1 || Op > 7)
	{
		printf("Error! Wrong opcode!");
		return false;
	}
	return true;
}

bool CheckAccess(DWORD Acc)
{
	if (Acc < 1 || Acc > 5)
	{
		printf("Error! Wrong access!");
		return false;
	}
	return true;
}

bool CheckTime(DWORD& Time, DWORD PrevTime)
{
	if (Time < PrevTime)
	{
		printf("Warning!! Error in time chain! Corrected=)");
		Time = PrevTime + 1;
	}
	return true;
}

int SetAccess(DWORD Acc)
{
	switch (Acc)
	{
	case 1:	Acc = PAGE_READONLY;
		break;
	case 2:	Acc = PAGE_READWRITE;
		break;
	case 3:	Acc = PAGE_EXECUTE;
		break;
	case 4:	Acc = PAGE_EXECUTE_READ;
		break;
	case 5:	Acc = PAGE_EXECUTE_READWRITE;
		break;
	}
	return 0;
}

DWORD WINAPI Monitor(PVOID Param)
{
	bool bExit = false;
	HANDLE hE = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"f_end");
	FILE* output = fopen(OUT_FILE, "wt");
	MEMORYSTATUS ms;
	while (!bExit)
	{
		GlobalMemoryStatus(&ms);
		//printf("%ld\n",ms.dwMemoryLoad);
		DWORD res = WaitForSingleObject(hE, 100);
		bExit = (res == WAIT_OBJECT_0);
		fprintf(output, "Memory load: %ld\n", ms.dwMemoryLoad);
		fprintf(output, "Physical memory available: %ld\n", ms.dwAvailPhys);
		fprintf(output, "Virtual memory available: %ld\n", ms.dwAvailVirtual);
		fprintf(output, "Page File available: %ld\n", ms.dwAvailPageFile);
		fprintf(output, "\n");
	}
	fclose(output);
	return 0;
}

int main2()
{
	FILE* input = fopen(IN_FILE, "r");


	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(sa);

	HANDLE f_end = CreateEvent(&sa, TRUE, FALSE, (LPCWSTR)"f_end");
	HANDLE monitor = CreateThread(&sa, 0, Monitor, NULL, NULL, NULL);

	char str[1024];
	while (!feof(input))
	{
		Time = 0;
		Block = 0;
		OpCode = 0;
		Size = 0;
		Access = 0;
		fgets(str, 1024, input);
		sscanf(str, "%ld%d%ld%ld%ld", &Time, &Block, &OpCode, &Size, &Access);
		if (!(CheckAccess(Access) && CheckOp(OpCode) && CheckTime(Time, PrevTime)))
		{
			printf("Error in read data!");
		}
		else
		{
			SetAccess(Access);
			Sleep(Time - PrevTime);
			PrevTime = Time;
			switch (OpCode)
			{
			case RESERVE:
				VirtualAlloc(Block, Size, MEM_RESERVE, Access);
				break;
			case COMMIT:
				VirtualAlloc(Block, Size, MEM_COMMIT, Access);
				break;
			case DECOMMIT:
				VirtualFree(Block, Size, MEM_DECOMMIT);
				break;
			case RESET:
				VirtualAlloc(Block, Size, MEM_RESET, Access);
				break;
			case RELEASE:
				VirtualFree(Block, 0, MEM_RELEASE);
				break;
			case LOCK:
				VirtualLock(Block, Size);
				break;
			case UNLOCK:
				VirtualUnlock(Block, Size);
				break;
			}
		}
	}
	SetEvent(f_end);
	fclose(input);
	WaitForSingleObject(monitor, INFINITE);
	_getch();
	return 0;
}