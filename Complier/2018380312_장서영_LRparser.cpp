#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

#define NO_RULES 7	// 생성규칙 갯수
#define GOAL_RULE 7 // accpet 생성규칙
#define PS_SIZE 200 // 파싱 스택 사이즈
#define ID_LEN 100	// 인풋 테이프 최대 길이

// (파싱테이블)
#define NO_SYMBOLS 9 // 문법심볼 + 1
#define NO_STATES 12 // 상태

string input;	// 사용자 입력
int len = 0;
int pos = 0;

/* 스 캐 너 **************************************************************/
struct tokenType {
	int number;		// token number
	union {
		char id[10];
		int num;
	} value;		// token value (일단 토큰 밸류는 무시하겠음. 다른 에러가 지금 시급함,,ㅠㅠㅠㅠ)
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

	return token; // 토큰 (토큰 넘버+밸류) 리턴
}
/***************************************************************/

int parsingTable[NO_STATES][NO_SYMBOLS + 1] = { //★ 이미 9개인데 +1은 왜 하는 거..?
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

	// ※ 7번 생성규칙으로 reduce 될 때 accept라고 가정하겠다. → -7
	// entry는 다음 상태 (shift는 양수, reduce는 음수, error은 0, accept는 -7로 표현)
};

// 생성규칙 lhs에 있는 nonterminal의 번호를 갖고 있는 배열
int leftSymbol[NO_RULES + 1] = {
	// [0]은 무시하겠다. 인덱스 1부터 7까지
	0, 6, 6, 7, 7, 8, 8, 5
};
// 각 생성규칙 rhs의 길이
int rightLength[NO_RULES + 1] = {
	// [0]은 무시하겠다. 인덱스 1부터 7까지
	0, 3, 1, 3, 1, 3, 1, 1
};
// -> left, right를 이용해 reduce 함!!

int semantic[PS_SIZE] = { 0, };	// 우파스 보관 배열
int semP = 0;

int errcnt = 0;
int sp;						// 스택 포인터 - 스택 shift, reduce 시 위치 지정
int stateStack[PS_SIZE];	// 상태번호 스택
int symbolStack[PS_SIZE];	// 심볼 스택

void parser()
{
	int entry, ruleNumber, lhs;
	int currentState;	// 파싱 테이블의 '행' (상태)
	struct tokenType token;

	// 1. 초기상태 (시작)
	sp = 0; stateStack[sp] = 0;

	token = scanner();

	while (1) {
		currentState = stateStack[sp];
		entry = parsingTable[currentState][token.number];	// ★ 토큰 넘버 수정 (파싱테이블 열에 맞추기)
		// cout << "entry : " << entry << endl;
		if (entry > 0) {	/* SHIFT ACTION */
			sp++;
			if (sp > PS_SIZE) {	// (에러 처리) 스택 오버플로우
				printf("critical compiler error: parsing stack overflow");
				return;
			}
			symbolStack[sp] = token.number;	// 심볼 스택 push
			stateStack[sp] = entry;			// 상태 스택 push

			token = scanner(); // 다음 입력 심벌로 이동
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

