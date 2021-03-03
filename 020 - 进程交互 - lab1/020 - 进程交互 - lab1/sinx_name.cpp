#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>

// ручка - 通过这个中间媒介可控制、操作某样东西
HANDLE hEvent;

WCHAR proc_name[50];
WCHAR str[50];

int wmain(int argc, WCHAR* argv[])
{
	if (argc >= 2)
	{
		wcscpy_s(proc_name, wcslen(argv[1]) + 1, argv[1]);
	}
	else
	{
		wcscpy_s(proc_name, wcslen(L"Default Proc_name") + 1, L"Default Proc_name");
	}

	// CreateEvent是一个WindowsAPI函数。它用来创建或打开一个命名的或无名的事件对象
	// 一个Event被创建以后，可以用OpenEvent()API来获得它的Handle
	// event - событие - 事件
	hEvent = CreateEvent(NULL, FALSE, TRUE, L"exclusive_speech_event");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("Event was opened\n");
	}
	else
	{
		printf("Event was created\n");
	}

	while (TRUE)
	{
		wcscpy_s(str, wcslen(L"a") + 1, L"a");

#if 0
		WaitForSingleObject是一种Windows API函数，当等待仍在挂起状态时，句柄被关闭，那么函数行为是未定义的。
		该句柄必须具有 SYNCHRONIZE 访问权限。

		WaitForSingleObject函数用来检测hHandle事件的信号状态，在某一线程中调用该函数时，线程暂时挂起，
		如果在挂起的dwMilliseconds毫秒内，线程所等待的对象变为有信号状态，则该函数立即返回；
		如果时间已经到达dwMilliseconds毫秒，但hHandle所指向的对象还没有变成有信号状态，函数照样返回。
#endif
		// Нить временно подвешена 线程暂时挂起
		WaitForSingleObject(hEvent, INFINITE);  // INFINITE 无穷

		printf("Hello! My name is %ls\n", proc_name);

		while (wcscmp(str, L"goodbye"))
		{
			if (!wcscmp(str, L"exit"))
			{
				// 用SetEvent（）或PulseEvent（）来设置它使其有信号
				SetEvent(hEvent);

				// 用CloseHandle()来关闭它 Event
				CloseHandle(hEvent);

				return 0;
			}

			_getws_s(str, 10);
			printf("User input %ls\n", str);
		}

		printf("goodbye!\n");
		SetEvent(hEvent);
	}

}