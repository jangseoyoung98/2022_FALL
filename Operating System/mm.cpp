#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadFunc(LPVOID) {

	DWORD dwResult = 0;

	// CreateThread()�� ������ ���� ��, ����� �Լ�
	// -> �� Cij �� �ϳ��� �� �Լ��� ȣ��!

	return dwResult;
}

int main() {

	// ������ ����
	DWORD dwThreadID = 0;
	HANDLE hThread = 0; // ������ ���� ��, (Ŀ�� ������Ʈ) �ڵ�� ����

	hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &dwThreadID);
	// CreateThread -> ���� �� ������ Ŀ�� ������Ʈ�� �ڵ� / ���� �� NULL ����

	// ������ �ݱ�
	GetExitCodeThread(hThread, &dwThreadID);
	CloseHandle(hThread);

	return 0;
}