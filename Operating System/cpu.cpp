#include <Windows.h> // Sleep()
#include <stdio.h>
#include <sysinfoapi.h> // GetSystemInfo()

// 매크로 상수 정의
#define MAX_LOOP 100
#define SLEEP_TIME 1000
#define MAX_PROCESS 1024

// cpu load 출력 함수
double cpuLoad() {

	// 1) 기준 시간 : 1초

	FILETIME IdleT, KernelT, UserT;
	
	// ★ 시간을 상위/하위 32비트(4바이트)로 구분한다는 게.. -> 아 둘이 연결해야 하나? 
	// 옛날 컴파일러는 64비트를 지원하지 않아서 32비트씩 분리해서 지원함
	// The low part contains the least significant 32 bits. The high part contains the most significant 32 bits
	// DWOR = unsigned long = 4 bytes -> DWORD * 2 = __int64
	/*
	GetSystemTimes(&IdleT, &KernelT, &UserT);
	DWORD IdLow1 = IdleT.dwLowDateTime;
	DWORD IdHigh1 = IdleT.dwHighDateTime;
	DWORD KeLow1 = KernelT.dwLowDateTime;
	DWORD KeHigh1 = KernelT.dwHighDateTime;
	DWORD UsLow1 = UserT.dwLowDateTime;
	DWORD UsHigh1 = UserT.dwHighDateTime;

	Sleep(1000); // 1초 기다림

	GetSystemTimes(&IdleT, &KernelT, &UserT);
	DWORD IdLow2 = IdleT.dwLowDateTime;
	DWORD IdHigh2 = IdleT.dwHighDateTime;
	DWORD KeLow2 = KernelT.dwLowDateTime;
	DWORD KeHigh2 = KernelT.dwHighDateTime;
	DWORD UsLow2 = UserT.dwLowDateTime;
	DWORD UsHigh2 = UserT.dwHighDateTime;
	*/

	// 1초 동안의 각 T을 계산함

	// (temp) 시간 연결하기 (https://stackoverflow.com/questions/29266743/what-is-dwlowdatetime-and-dwhighdatetime)
	ULARGE_INTEGER IdT, KeT, UsT;

	GetSystemTimes(&IdleT, &KernelT, &UserT);
	IdT.LowPart = IdleT.dwLowDateTime;
	IdT.HighPart = IdleT.dwHighDateTime;
	KeT.LowPart = KernelT.dwLowDateTime;
	KeT.HighPart = KernelT.dwHighDateTime;
	UsT.LowPart = UserT.dwLowDateTime;
	UsT.HighPart = UserT.dwHighDateTime;

	__int64 IdleT_1 = IdT.QuadPart;
	__int64 KernelT_1 = KeT.QuadPart;
	__int64 UserT_1 = UsT.QuadPart;

	Sleep(50); // 0.5초 기다림

	GetSystemTimes(&IdleT, &KernelT, &UserT);
	IdT.LowPart = IdleT.dwLowDateTime;
	IdT.HighPart = IdleT.dwHighDateTime;
	KeT.LowPart = KernelT.dwLowDateTime;
	KeT.HighPart = KernelT.dwHighDateTime;
	UsT.LowPart = UserT.dwLowDateTime;
	UsT.HighPart = UserT.dwHighDateTime;

	__int64 IdleT_2 = IdT.QuadPart;
	__int64 KernelT_2 = KeT.QuadPart;
	__int64 UserT_2 = UsT.QuadPart;

	// CPU 사용률 - 1초
	__int64 IdleTime = IdleT_2 - IdleT_1;
	__int64 KernelTime = KernelT_2 - KernelT_1;
	__int64 UserTime = UserT_2 - UserT_1;

	double result = (double)(UserTime + KernelTime - IdleTime) / (UserTime + KernelTime) * 100;

	return result;

}


int main(int arg, char* argv) { // main()의 매개변수 삽입

	// 1. CPU 갯수 -> OK
	SYSTEM_INFO num;
	GetSystemInfo(&num);
	printf("Number of CPUs : %d\n", num.dwNumberOfProcessors);


	// 2. cpu load 출력
	
	// 2-1) 번호 + 현재 시간 (기준 시간 1초) -> OK
	SYSTEMTIME now;
	unsigned int i = 0;
	double arr[MAX_PROCESS];

	for (; i < MAX_LOOP; i++) {

		// 2-2) cpu load 계산
		double result = cpuLoad();
		arr[i] = result;

		GetLocalTime(&now);
		printf(" %3d %04d.%02d.%02d %02d:%02d:%02d : ", i, now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);

		if(i >= 1)
			printf("[CPU Load: %0.2f%%] ", arr[i]);
		
		double avg5 = 0, avg10 = 0, avg15 = 0;

		if (i >= 5) {
			avg5 = (arr[i - 1] + arr[i - 2] + arr[i - 3] + arr[i - 4] + arr[i - 5]) / 5;
			printf("[5sec avg: %0.2f%%] ", avg5);
		}
		if (i >= 10) {
			avg10 = (avg5 * 5 + arr[i - 6] + arr[i - 7] + arr[i - 8] + arr[i - 9] + arr[i - 10]) / 10;
			printf("[10sec avg: %0.2f%%] ", avg10);
		}
		if (i >= 15) {
			avg15 = (avg10 * 10 + arr[i - 11] + arr[i - 12] + arr[i - 13] + arr[i - 14] + arr[i - 15]) / 15;
			printf("[15sec avg: %0.2f%%] ", avg15);
		}

		printf("\n");
		Sleep(SLEEP_TIME); // 1000밀리초 = 1초

		// continue;
	}

	return 0;
}
