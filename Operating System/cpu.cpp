#include <Windows.h> // Sleep()
#include <stdio.h>
#include <sysinfoapi.h> // GetSystemInfo()

// 매크로 상수 정의
#define MAX_LOOP 100
#define SLEEP_TIME 1000
#define MAX_PROCESS 1024

/* 
// FILETIME - 파일 시간을 사용하여 작업할 때 매크로 상수 정의하겠음
#define SEC ((int64) 10000000) // 100 나노초 간격 기반 
#define MIN (60 * SEC)
#define HOUR (60 * MIN)
#define DAY (24 * HOUR)
*/

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

	Sleep(1000); // 1초 기다림

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

	// 1초 동안!
	__int64 IdleTime = IdleT_2 - IdleT_1;
	__int64 KernelTime = KernelT_2 - KernelT_1;
	__int64 UserTime = UserT_2 - UserT_1;

	double result = (double)(UserTime + KernelTime - IdleTime) / (UserTime + KernelTime) * 100;

	printf("%.2f", result);
	return result;

	// 오~~ 일단 1초 동안은 한 거 같다!
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

	for (; i < MAX_LOOP; i++) {
	
		GetLocalTime(&now);
		printf(" %3d %04d.%02d.%02d %02d:%02d:%02d : ", i, now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);

		// 2-2) cpu load 계산
		cpuLoad();
		
		Sleep(SLEEP_TIME); // 1000밀리초 = 1초

		// continue;
	}

	return 0;
}
