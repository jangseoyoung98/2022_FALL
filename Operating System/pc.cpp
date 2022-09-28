// [�ü��]Program Assignment 2_2018380312 �弭��

#include <windows.h>	// ������ ��� ���α׷����� �� �� �׻� �����ؾ� �Ѵ�. (������ API �Լ��� ���Ǹ� �����ϰ� ����)
#include <psapi.h>		// EnumProcesses() ����� ���� �ʿ��ϴ�.
#include <stdio.h>		// printf() ����� ���� �ʿ��ϴ�.

int main() {

	while (1) {

		//1. �ð� �������� - GetLocalTime()
		SYSTEMTIME now;			// (windows.h�� ���ǵǾ� �ִ�) SYSTEMTIME ����ü ���� now�� �����Ѵ�.
		GetLocalTime(&now);		// GetLocalTime()�� ���ڷ� now�� �ּҸ� �ѱ��. (�Լ��� �Ű����� ���������� LPSYSTEMTIME. ��, SYSTEMTIME�� ������)
		printf("%d.%02d.%02d %02d:%02d:%02d : ", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);	// ����� Ȱ����, ��¥�� ����Ѵ�.

		// 2. ���μ��� ���� �������� - EnumProcesses()
		DWORD pidArray[1024];		// ���μ��� ������ ��ƿ��� ���� �迭�� �����Ѵ�. (�� DWORD = unsigned long����, win32 API�� �ٷ� �� ���� ����)
		DWORD bytesize, pidsize;	// ���μ����� ����Ʈ ũ�� & ������ �����ϱ� ���� ������ �����Ѵ�.

		if (!(EnumProcesses(pidArray, sizeof(pidArray), &bytesize))) { // EnumProcesses()�� ���������� �۵��� ���, ������� nonzero�̴�.
			printf("���μ��� ������ �ҷ��� �� �����ϴ�.\n");	
			return 1;
		}	
		
		pidsize = bytesize / sizeof(DWORD); // sizeof() �����ڸ� Ȱ����, ���μ����� '����'�� ����Ѵ�. (����Ʈ ũ�� X)
		printf("%d\n", pidsize);			
		Sleep(1000);						// ��� �Ŀ��� 1��(1000�и���) �����.
		
	}

	return 0;
}
