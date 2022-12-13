// os-06 과제 (2018380312 장서영)
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <cstring>
#include <stdbool.h>
#include <limits.h>
#include <fstream>
#include <iostream>
using namespace std;

#define MAX 100
#define DELIM ":"
#define MAX_LINE 1000

struct Process {// ▶ 프로세스 하나씩 구조체로 관리한다.
	char pName[MAX]; // 프로세스명
	
	int at; // arrival T
	int wt;	// waiting T
	int start_time;	// 시작 지점

	int burstList[MAX]; // (인덱스) 0, 2, 4 ... -> CPU burst라 가정 / 1, 3, 5 -> IO burst라 가정
	int pos = 0; // cpu burst인지 io burst인지 표시 (burstList의 인덱스)

} ps[100];

int main(int argc, char* argv[]) { 
	// char ** argv 와도 동일
	// argv[0] [1]이므로, input.txt는 [1]
	
	// ▼ 파일 불러오기
	char line[MAX_LINE]; // 파일로부터 읽은 내용을 저장할 변수(문자열),
	char* tok;			 // 파일을 읽어올 때, 사용할 토큰
	FILE* fp;			 // 파일을 읽어올 때, 사용할 FILE 포인터 변수
	int n = 0;			 // 프로세스의 저장 인덱스 (ps[n]) -> n + 1 : 프로세스 갯수

	if (!(fp = fopen(argv[1], "r"))) { printf("ERROR: file open\n"); exit(0); }	// 에러 처리
	
	while (fgets(line, MAX_LINE, fp))	// fgets(파일 데이터를 저장할 변수, 읽을 문자의 수, 읽을 파일)
	{									// 파일 내용을 한 줄씩 읽는다. -> 프로세스 하나씩

		char* pNum = strtok(line, "\t");
		strcpy(ps[n].pName, pNum);	// 1) 프로세스명

		tok = strtok(NULL, DELIM);
		tok = strtok(NULL, DELIM);
		ps[n].at = atoi(tok);		// 2) arrival T

		tok = strtok(NULL, DELIM);
		for (int i = 0; tok != NULL; i++) {
			ps[n].burstList[i] = atoi(tok);	// 3) CPU 혹은 IO burst (순서대로 배열에 저장)
			tok = strtok(NULL, DELIM);
		}
		n++;
	}
	fclose(fp);

	// cout << ps[0].pName << endl;
	// cout << ps[0].at << endl;

	int sum_wt = 0;	 // 모든 프로세스의 waiting T을 누적한다.
	int max_completion_time, min_arrival_time;

	bool is_completed[MAX] = { false }; // 프로세스가 terminated 되었는지 확인. (burst가 다 끝나면 해당 인덱스는 true로 변경)

	int sch = 0; // 스케줄러의 위치
	int completed = 0;
	int current_time = 0; // 전체 시간 (Gantt 차트)

	while (completed != n) {

		// 1. cpu burst가 가장 작은 프로세스에게 스케줄러를 할당한다.
		int min_index = -1;	// running으로 가게 된, 실행 시작한 프로세스의 인덱스
		int minimum = INT_MAX;

		for (int i = 0; i < n; i++) {
			if (ps[i].at <= current_time && is_completed[i] == false) {	// i번째부터 검사할 때, 이미 도착한 (i번째) 프로세스가 terminated된 게 아닐 경우 검사
				if (ps[i].burstList[ps[i].pos] < minimum) {				// cpu burst가 더 작은지 비교
					minimum = ps[i].burstList[ps[i].pos];
					min_index = i;
				}
				if (ps[i].burstList[ps[i].pos] == minimum) { // cpu burst가 동일할 때, 먼저 온 프로세스가 선발된다.
					if (ps[i].at < ps[min_index].at) {	
						minimum = ps[i].burstList[ps[i].pos];
						min_index = i;
					}
				}
			}
		}

		// 2. 더 작은 burst를 가진 프로세스에 cpu를 할당한다.
		if (min_index == -1) { // idle time (즉, 다음에 할당할 프로세스가 레디 큐에 없음)
			current_time++;
		}
		else {
			ps[min_index].start_time = current_time;
			sch = ps[min_index].start_time + ps[min_index].burstList[ps[min_index].pos];
			ps[min_index].pos++;
			ps[min_index].wt = ps[min_index].start_time - ps[min_index].at;

			sum_wt += ps[min_index].wt;

			completed++;
			is_completed[min_index] = true;
			current_time = sch;

		}
	}

	// 결과 출력
	printf("\nProcess : Waiting Time\n");
	printf("--------------------------------------\n");
	for (int i = 0; i < n; i++) {
		cout << ps[i].pName << "\t : " << ps[i].wt << endl;
	}
	printf("--------------------------------------\n");
	printf("Average Waiting Time  =  %.2f", (float)sum_wt / n + 1);


	return 0;
}
