#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	// §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ
	theClock = 0;
	// §°§ä§Ü§â§í§ä§î §æ§Ñ§Û§Ý §ã§è§Ö§ß§Ñ§â§Ú§ñ §Ú §æ§Ñ§Û§Ý §à§ä§é§Ö§ä§Ñ
	scriptFID = fopen(argv[1], ¡±r¡±);
	reportFID = fopen(REPORT_FILE, ¡±w¡±);
	// §³§à§Ù§Õ§Ñ§ä§î §á§à§ä§à§Ü
	while (fscanf(¡­) != EOF)
	{
		if (time >= theClock) {
			if (time > theClock)
				simActivity(time ¨C theClock, NULL, 0);
			theClock = time;
		}
		//§³§é§Ú§ä§Ñ§ä§î §Ü§à§Þ§Ñ§ß§Õ§å §Ú§Ù §æ§Ñ§Û§Ý§Ñ §ã§è§Ö§ß§Ñ§â§Ú§ñ §Ú §Ó§í§á§à§Ý§ß§Ú§ä§î §Ö§Ö
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