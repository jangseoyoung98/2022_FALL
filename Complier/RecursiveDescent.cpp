// 완료
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAX 100

string input; // 입력 스트링
string leftParse; // 좌파스
char nextSym;

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

bool pS(char nextSym) {
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

void pA(char nextSym) {
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

char getNextSym(string* input) {

	string tempInput = *input;

	if(*input != "$")
		input->erase(0, 1);

	char temp = tempInput[0];

	return temp;
}