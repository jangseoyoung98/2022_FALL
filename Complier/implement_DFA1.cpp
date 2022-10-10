// 예제 3.14(교재 86p)
// ★ 생성자 함수의 디폴트 값을 통해서 클래스를 생성할 때는 ()를 붙이면 안 된다!

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct State {	// 각 상태를 노드(구조체)로 표현한다.
public:	
	char stateName = NULL;
	struct State* symBy0 = NULL;	// 입력 심볼이 0일 때
	struct State* symBy1 = NULL;	// 입력 심볼이 1일 때
};

class TransitionTable {	// transition table을 클래스로 표현한다.
public:
	struct State s1, s2, s3;

	TransitionTable() {	
		// Q = {p, q, r}
		s1.stateName = 'p'; // s1을 시작상태로 간주한다.
		s2.stateName = 'q';
		s3.stateName = 'r';

		// transition function
		s1.symBy0 = &s2; // p,0 → q
		s1.symBy1 = &s1; // p,1 → p
		s2.symBy0 = &s3; // q,0 → r
		s2.symBy1 = &s1; // q,1 → p
		s3.symBy0 = &s3; // r,0 → r
		s3.symBy1 = &s3; // r,1 → r
	}

	struct State* transFunc(struct State currentState, char nextSymbol) {
		if (nextSymbol == '0')
			return currentState.symBy0;
		else
			return currentState.symBy1;
	}
};


int main() {

	TransitionTable table;	// transition table을 생성함
	struct State* currentState = &(table.s1);  // 현재 상태 (시작 상태 s1으로 초기화)
	string str;	// 사용자로부터 입력 받을 스트링

	cout << "스트링을 입력하세요.(0 또는 1만 가능) : ";
	cin >> str;
	size_t len = str.length(); // size_t = unsigned int


	//
	for(int i = 0; i <= len; i++)
	{
		currentState = table.transFunc(*(currentState), str[i]);

	}
	//


	if (currentState->stateName == 'r')
		cout << "input recognized" << endl;
	else
		cout << "input not recognized" << endl;

	return 0;
}
