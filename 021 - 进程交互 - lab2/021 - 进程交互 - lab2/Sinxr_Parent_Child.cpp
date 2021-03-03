#include <string.h>
#include <windows.h>
#include <stdio.h>

char Name[50];
char path[200];
char str[200];

HANDLE hEvent;

// SECURITY_ATTRIBUTES，结构包含一个对象的安全描述符，并指定检索到指定这个结构的句柄是否是可继承的
SECURITY_ATTRIBUTES SecurityAttributes;

// 在创建进程时相关的数据结构之一，该结构返回有关新进程及其主线程的信息
PROCESS_INFORMATION ProcessInf;

// STARTUPINFO用于指定新进程的主窗口特性的一个结构
STARTUPINFO StartInfo;


LPWSTR ConvertCharToLPWSTR(const char* szString)

{

	int dwLen = strlen(szString) + 1;

	int nwLen = MultiByteToWideChar(CP_ACP, 0, szString, dwLen, NULL, 0);//算出合适的长度

	LPWSTR lpszPath = new WCHAR[dwLen];

	MultiByteToWideChar(CP_ACP, 0, szString, dwLen, lpszPath, nwLen);

	return lpszPath;

}

int main(int argc, char* argv[])
{
	strcpy_s(Name, "Parent");

	SecurityAttributes.bInheritHandle = TRUE;  // 安全描述的对象能否被新创建的进程继承
	SecurityAttributes.lpSecurityDescriptor = NULL;  // 安全描述符
	SecurityAttributes.nLength = sizeof(SecurityAttributes);  // 结构体的大小，可用SIZEOF取得

	//printf("Enter path to child process:\n");
	//gets(path);
	// strcpy_s(path, "c:\\Users\\Admin\\source\\repos\\child\\debug");
	strcpy_s(path, "C:\\Users\\weidu\\OneDrive\\Desktop\\Programma\\OS\\Debug");
	strcat_s(path, "\\");

	strcat_s(path, "child2.exe");
	// strcat_s(path, "021 - 进程交互 - lab2.exe");
	strcat_s(path, " ");

	hEvent = CreateEvent(&SecurityAttributes, FALSE, TRUE, NULL);

	_itoa_s((int)hEvent, str, 10);
	strcat_s(path, str);

	memset(&StartInfo, 0, sizeof(StartInfo));
	StartInfo.cb = sizeof(StartInfo);
	//StartInfo.lpTitle="Child";

	// LPWSTR path_input = L"C:\\Users\\weidu\\OneDrive\\Desktop\\Programma\\OS\\Debug";
	if (!CreateProcess(NULL, ConvertCharToLPWSTR(path), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL,
		&StartInfo, &ProcessInf))
	{
		printf("Could not create child process!\n");
		CloseHandle(hEvent);
		return 0;
	}

	while (TRUE)
	{
		strcpy_s(str, "a");

		WaitForSingleObject(hEvent, INFINITE);

		printf("Hello! My name is %s\n", Name);

		while (strcmp(str, "good buy"))
		{
			if (!strcmp(str, "exit"))
			{
				SetEvent(hEvent);

				CloseHandle(hEvent);

				return 0;
			}

			gets_s(str);
			printf("User input %s\n", str);
		}

		printf("good buy!\n");
		SetEvent(hEvent);

	}

	return 0;

}