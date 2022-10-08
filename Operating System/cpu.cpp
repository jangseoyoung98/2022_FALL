#include <Windows.h>	// Sleep() 등 
#include <sysinfoapi.h> // GetSystemInfo()
#include <winnt.h>		// ULARGE_INTEGER 

#include <stdio.h>


// 매크로 상수
#define MAX_LOOP 100
#define SLEEP_TIME 1000
#define MAX_PROCESS 1024

// cpu load 계산 함수 (기준 시간 1 sec)
double cpuLoad() {
	
	/*
	GetSystemTimes(&IdleT, &KernelT, &UserT);
	DWORD IdLow1 = IdleT.dwLowDateTime;
	DWORD IdHigh1 = IdleT.dwHighDateTime;
	DWORD KeLow1 = KernelT.dwLowDateTime;
	DWORD KeHigh1 = KernelT.dwHighDateTime;
	DWORD UsLow1 = UserT.dwLowDateTime;
	DWORD UsHigh1 = UserT.dwHighDateTime;

	Sleep(1000);

	GetSystemTimes(&IdleT, &KernelT, &UserT);
	DWORD IdLow2 = IdleT.dwLowDateTime;
	DWORD IdHigh2 = IdleT.dwHighDateTime;
	DWORD KeLow2 = KernelT.dwLowDateTime;
	DWORD KeHigh2 = KernelT.dwHighDateTime;
	DWORD UsLow2 = UserT.dwLowDateTime;
	DWORD UsHigh2 = UserT.dwHighDateTime;
	*/

	// DWORD(4 bytes) 대신 ULARE_INTEGER, __int64 사용 -> (https://stackoverflow.com/questions/29266743/what-is-dwlowdatetime-and-dwhighdatetime) 참고
	
	FILETIME IdleT, KernelT, UserT;
	ULARGE_INTEGER IdT, KeT, UsT;
	BOOL res;
	
	res = GetSystemTimes(&IdleT, &KernelT, &UserT);
	if (res == NULL) 
		return 0; // if it can't get system times, it will return zero.

	IdT.LowPart = IdleT.dwLowDateTime;
	IdT.HighPart = IdleT.dwHighDateTime;
	KeT.LowPart = KernelT.dwLowDateTime;
	KeT.HighPart = KernelT.dwHighDateTime;
	UsT.LowPart = UserT.dwLowDateTime;
	UsT.HighPart = UserT.dwHighDateTime;

	__int64 IdleT_1 = IdT.QuadPart;
	__int64 KernelT_1 = KeT.QuadPart;
	__int64 UserT_1 = UsT.QuadPart;

	Sleep(SLEEP_TIME); // 1초 기다림

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

	// CPU 사용률 -> 1초
	__int64 IdleTime = IdleT_2 - IdleT_1;
	__int64 KernelTime = KernelT_2 - KernelT_1;
	__int64 UserTime = UserT_2 - UserT_1;

	double result = (double)(UserTime + KernelTime - IdleTime) / (UserTime + KernelTime) * 100;

	return result;
	
	/* 왜 아래처럼 해야 하는지 이해 안 감..!!
	// set high, low in FILETIME structure (first time)
		idle_High = idleTime.dwHighDateTime;
		idle_Low = idleTime.dwLowDateTime;
		kernel_High = kernelTime.dwHighDateTime;
		kernel_Low = kernelTime.dwLowDateTime;
		user_High = userTime.dwHighDateTime;
		user_Low = userTime.dwLowDateTime;

		high_1 = idle_High + kernel_High + user_High;
		Low_1 = idle_Low + kernel_Low + user_Low;

		Sleep(1000); // sleep to get system time for 1 sec

		res = GetSystemTimes(&idleTime, &kernelTime, &userTime); // get system times (idle, kernel, user)
		if (res == NULL) return 0; // if it can't get system times, it will return zero.

		// set high, low in FILETIME structure (second time)
		idle_High_2 = idleTime.dwHighDateTime;
		idle_Low_2 = idleTime.dwLowDateTime;
		kernel_High_2 = kernelTime.dwHighDateTime;
		kernel_Low_2 = kernelTime.dwLowDateTime;
		user_High_2 = userTime.dwHighDateTime;
		user_Low_2 = userTime.dwLowDateTime;

		high_2 = idle_High_2 + kernel_High_2 + user_High_2;
		Low_2 = idle_Low_2 + kernel_Low_2 + user_Low_2;

		// calculate time (first time minus second time)
		idle = idle_Low_2 - idle_Low; // get time in idle mode 
		kernel = kernel_Low_2 - kernel_Low;  // get time in kernel mode
		user = user_Low_2 - user_Low;  // get time in user mode
	*/
}


int main(int arg, char* argv) { // main()의 매개변수 삽입

	// 1. CPU 갯수 -> OK
	SYSTEM_INFO num;
	GetSystemInfo(&num);
	printf("Number of CPUs : %d\n", num.dwNumberOfProcessors);

	// 2. cpu load 출력 -> OK..?
	SYSTEMTIME now;
	double arr[MAX_PROCESS];
	double avg5 = 0.0, avg10 = 0.0, avg15 = 0.0;
	int i = 0;

	for (; i < MAX_LOOP; i++) {

		arr[i] = cpuLoad();

		GetLocalTime(&now);
		printf(" %3d %04d.%02d.%02d %02d:%02d:%02d : ", i, now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);

		if (i == 0) {
			printf("\n");
			continue;
		}

		printf("[CPU Load: %3.2f%%] ", arr[i]);
		
		if (i >= 5) {
			avg5 = (arr[i - 1] + arr[i - 2] + arr[i - 3] + arr[i - 4] + arr[i - 5]) / 5;
			printf("[5sec avg: %3.2f%%] ", avg5);
		}
		if (i >= 10) {
			avg10 = (avg5 * 5 + arr[i - 6] + arr[i - 7] + arr[i - 8] + arr[i - 9] + arr[i - 10]) / 10;
			printf("[10sec avg: %3.2f%%] ", avg10);
		}
		if (i >= 15) {
			avg15 = (avg10 * 10 + arr[i - 11] + arr[i - 12] + arr[i - 13] + arr[i - 14] + arr[i - 15]) / 15;
			printf("[15sec avg: %3.2f%%] ", avg15);
		}

		printf("\n");
	}

	return 0;
}
