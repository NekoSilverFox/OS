#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	// ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ�
	theClock = 0;
	// ����ܧ���� ��ѧۧ� ���֧ߧѧ�ڧ� �� ��ѧۧ� ����֧��
	scriptFID = fopen(argv[1], ��r��);
	reportFID = fopen(REPORT_FILE, ��w��);
	// ����٧էѧ�� ������
	while (fscanf(��) != EOF)
	{
		if (time >= theClock) {
			if (time > theClock)
				simActivity(time �C theClock, NULL, 0);
			theClock = time;
		}
		//����ڧ�ѧ�� �ܧ�ާѧߧէ� �ڧ� ��ѧۧݧ� ���֧ߧѧ�ڧ� �� �ӧ���ݧߧڧ�� �֧�
		switch (vmOp)
		{
		case 1: // Reverse a region
			break;
		case 2: // Commit a block
			22
				break;
		case 3: // Reset a block
			break;
		case 4: // Release a region
			break;
		case 5: // Decommit a block
			break;
		case 6: // Lock a block
			break;
		case 7: // Unlock a block
			break;
		} // switch
	}//while
}
void simActivity(int period, LPVOID lpAddress, DWORD dwSize)
{
#ifdef REALTIME
	Sleep(period);
#else
	Sleep(100);
#endif
	if (lpAdddress != NULL)
		ZeroMemory(lpAdress, dwSize);
}