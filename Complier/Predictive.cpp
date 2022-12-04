// [�����Ϸ� prog 3] Predictive Parser_�Ϸ�
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

// �Ľ� ���̺� (���� "-1")
char pTable[2][5][MAX] = {
	// 1st [] : ���͹̳� ����
	// 2nd [] : �Է� �ɺ� ����

		   /*   a     b     c     d    $ */
	/* S */ {"aS", "bA", "-1", "-1", "-1"},
	/* A */ {"-1", "-1", "ccA", "d", "-1" }

};

// ����
class Stack {
private:
	char array[MAX] = "\0";	// ����
	int top = 0;			// ������ top �ε���

public:
	Stack() { // ������ : ���ÿ� $S(���� �ɺ�)�� �ְ� �����Ѵ�.
		array[top] = '$';
		top++;
		array[top] = 'S';
	}
	char seek() { // ������ top symbol�� Ȯ���Ѵ�.
		return array[top];
	}
	void push(string handle) { // expand 
		top++;
		int len = handle.length();

		// ������ �������� top�̹Ƿ�, ����� �ִ´�.		
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

	Stack stack;		// ������ �����Ѵ�.
	string leftParse;	// ���Ľ�
	string input;		// ��ǲ ��Ʈ��
	int ip = 0;			// ���� ���� �ִ� �Է� �ɺ�(�ε���)

	int tR, tC;			// �Ľ� ���̺��� ��(S:0, A:1) �� ��(a:0, b:1, c:2, d:3, $:4) -> ������ ������� ��ȣ�� �ο��Ѵ�.

	cout << "Enter a sentence: ";
	cin >> input;	// �Է� ��, ���� $ �߰����� �����Ѵ�.

	char stackSym;
	bool is_not_error = true;

	do {
		stackSym = stack.seek();
		// �͹̳��� ��� ($ ����)
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
		// ���͹̳��� ���
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
					return 0; // ���α׷� ����
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
					return 0; // ���α׷� ����
				}
			}
			// �Ľ� ���̺��� �ش� ���ڿ� ã�Ƽ� push�� ������.
			// �� ��ȣ�� ���缭 ���Ľ� ����
		}

	} while (stack.seek() != '$');
	
	if (is_not_error) // accept
		cout << "Accept!!\n" << "LeftParse: " << leftParse << endl;
	else // error
		cout << "error!!\n";

	return 0;
}