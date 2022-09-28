// [운영체제]Program Assignment 2_2018380312 장서영

#include <windows.h>	// 윈도우 기반 프로그래밍을 할 때 항상 포함해야 한다. (윈도우 API 함수의 정의를 포함하고 있음)
#include <psapi.h>		// EnumProcesses() 사용을 위해 필요하다.
#include <stdio.h>		// printf() 사용을 위해 필요하다.

int main() {

	while (1) {

		//1. 시간 가져오기 - GetLocalTime()
		SYSTEMTIME now;			// (windows.h에 정의되어 있는) SYSTEMTIME 구조체 변수 now를 생성한다.
		GetLocalTime(&now);		// GetLocalTime()의 인자로 now의 주소를 넘긴다. (함수의 매개변수 데이터형은 LPSYSTEMTIME. 즉, SYSTEMTIME의 포인터)
		printf("%d.%02d.%02d %02d:%02d:%02d : ", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);	// 멤버를 활용해, 날짜를 출력한다.

		// 2. 프로세스 정보 가져오기 - EnumProcesses()
		DWORD pidArray[1024];		// 프로세스 정보를 담아오기 위한 배열을 선언한다. (※ DWORD = unsigned long으로, win32 API를 다룰 때 자주 사용됨)
		DWORD bytesize, pidsize;	// 프로세스의 바이트 크기 & 개수를 관리하기 위한 변수를 선언한다.

		if (!(EnumProcesses(pidArray, sizeof(pidArray), &bytesize))) { // EnumProcesses()가 정상적으로 작동할 경우, 결과값은 nonzero이다.
			printf("프로세스 정보를 불러올 수 없습니다.\n");	
			return 1;
		}	
		
		pidsize = bytesize / sizeof(DWORD); // sizeof() 연산자를 활용해, 프로세스의 '개수'를 출력한다. (바이트 크기 X)
		printf("%d\n", pidsize);			
		Sleep(1000);						// 출력 후에는 1초(1000밀리초) 멈춘다.
		
	}

	return 0;
}
