#include <windows.h>
#include <tlhelp32.h>


char patch[] = { 0xC3 }; 

DWORD GetPID(LPCSTR pn)
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
	DWORD tpid = GetPID("Malware.exe");
	if (!tpid)
		return -1;
	
	HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS , 0, tpid);
	if (!ProcessHandle)
		return (-1);

	PVOID NTDEAddr = GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDelayExecution");
	if (!NTDEAddr)
		return(-1);

	if (!WriteProcessMemory(ProcessHandle, NTDEAddr, patch, 1, 0))
		return (-1);
	
	system("pause");
	return 0;
}
