#include <iostream>
#include <string>
#include <windows.h>
#define MEM_MAX_SIZE 1000
#define NAME_OF_SHARED_OBJEECT L"SharedMem1"
using namespace std;

void lockMemory() {};

HANDLE createSharedMemory()
{
	return CreateFileMappingW(INVALID_HANDLE_VALUE,
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,
		MEM_MAX_SIZE,
		NAME_OF_SHARED_OBJEECT
	);
}


void writeToView(HANDLE sharedObject,LPVOID offsetOfView,  wstring sDataForConsumer)
{
	//CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	CopyMemory(offsetOfView, sDataForConsumer.c_str(), sDataForConsumer.size() * sizeof(sDataForConsumer[0]));
}

LPVOID getView(HANDLE hSharedObject)
{
	return MapViewOfFile(
		hSharedObject,
		FILE_MAP_WRITE,
		0,
		0,
		MEM_MAX_SIZE);
}

int main()
{
	wstring sDataForConsumer;
	HANDLE hSharedObject  = createSharedMemory();
	LPVOID offsetOfView = getView(hSharedObject);
	while ( true)
	{
		lockMemory(); //TODO: implement

		cout << "Please enter data :" << endl;
		wcin >> sDataForConsumer;
		writeToView(hSharedObject, offsetOfView, sDataForConsumer);
		Sleep(1000);

	}
	CloseHandle(hSharedObject);
    

}

