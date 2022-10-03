#include <Windows.h>
#include <sysinfoapi.h>
#include <stdio.h>

// cpu 사용량 구하는 함수
double cpu() {
	FILETIME idle, kernel, user; /* FILETIME : structure typedef - dwLowDateTime, dwHighDateTime */
	int i = 0;
	double r = 0;

	GetSystemTimes(&idle, &kernel, &user);
	DWORD kehigh1 = kernel.dwHighDateTime;
	DWORD kelow1 = kernel.dwLowDateTime;
	DWORD ushigh1 = user.dwHighDateTime;
	DWORD uslow1 = user.dwLowDateTime;
	DWORD idhigh1 = idle.dwHighDateTime;
	DWORD idlow1 = idle.dwLowDateTime;
	// ★1. dwLowDateTime, dwHighDateTime ? -> 즉, GetSystemTimes()를 알아야!
	// ★2. idle, kernel, user 각각의 역할 ?

	Sleep(500);

	GetSystemTimes(&idle, &kernel, &user);
	DWORD kehigh2 = kernel.dwHighDateTime;
	DWORD kelow2 = kernel.dwLowDateTime;
	DWORD ushigh2 = user.dwHighDateTime;
	DWORD uslow2 = user.dwLowDateTime;
	DWORD idhigh2 = idle.dwHighDateTime;
	DWORD idlow2 = idle.dwLowDateTime;

	// ★3. while 부분 이해 잘 안 됨 (___1과 ___2 변수의 값은 고정되어 있는데?)
	while (i <= 5) {
		double ke = (kehigh2 + kelow2) - (kehigh1 + kelow1);
		double us = (ushigh2 + uslow2) - (ushigh1 + uslow1);
		double id = (idhigh2 + idlow2) - (idhigh1 + idlow1);
		double res = (us + ke - id) * 100 / (us + ke);
		Sleep(100);
		r = r + res;
		i++;
	}

	return r / 5;

}

int main() {

	int n = 0;
	double a[1000];
	SYSTEMTIME t;
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	// ★4. GetSystemInfo() ?

	printf("Number of CPU's : %d\n", info.dwNumberOfProcessors);

	while (1) {
		GetLocalTime(&t);
		double rr = cpu();
		a[n] = rr;

		// cpu 사용량 출력 시작


		n++;
	}




	return 0;
}
