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
		if (n == 0)
			printf("%d %d.%02d.%02d  %02d:%02d:%02d  : ", n, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);

		if (n >= 1)
			printf("%d %d.%02d.%02d  %02d:%02d:%02d  : [CPU Load: %0.2f%%]", n, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, rr);

		if (n < 5)
			printf("\n");
		else if (n >= 5 && n < 10)
			printf(" [5sec avg]: %0.2f%%\n",
				(double)(a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 5);
		else if (n >= 10 && n < 15)
			printf(" [5sec avg]: %0.2f%% [10sec avg]: %0.2f%%\n",
				(double)(a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 5,
				(double)(a[n - 9] + a[n - 8] + a[n - 7] + a[n - 6] + a[n - 5] + a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 10);
		else if (n >= 15)
			printf(" [5sec avg]: %0.2f%% [10sec avg]: %0.2f%% [15sec avg]: %0.2f%%\n",
				(double)(a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 5,
				(double)(a[n - 9] + a[n - 8] + a[n - 7] + a[n - 6] + a[n - 5] + a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 10,
				(double)(a[n - 14] + a[n - 13] + a[n - 12] + a[n - 11] + a[n - 10] + a[n - 9] + a[n - 8] + a[n - 7] + a[n - 6] + a[n - 5] + a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 15);
		
		n++;
	}




	return 0;
}
