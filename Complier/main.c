#include "scanner.c"

FILE* srcFile, * rstFile; // ��ĳ���� �Է� �� ��� (mini c �ҽ����� �� �������)

int main() {

	printf("***************** ���� �м��� �����մϴ�. *****************\n");
	
	struct tokenType temp;
	
	do {

		temp = scanner();
		printf("Token---> %s : (%d, %c)\n", temp.value.id, temp.number, temp.value.num);

	} while (temp.number != teof);	// ������ ���� �����ϸ� �����Ѵ�.

	printf("***************** ���� �м��� �����մϴ�. *****************\n");


	return 0;
}

