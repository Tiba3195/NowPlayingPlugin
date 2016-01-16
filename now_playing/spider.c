#include "spider.h"

int spider (struct TrackInfo *info, struct TS3Functions ts3Functions) {
	HWND hwndCurrentWindow = 0;
	wchar_t wcharWindowText[500];	
	char cWindowText[500];
	int iFound = 0;
	int iStringLen = 0;

	do {
		hwndCurrentWindow = FindWindowEx (0, hwndCurrentWindow, "TApplication", 0);
		if (hwndCurrentWindow == 0) {
			break;
		}

		iStringLen = GetWindowTextW (hwndCurrentWindow, wcharWindowText, 500);
		if (iStringLen == 0) {
			continue;
		}
		
		iStringLen = WideCharToMultiByte (CP_UTF8, 0, wcharWindowText, 
						wcslen (wcharWindowText), cWindowText, 
						500, 0, 0);

		iStringLen -=  15; /* 15 = length of " - Spider Player" */

		if (strstr (cWindowText, " - Spider Player") != 0 && iStringLen >= 1) { 
			iFound = 1;

			memcpy (cWindowText, cWindowText, (iStringLen)); /* remove " - Spider Player" */
			cWindowText[iStringLen] = 0;
			strcpy_s (info->chTitle, sizeof (info->chTitle), cWindowText);
			info->chProgramm = "Spider Player";

			break;
		}
	} while (hwndCurrentWindow);
	
	return iFound;
}