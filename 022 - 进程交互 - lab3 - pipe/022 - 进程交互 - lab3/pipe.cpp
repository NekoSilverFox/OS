#include <stdio.h>
#include <windows.h>

#define BUFSIZE 50

char chBuf[BUFSIZE];

int main(int argc, char* argv[])
{
	DWORD dwRead, dwWritten;

	HANDLE hStdout, hInputFile;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);// PIPE!!!

	if ((hStdout == INVALID_HANDLE_VALUE))
		ExitProcess(1);

	LPCWSTR path_input = L"C:\\Users\\weidu\\OneDrive\\Desktop\\Programma\\OS\\Debug\\input.txt";
	// hInputFile = CreateFile("c:\\Users\\Admin\\source\\repos\\w_pipe\\debug\\input.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING,
	hInputFile = CreateFile(path_input, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_READONLY, NULL);

	while (TRUE)
	{

		if (!ReadFile(hInputFile, chBuf, BUFSIZE, &dwRead, NULL))
		{
			printf("Can'not read from file\n");
			ExitProcess(0);
		}

		printf("In buffer %s\n", chBuf);

		Sleep(5000);

		if (!WriteFile(hStdout, chBuf, dwRead, &dwWritten, NULL))
		{
			printf("Can'not write to pipe\n");
			ExitProcess(0);
		}

	}

}