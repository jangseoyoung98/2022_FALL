// [컴파일러 prog 3] Predictive Parser_완료
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#define MAX 20

/*
* Vn : S, A
* Vt : a, b, c, d
* 
* 1. S -> aS
* 2. S -> bA
* 3. A -> d
* 4. A -> ccA
*/

// 파싱 테이블 (에러 "-1")
char pTable[2][5][MAX] = {
	// 1st [] : 논터미널 접근
	// 2nd [] : 입력 심볼 접근

		   /*   a     b     c     d    $ */
	/* S */ {"aS", "bA", "-1", "-1", "-1"},
	/* A */ {"-1", "-1", "ccA", "d", "-1" }

};

// 스택
class Stack {
private:
	char array[MAX] = "\0";	// 스택
	int top = 0;			// 스택의 top 인덱스

public:
	Stack() { // 생성자 : 스택에 $S(시작 심볼)을 넣고 시작한다.
		array[top] = '$';
		top++;
		array[top] = 'S';
	}
	char seek() { // 스택의 top symbol을 확인한다.
		return array[top];
	}
	void push(string handle) { // expand 
		top++;
		int len = handle.length();

		// 스택의 오른쪽이 top이므로, 뒤집어서 넣는다.		
		for (int i = len - 1; i >= 0; i--) {
			array[top] = handle[i];
			top++;
		}
		top--;
	}
	void pop() {
		array[top] = '\0';
		top--;
	}
};

int main() {

	Stack stack;		// 스택을 생성한다.
	string leftParse;	// 좌파스
	string input;		// 인풋 스트링
	int ip = 0;			// 현재 보고 있는 입력 심볼(인덱스)

	int tR, tC;			// 파싱 테이블의 행(S:0, A:1) 과 열(a:0, b:1, c:2, d:3, $:4) -> 각각에 순서대로 번호를 부여한다.

	cout << "Enter a sentence: ";
	cin >> input;	// 입력 시, 끝에 $ 추가함을 가정한다.

	char stackSym;
	bool is_not_error = true;

	do {
		stackSym = stack.seek();
		// 터미널인 경우 ($ 포함)
		if (stackSym == 'a' || stackSym == 'b' || stackSym == 'c' || stackSym == 'd' || stackSym == '$') {
			if (stackSym == input[ip]) {
				stack.pop();
				ip++;
			}
			else {
				is_not_error = false;
				break;
			}
		}
		// 논터미널인 경우
		else {
			if (stackSym == 'S') {
				switch (input[ip]) {
				case 'a':
					stack.pop();
					stack.push(pTable[0][0]); // "aS"
					leftParse.append("1");
					break;
				case 'b':
					stack.pop();
					stack.push(pTable[0][1]); // "bA"
					leftParse.append("2");
					break;
				default:
					cout << "error!!\n";
					return 0; // 프로그램 종료
				}
			}
			else if (stackSym == 'A') {
				switch (input[ip]) {
				case 'c':
					stack.pop();
					stack.push(pTable[1][2]); // "ccA"
					leftParse.append("4");
					break;
				case 'd':
					stack.pop();
					stack.push(pTable[1][3]); // "d"
					leftParse.append("3");
					break;
				default:
					cout << "error!!\n";
					return 0; // 프로그램 종료
				}
			}
			// 파싱 테이블에서 해당 문자열 찾아서 push로 보낸다.
			// 그 번호에 맞춰서 좌파스 생성
		}

	} while (stack.seek() != '$');
	
	if (is_not_error) // accept
		cout << "Accept!!\n" << "LeftParse: " << leftParse << endl;
	else // error
		cout << "error!!\n";

	return 0;
}