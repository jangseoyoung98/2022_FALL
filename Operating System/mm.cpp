#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadFunc(LPVOID) {

	DWORD dwResult = 0;

	// CreateThread()로 스레드 생성 시, 실행될 함수
	// -> ★ Cij 셸 하나씩 이 함수로 호출!

	return dwResult;
}

int main() {

	// 스레드 생성
	DWORD dwThreadID = 0;
	HANDLE hThread = 0; // 스레드 생성 시, (커널 오브젝트) 핸들로 관리

	hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &dwThreadID);
	// CreateThread -> 성공 시 생성된 커널 오브젝트의 핸들 / 실패 시 NULL 리턴

	// 스레드 닫기
	GetExitCodeThread(hThread, &dwThreadID);
	CloseHandle(hThread);

	return 0;
}