#include <windows.h>
#include <stdio.h>
#include <string.h>

 LPCWSTR lpCommandLine[3]={L"C:\\WINDOWS\\SYSTEM32\\NOTEPAD.EXE temp.txt",
L"C:\\WINDOWS\\sYSTEM32\\CALC.EXE",L"C:\\WINNT\\SYSTEM32\\CHARMAP.EXE"};

STARTUPINFO startInfo;
PROCESS_INFORMATION processInfo;

int main(int argc, char* argv[])
{
	ZeroMemory(&startInfo,sizeof(STARTUPINFO));
	startInfo.cb=sizeof(startInfo);

	WCHAR proc_name[256];
	for(int i=0;i<3;i++)
	{
		wcscpy_s(proc_name, wcslen(lpCommandLine[i])+1, lpCommandLine[i]);
		printf("!!!%ls %d\n",lpCommandLine[i],wcslen(lpCommandLine[i]));
		
		if(!CreateProcess(NULL,proc_name,NULL,NULL,FALSE,
				  HIGH_PRIORITY_CLASS|CREATE_NEW_CONSOLE,NULL,NULL,
				  &startInfo,&processInfo))
		{
			fprintf(stderr,"CreateProcess failed on error %d\n",GetLastError());
			ExitProcess(1);
		}	
	}



printf("ProcessHandle=%d\n",(int)processInfo.hProcess);
printf("ThreadHandle=%d\n",(int)processInfo.hThread);

CloseHandle(processInfo.hProcess);
CloseHandle(processInfo.hThread);
return 0;
}