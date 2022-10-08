// [운영체제] Program Assignment 3_2018380312 장서영
#include <Windows.h>	
#include <sysinfoapi.h> // GetSystemInfo()
#include <winnt.h>		// ULARGE_INTEGER 
#include <stdio.h>
#include <iostream>

#define MAX_LOOP 100
#define SLEEP_TIME 1000
#define MAX_PROCESS 1024

double cpuLoad();

int main(int arg, char* argv) { 

	// 1. GetSystemInfo()를 통해 현재 컴퓨터의 CPU 갯수를 출력한다.
	SYSTEM_INFO num;			
	GetSystemInfo(&num);
	printf("Number of CPUs : %d\n", num.dwNumberOfProcessors);

	// 2. (코드 하단에 정의한) cpuLoad()를 통해 1초마다 cpu load를 출력하고, 5/10/15초씩 cpu의 평균 load 또한 출력한다.
	SYSTEMTIME now;									
	double arr[MAX_PROCESS];						// (함수를 통해 받는) cpu load 값을 보관할 배열을 선언함
	double avg5 = 0.0, avg10 = 0.0, avg15 = 0.0;	// 5초, 10초, 15초 동안의 cpu 평균 load를 담을 변수를 선언함
	int i = 0;			

	for (; i < MAX_LOOP; i++) {	// 100번의 cpu laod 출력을 수행함

		arr[i] = cpuLoad(); // cpuLoad() 함수를 통해 받은 cpu load 값을 arr[0]~[99]에 순차적으로 저장함
		
		GetLocalTime(&now);	// GetLocalTime()을 통해 현재 날짜 및 시간을 출력함
		printf(" %3d %04d.%02d.%02d %02d:%02d:%02d : ", i, now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);

		if (i == 0) {		// i가 0일 때는(첫 번째 줄은) 출력하지 않음 
			printf("\n");
			continue;
		}

		printf("[CPU Load: %3.2f%%] ", arr[i]);

		// i가 5/10/15 이상일 때, (이전) 5초/10초/15초 동안의 cpu load 평균을 계산해 줄력함 
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

double cpuLoad() {	// cpu load 계산 함수 - 기준 시간 : 1초(1000밀리초)

	// DWORD(4 bytes) 대신 ULARE_INTEGER, __int64 사용 -> (https://stackoverflow.com/questions/29266743/what-is-dwlowdatetime-and-dwhighdatetime) 참고
	FILETIME IdleT, KernelT, UserT;	// (GetSystemTimes()을 통한 결과값을 담을) FILETIME 구조체 변수 세 개 선언함
	ULARGE_INTEGER IdT, KeT, UsT;	// (64비트 데이터를 담는) ULARGE_INTEGER 구조체 변수 세 개 선언함
	BOOL res;						

	// GetSystemtimes()는 idle, kernel, user times를 32비트씩 상단(high)/하단(low) 두 부분으로 나누어 반환한다.
	// 따라서, 각 times를 LowPart와 HighPart에 나누어서 할당한다.
	// 이후, ULARGE_INTEGER 구조체의 멤버 QuadPart를 활용해 (64비트의) Idle, Kernel, User 시간을 사용한다.
	/*
	  ULARGE_INTEGER members
	  - LowPart : The low-order 32 bits
	  - HighPart : The high-order 32 bits
	  - QuadPart : An unsigned 64-bit integer
	*/

	// 첫 번째 GetsystemTimes (1초 전)
	res = GetSystemTimes(&IdleT, &KernelT, &UserT);
	if (res == NULL) return 0;		// GetSystemtimes에 실패한 경우 zero를 리턴함

	IdT.LowPart = IdleT.dwLowDateTime;
	IdT.HighPart = IdleT.dwHighDateTime;
	KeT.LowPart = KernelT.dwLowDateTime;
	KeT.HighPart = KernelT.dwHighDateTime;
	UsT.LowPart = UserT.dwLowDateTime;
	UsT.HighPart = UserT.dwHighDateTime;

	__int64 IdleT_1 = IdT.QuadPart;
	__int64 KernelT_1 = KeT.QuadPart;
	__int64 UserT_1 = UsT.QuadPart;

	Sleep(SLEEP_TIME);

	// 두 번째 GetSystemTimes (현재 - 1초 경과 후)
	res = GetSystemTimes(&IdleT, &KernelT, &UserT);
	if (res == NULL) return 0;		// GetSystemtimes에 실패한 경우 zero를 리턴함

	IdT.LowPart = IdleT.dwLowDateTime;
	IdT.HighPart = IdleT.dwHighDateTime;
	KeT.LowPart = KernelT.dwLowDateTime;
	KeT.HighPart = KernelT.dwHighDateTime;
	UsT.LowPart = UserT.dwLowDateTime;
	UsT.HighPart = UserT.dwHighDateTime;

	__int64 IdleT_2 = IdT.QuadPart;
	__int64 KernelT_2 = KeT.QuadPart;
	__int64 UserT_2 = UsT.QuadPart;

	// 1초 동안 CPU가 일 한 시간(cpu load)를 구한다.
	__int64 IdleTime = IdleT_2 - IdleT_1;
	__int64 KernelTime = KernelT_2 - KernelT_1;
	__int64 UserTime = UserT_2 - UserT_1;

	double result = (double)(UserTime + KernelTime - IdleTime) / (UserTime + KernelTime) * 100;

	return result;

}
