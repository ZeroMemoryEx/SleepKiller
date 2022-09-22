#include <windows.h>
#include <tlhelp32.h>


unsigned long long patch[] = { 0x90, 0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0xC3
};


DWORD GetPID(const char* pn)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pE;
		pE.dwSize = sizeof(pE);

		if (Process32First(hSnap, &pE))
		{
			if (!pE.th32ProcessID)
				Process32Next(hSnap, &pE);
			do
			{
				if (!_stricmp(pE.szExeFile, pn))
				{
					procId = pE.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &pE));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

int wmain() {

	int i = 0;
	DWORD tpid = 0;
	HANDLE hw = OpenProcess(PROCESS_ALL_ACCESS, 0, tpid = GetPID("Malware.exe"));
	if (!hw)
		return (-1);

	unsigned long long baseAdd = (unsigned long long)GetProcAddress(GetModuleHandleA("kernel32.dll"), "Sleep");
	if (!baseAdd)
		return(-1);

	while (i < (sizeof(patch) / 8))
	{
		if (!WriteProcessMemory(hw, (LPVOID)(baseAdd + i), &patch[i++], 1, 0))
			return (-1);
	}
	system("pause");
	return 0;
}
