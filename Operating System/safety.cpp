#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

# define MAX 100
// 벡터
int g_Available[1][MAX];
int g_Work[1][MAX];	// new available
// 행렬
int g_Max[MAX][MAX];
int g_Allocation[MAX][MAX];
int g_Need[MAX][MAX];

int g_Process_finish[MAX];
int g_Process_sequence[MAX];

int g_Process_num = 0;
int g_Resource_num = 0;

void init() {

	int r, c;

	for (r = 0; r < MAX; r++) {
		for (c = 0; c < MAX; c++) {
			g_Max[r][c] = 0;
			g_Allocation[r][c] = 0;
			g_Need[r][c] = 0;
			g_Available[0][c] = 0;
		}
	}

	for (r = 0; r < MAX; r++) {
		g_Process_finish[r] = 0;
		g_Process_sequence[r] = 0;
	}

}

#define MAX_LINE 1000
#define DELIM "\t\r\n"
void read_file(char* filename) {
	FILE* fp;
	char line[MAX_LINE], * ret;
	int i = 0, flag = 0, index, r, c;

	if (!(fp = fopen(filename, "r"))) { printf("ERROR READ FILE\n"); exit(1); }
	
	while (fgets(line, MAX_LINE, fp)) {
		printf("%s", line);

		ret = strtok(line, DELIM);
		if (ret == NULL) continue;

		if (flag == 0) {
			g_Resource_num = atoi(ret);
			g_Process_num = atoi(strtok(NULL, DELIM));
			flag++;
			index = 0;
			continue;
		}

		if (flag == 1) {
			if (strcmp("Allocation", ret) == 0) continue;
			if (strcmp("MAX", ret) == 0) { flag++; index = 0; continue; }
			for (i = 0; i < g_Resource_num; i++)
				g_Allocation[index][i] = atoi(strtok(NULL, DELIM));
			index++;
			continue;
		}

		if (flag == 2) {
			if (strcmp("MAX", ret) == 0) continue;
			if (strcmp("Available", ret) == 0) { flag++; index = 0; continue; }
			for (i = 0; i < g_Resource_num; i++)
				g_Max[index][i] = atoi(strtok(NULL, DELIM));
			index++;
			continue;
		}

		if (flag == 3) {
			if (strcmp("Available", ret) == 0) continue;
			g_Available[index][0] = g_Work[index][0] = atoi(ret);
			for (i = 0; i < g_Resource_num; i++)
				g_Available[index][i] = g_Work[index][i] = atoi(strtok(NULL, DELIM));
			index++;
			continue;
		}
	}
	fclose(fp);

	for (r = 0; r < g_Process_num; r++) {
		for (c = 0; c < g_Resource_num; c++) {
			g_Need[r][c] = g_Max[r][c] - g_Allocation[r][c];
		}
	}

	printf("\n");

}

void print_matrix(int matrix[MAX][MAX], int p_f, int p_c) {
	
	for (int i = 0; i < p_f; i++) {
		printf("                    ");
		for (int j = 0; j < p_c; j++) {
			printf("%2d  ", matrix[i][j]);
			printf("\n");
		}
	}
	printf("\n");
}

void print_all() {

	printf("-------------------------------------------\n");
	printf("Number of Resources: %3d\n", g_Resource_num);
	printf("Number of Processes: %3d\n", g_Process_num);
	printf("\n");

	printf("Allocation  ");
	for (int i = 0; i < g_Resource_num; i++) {
		printf(" %c ", 'A' + i);
	}
	printf("\n");
	print_matrix(g_Allocation, g_Process_num, g_Resource_num);

	printf("Max         ");
	for (int i = 0; i < g_Resource_num; i++) {
		printf(" %c ", 'A' + i);
	}
	printf("\n");
	print_matrix(g_Max, g_Process_num, g_Resource_num);

	printf("Available  ");
	for (int i = 0; i < g_Resource_num; i++) {
		printf(" %c ", 'A' + i);
	}
	printf("\n");
	print_matrix(g_Available, g_Process_num, g_Resource_num);

	printf("Need       ");
	for (int i = 0; i < g_Resource_num; i++) {
		printf(" %c ", 'A' + i);
	}
	printf("\n");
	print_matrix(g_Need, g_Process_num, g_Resource_num);

	printf("Work       ");
	for (int i = 0; i < g_Resource_num; i++) {
		printf(" %c ", 'A' + i);
	}
	printf("\n");
	print_matrix(g_Work, g_Process_num, g_Resource_num);

	printf("Process     \n");
	for (int i = 0; i < g_Process_num; i++)
		printf("P_%02d %2d\n", i, g_Process_finish);

	printf("-------------------------------------\n");
	getchar();
}

int is_acceptable(int p_i) { // 워크보다 니드가 작은지 체크
	int i;

	for (i = 0; i < g_Resource_num; i++) {
		if (g_Need[p_i][i] > g_Work[0][i]) return 0;
 	}
	return 1;
}

void add_to_Work(int p_i) { // 프로세스 선택 되면, 리소스 종료시키고 워크 업데이트
	int i;

	for (i = 0; i < g_Resource_num; i++) {
		g_Work[0][i] += g_Allocation[p_i][i];
	}
}

void run_safety() {
	int i;
	int p_count = 0;
	while (p_count < g_Process_num) {
		for (i = 0; i < g_Process_num; i++) {
			if (g_Process_finish[i]) continue;
			if (!is_acceptable(i)) continue;
			break;
		}
		if (i == g_Process_num) break;

		g_Process_sequence[p_count++] = i;
		g_Process_finish[i] = p_count;
		add_to_Work(i);

	}
	print_all();

	printf("---------------------------");
	if (p_count == g_Process_num)
	{
		printf("Result: Safe --> ");
		for (i = 0; i < g_Process_num; i++)
			printf("P_%02d ", g_Process_sequence[i]);
		printf("\n");
	}
	else
	{
		printf("Result: Unsafe --> ");
		for (i = 0; i < g_Process_num; i++) {
			if (!g_Process_finish[i])
				printf("P_%02d ", g_Process_sequence[i]);
		}
		printf("\n");
	}


}


int main(int argc, char* argv[]) {

	if (argc != 2) { printf("ERROR: No input file!\n"); exit(1); }
	init();
	read_file(argv[1]);
	print_all();

	return 0;
}