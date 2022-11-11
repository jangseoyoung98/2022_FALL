#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROW 100
#define MAX_COL 100

int A[MAX_ROW][MAX_COL];
int Ar, Ac;	// 행, 열 "갯수"

int B[MAX_ROW][MAX_COL];
int Br, Bc;	// 행, 열 "갯수"

int result[MAX_ROW][MAX_COL];

//#########################################################################################
/* 파일로부터 읽기 -> read.from.file.cpp 참고 */
#define DELIM		" \r\t"
#define MAX_LINE	1000
void read_matrix(int tmp[MAX_ROW][MAX_COL], int& tmpR, int& tmpC, char* filename)
{
	char line[MAX_LINE], * tok;
	FILE* fp;

	if (!(fp = fopen(filename, "r"))) { printf("ERROR: file open\n"); exit(0); }
	tmpR = 0;
	while (fgets(line, MAX_LINE, fp))
	{
		tok = strtok(line, DELIM);
		tmpC = 0;
		do
		{
			tmp[tmpR][tmpC++] = atoi(tok);

		} while (tok = strtok(NULL, DELIM));
		tmpR++;
	}
	fclose(fp);
}

//#########################################################################################
/* 행렬의 곱셈을 수행 (thread entry point) */
int i = 0, j = 0;	// A[i][] & B[][j]
DWORD WINAPI ThreadFunc_Multi(LPVOID) {

	int sum = 0;

	for (int k = 0; k < Ac; k++) {
		sum = sum + (A[i][k] * B[k][j]);
	}
	result[i][j] = sum;
	return 0;
}

//#########################################################################################
/* 행렬 곱의 결과를 출력 */
DWORD WINAPI ThreadFunc_Print(LPVOID) {
	
	printf("\n\n");

	for (int row = 0; row < Ar; row++) {
		for (int col = 0; col < Ac; col++) {
			printf("\t%5d", A[row][col]);
		}
		printf("\n");
	}
	return 0;
}

int main(int argc, char** argv) {

	// 프로세스 수행 시간 합계 + 출력
	clock_t start, finish;
	double totalT;

	start = clock();

	// 1. 예외 처리 (콘솔창 입력 인자 : max 10개)
	if (argc < 2 || argc > 11)
	{
		printf("ERROR: input sequence! ...\n"); return 0;
		printf("Usage: read_matrix <filename> \n"); return 0;
	}

	// 2. 스레드 생성으로 행렬 곱셈을 수행한다.
	DWORD dwThreadID[MAX_ROW * MAX_COL] = { 0, };
	HANDLE hThread[MAX_ROW * MAX_COL] = { 0, };

	memset(A, 0, sizeof(int) * MAX_ROW * MAX_COL);
	Ar = Ac = 0;
	read_matrix(A, Ar, Ac, argv[1]);

	int cnt;	// 커널 오브젝트(배열)의 인덱스
	int fileCnt;	// 콘솔 입력 인자 2번째부터
	for (fileCnt = 2; fileCnt < argc; fileCnt++) {
		memset(B, 0, sizeof(int) * MAX_ROW * MAX_COL);
		Br = Bc = 0;
		read_matrix(B, Br, Bc, argv[fileCnt]);

		if (Ac != Br) {
			printf("행렬곱이 불가능합니다.\n");
			return -1;
		}

		cnt = 0;
		Sleep(1000);
		for (i = 0; i < Ar; i++) { // i +1 증가되고 끝남
			for (j = 0; j < Bc; j++) { // j +1 증가되고 끝남
				hThread[cnt] = CreateThread(NULL, 0, ThreadFunc_Multi, 0, 0, &dwThreadID[cnt]);
				printf("\t");
				cnt++;
			}
		}

		// 3. 스레드 함수들이 행렬 곱셈을 마칠 때까지 대기한다.
		WaitForMultipleObjects(cnt, hThread, TRUE, INFINITE);

		// 4. 스레드를 닫는다.
		int close;
		for (close = 0; close < cnt; close++)
			CloseHandle(hThread[close]);

		// 출력하기
		printf("\n<%5dx%-5d> X <%5dx%-5d> = <%5dx%-5d>", Ar, Ac, Br, Bc, i, j);

		// result를 A에 옮기고
		// B에 다음 파일 값을 넣어서
		// A와 B부터 실행하기!!
		for (int row = 0; row < i; row++) {
			for (int col = 0; col < j; col++) {
				A[row][col] = result[row][col];
			}
		}
		Ar = i;
		Ac = j;
	}


	// 행렬 곱셈 결과 -> 파일 생성
	FILE* rstFp = fopen("result.txt", "w");
	for (int row = 0; row < Ar; row++) {
		for (int col = 0; col < Ac; col++) {
			fprintf(rstFp, "%5d", A[row][col]); // rstFp가 가리키는 파일에다가 행렬값 작성
		}
		fprintf(rstFp, "\n"); // rstFp가 가리키는 파일에다가 문자열 쓰기
	}
	fclose(rstFp);


	// 행렬 곱셈 결과 -> 콘솔 출력
	hThread[cnt] = CreateThread(NULL, 0, ThreadFunc_Print, 0, 0, &dwThreadID[cnt]);
	if (!(hThread[cnt])) {
		printf("행렬곱 출력을 수행하는 데 문제가 발생했습니다!\n");
		exit(1);
	}

	// thread 함수가 출력을 마칠 때까지 대기한다.
	WaitForSingleObject(hThread[cnt], INFINITE);

	// 닫는다.
	CloseHandle(hThread[cnt]);


	finish = clock();
	totalT = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\nProcessing Time:\t%.3f sec\n", totalT);

	return 0;
}
