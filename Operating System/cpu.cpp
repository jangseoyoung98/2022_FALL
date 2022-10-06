#include <Windows.h>
#include <stdio.h>
#include <sysinfoapi.h>

// FILETIME - 파일 시간을 사용하여 작업할 때 매크로 상수 정의하겠음
#define SEC ((int64) 10000000) // 100 나노초 간격 기반 
#define MIN (60 * SEC)
#define HOUR (60 * MIN)
#define DAY (24 * HOUR)

// cpu 사용량 출력 함수
double cpuLoad() {

	FILETIME IdleT, KernelT, UserT;
	
	// GetSystemTimes() 사용 -> BOOL 리턴
	GetSystemTimes(&IdleT, &KernelT, &UserT);
	DWORD Id_h = IdleT.





	return;
}


int main() {


	cpuLoad();


	return 0;
}
