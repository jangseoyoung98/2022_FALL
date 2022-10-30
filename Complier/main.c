#include "scanner.c"

FILE* srcFile, * rstFile; // 스캐너의 입력 및 출력 (mini c 소스파일 및 결과파일)

int main() {

	printf("***************** 어휘 분석을 시작합니다. *****************\n");
	
	struct tokenType temp;
	
	do {

		temp = scanner();
		printf("Token---> %s : (%d, %c)\n", temp.value.id, temp.number, temp.value.num);

	} while (temp.number != teof);	// 파일의 끝에 도달하면 종료한다.

	printf("***************** 어휘 분석을 종료합니다. *****************\n");


	return 0;
}

