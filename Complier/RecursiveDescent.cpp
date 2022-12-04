// [컴파일러 prog 3] Recursive-descent Parser_완료
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAX 100

string input;		// 입력 스트링
string leftParse;	// 좌파스
char nextSym;		// 다음 입력 심볼

bool pS(char nextSym);
void pA(char nextSym);
char getNextSym(string* input);

int main() {

	cout << "Enter a sentence: ";
	cin >> input;
	
	nextSym = getNextSym(&input);
	
	bool is_accepted = pS(nextSym);
	if (is_accepted && input == "$") {
		cout << "Accept!!\n" << "LeftParse: " << leftParse << endl;
	}
	else {
		cout << "error!!\n";
	}
	return 0;
}

bool pS(char nextSym) {	// 논터미널 S -> 프로시저 pS
	if (nextSym == 'a') {
		leftParse.append("1");
		nextSym = getNextSym(&input);
		pS(nextSym);
	}
	else if (nextSym == 'b') {
		leftParse.append("2");
		nextSym = getNextSym(&input);
		pA(nextSym);
	}
	else
		return false;

	return true;
}

void pA(char nextSym) { // 논터미널 A -> 프로시저 pA
	if (nextSym == 'd') {
		leftParse.append("3");
		nextSym = getNextSym(&input);
	}
	else if (nextSym == 'c') {
		nextSym = getNextSym(&input);
		if (nextSym == 'c') {
			leftParse.append("4");
			nextSym = getNextSym(&input);
			pA(nextSym);
		}
	}
	/*
	else
		return '!';	// error

	return nextSym;
	*/
}

char getNextSym(string* input) { // 인풋 스트링에서 다음 입력 심볼을 반환한다. (이미 본 건 지운다.)

	string tempInput = *input;

	if(*input != "$")
		input->erase(0, 1);

	char temp = tempInput[0];

	return temp;
}
