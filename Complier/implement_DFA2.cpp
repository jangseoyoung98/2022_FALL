// 연습문제 3.7 (5)번 (교재 124p)
#include <iostream>
#include <string>
using namespace std;

#define MAX 3 // 하나의 상태수 [ ] 안에는 최대 3개까지 가질 수 있다.
enum statVal { q0, q1, q2 };

typedef struct Node { 
public:
	enum statVal stateName[MAX];
	struct Node* symByA = NULL;
	struct Node* symByB = NULL;
} State; 

class TransitionTable2 {

public:
	State s1, s2, s3, s4, s5;	
	
	/*
	Q' -> 2^3-1(7)개의 상태수 중에서 '도달할 수 있는 상태'만을 취함
	s1 = [q0] = A
	s2 = [q1,q2] = B
	s3 = [q0,q1,q2] = C 
	s4 = [q1] = D
	s5 = [q0,q1] = E
	*/

	TransitionTable2() {

		// Q' = {A, B, C, D, E}
		s1.stateName[0] = q0; // s1을 시작상태로 간주한다.

		s2.stateName[0] = q1;
		s2.stateName[1] = q2;

		s3.stateName[0] = q0;
		s3.stateName[1] = q1;
		s3.stateName[2] = q2;

		s4.stateName[0] = q1;

		s5.stateName[0] = q0;
		s5.stateName[1] = q1;


		s1.symByA = &s2; // A,a → B
		s1.symByB = &s1; // A,b → A
		s2.symByA = &s3; // B, a → C
		s2.symByB = &s4; // B, b → D
		s3.symByA = &s3; // C, a → C
		s3.symByB = &s5; // C, b → E
		s4.symByA = &s5; // D, a → E
		s4.symByB = NULL; // D, b → 공집합
		s5.symByA = &s3; // E, a → C
		s5.symByB = &s1; // E, b → A
	}

	State* transFunc2(State* currentState, char nextSymbol) {
		if (nextSymbol == 'a')
			return currentState->symByA;
		else
			return currentState->symByB;
	}

};

int main() {

	TransitionTable2 dfa2;
	State* currentState = &(dfa2.s1); // 시작 상태
	string str;

	cout << "스트링을 입력하세요. (a 또는 b만 가능) : ";
	cin >> str;
	size_t len = str.length();

	for (int i = 0; i < len; i++) {
		currentState = dfa2.transFunc2(currentState, str[i]);
	}

	// q2를 가지는지 확인
	for (int i = 0; i < MAX; i++) {
		if (currentState->stateName[i] == q2) {
			cout << "input recognized\n";
			return 0;
		}
		
	}

	cout << "input not recognized\n";

	return 0;
}
