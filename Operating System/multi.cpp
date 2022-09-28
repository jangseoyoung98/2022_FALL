// 운영체제 과제 1_2018380312 장서영
#include <iostream>
#include <string>
using namespace std;

void multi(int n);

int main(int argc, char* argv[]) {		// cmd 창에서 .exe와 함께 실행인자를 넘겨 주기 위해, int argc, char* argv를 매개변수로 둔다.

	string str_num = argv[1];			// 실행인자로 받은 데이터는 char형 포인터 배열(argv의 1번째 인덱스)에 저장되어 있다.
	int num = stoi(str_num);			// stoi()를 사용해, str_num의 문자열을 숫자로 변환한 후 num에 대입한다.
	multi(num);							// num을 인자로 넘겨 multi()를 호출한다. → 구구단 출력

	return 0;
}

void multi(int n) {	

	cout << endl;

	int cnt = n / 5;						// (5단씩 끊으려면) 총 몇 번 돌려야 하는지 구한다. 

	for (int row = 0; row <= cnt; row++) {  // 5단씩 끊어서 cnt번 줄바꿈 한다.
		int st = (5 * row) + 1;				// 각 행별 시작 숫자 : 1, 6, 11 .. 
		int fn = 5 * (row + 1);				// 각 행별 종료 숫자 : 5, 10, 15 ..

		for (int i = 1; i <= fn; i++) {		// 1*1 2*1 3*1 4*1 5*1 \n 2*2 3*2 4*2 5*2 .. 형태로 구구단을 출력한다. (i가 1씩 증가할 때, j는 st부터 fn까지 증가)
			for (int j = st; j <= fn; j++) {
				if (j > n || i > n)			// j와 i 둘 다 n을 넘어가면 안된다. (1*1 ~ n*n까지 출력)
					break;

				if (j < i) {				// j(곱함을 당하는 숫자)가 i(곱하는 숫자)보다 작은 경우 빈칸으로 둔다. ex) 6 * 7 (X)
					cout.width(10);			// width()와 std::left를 활용해, 왼쪽 정렬로 빈칸을 만든다.
					cout << std::left << " " << "\t";
					continue;
				}
				cout << "  " << j << " x " << i << " = " << j * i << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
}
