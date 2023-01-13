#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

#define NO_RULES 7	// ������Ģ ����
#define GOAL_RULE 7 // accpet ������Ģ
#define PS_SIZE 200 // �Ľ� ���� ������
#define ID_LEN 100	// ��ǲ ������ �ִ� ����

// (�Ľ����̺�)
#define NO_SYMBOLS 9 // �����ɺ� + 1
#define NO_STATES 12 // ����

string input;	// ����� �Է�
int len = 0;
int pos = 0;

/* �� ĳ �� **************************************************************/
struct tokenType {
	int number;		// token number
	union {
		char id[10];
		int num;
	} value;		// token value (�ϴ� ��ū ����� �����ϰ���. �ٸ� ������ ���� �ñ���,,�ФФФ�)
};
struct tokenType scanner() {
	struct tokenType token;
	token.number = -1;

	do {
		// while (isspace(input[pos++]));
		switch (input[pos++]) {	// a, +, *, (, ), $, E, T, F
		case 'a': token.number = 0;		break;
		case '+': token.number = 1;		break;
		case '*': token.number = 2;		break;
		case '(': token.number = 3;		break;
		case ')': token.number = 4;		break;
		case '$': token.number = 5;		break;
		case 'E': token.number = 6;		break;
		case 'T': token.number = 7;		break;
		case 'F': token.number = 8;		break;

		default: {
			//printf("Lexical Error!\n");
			break;
		}
		} // switch end

	} while (token.number == -1);

	return token; // ��ū (��ū �ѹ�+���) ����
}
/***************************************************************/

int parsingTable[NO_STATES][NO_SYMBOLS + 1] = { //�� �̹� 9���ε� +1�� �� �ϴ� ��..?
	/* term + Nonterm # :  a, +, *, (, ), $, E, T, F */
	/* term + Nonterm # :  0  1  2  3  4  5  6  7  8 */
	/* state 0 */		{  5, 0, 0, 4, 0, 0, 1, 2, 3 },
	/* state 1 */		{  0, 6, 0, 0, 0,-7, 0, 0, 0 },
	/* state 2 */		{  0,-2, 7, 0,-2,-2, 0, 0, 0 },
	/* state 3 */		{  0,-4,-4, 0,-4,-4, 0, 0, 0 },
	/* state 4 */		{  5, 0, 0, 4, 0, 0, 8, 2, 3 },
	/* state 5 */		{  0,-6,-6, 0,-6,-6, 0, 0, 0 },
	/* state 6 */		{  5, 0, 0, 4, 0, 0, 0, 9, 3 },
	/* state 7 */		{  5, 0, 0, 4, 0, 0, 0, 0,10 },
	/* state 8 */		{  0, 6, 0, 0,11, 0, 0, 0, 0 },
	/* state 9 */		{  0,-1, 7, 0,-1,-1, 0, 0, 0 },
	/* state 10 */		{  0,-3,-3, 0,-3,-3, 0, 0, 0 },
	/* state 11 */		{  0,-5,-5, 0,-5,-5, 0, 0, 0 },

	// �� 7�� ������Ģ���� reduce �� �� accept��� �����ϰڴ�. �� -7
	// entry�� ���� ���� (shift�� ���, reduce�� ����, error�� 0, accept�� -7�� ǥ��)
};

// ������Ģ lhs�� �ִ� nonterminal�� ��ȣ�� ���� �ִ� �迭
int leftSymbol[NO_RULES + 1] = {
	// [0]�� �����ϰڴ�. �ε��� 1���� 7����
	0, 6, 6, 7, 7, 8, 8, 5
};
// �� ������Ģ rhs�� ����
int rightLength[NO_RULES + 1] = {
	// [0]�� �����ϰڴ�. �ε��� 1���� 7����
	0, 3, 1, 3, 1, 3, 1, 1
};
// -> left, right�� �̿��� reduce ��!!

int semantic[PS_SIZE] = { 0, };	// ���Ľ� ���� �迭
int semP = 0;

int errcnt = 0;
int sp;						// ���� ������ - ���� shift, reduce �� ��ġ ����
int stateStack[PS_SIZE];	// ���¹�ȣ ����
int symbolStack[PS_SIZE];	// �ɺ� ����

void parser()
{
	int entry, ruleNumber, lhs;
	int currentState;	// �Ľ� ���̺��� '��' (����)
	struct tokenType token;

	// 1. �ʱ���� (����)
	sp = 0; stateStack[sp] = 0;

	token = scanner();

	while (1) {
		currentState = stateStack[sp];
		entry = parsingTable[currentState][token.number];	// �� ��ū �ѹ� ���� (�Ľ����̺� ���� ���߱�)
		// cout << "entry : " << entry << endl;
		if (entry > 0) {	/* SHIFT ACTION */
			sp++;
			if (sp > PS_SIZE) {	// (���� ó��) ���� �����÷ο�
				printf("critical compiler error: parsing stack overflow");
				return;
			}
			symbolStack[sp] = token.number;	// �ɺ� ���� push
			stateStack[sp] = entry;			// ���� ���� push

			token = scanner(); // ���� �Է� �ɹ��� �̵�
		}

		else if (entry < 0) {	/* REDUCE ACTION */
			ruleNumber = -entry;
			if (ruleNumber == GOAL_RULE) {	/* ACCEPT ACTION */
				printf("Accept!\n");
				return;
			}
			semantic[semP++] = ruleNumber;
			sp = sp - rightLength[ruleNumber];
			lhs = leftSymbol[ruleNumber];
			currentState = parsingTable[stateStack[sp]][lhs];
			sp++;
			symbolStack[sp] = lhs;
			stateStack[sp] = currentState;

		}
		else {
			printf("Error: Wrong sentence\n");
			return;
		}
	}

}

int main() {

	cout << "Input string: ";
	cin >> input;
	len = input.length();

	parser();
	printf("Right Parse: ");
	for (int i = 0; i < semP; i++) {
		printf("%d ", semantic[i]);
	}


	return 0;
}

