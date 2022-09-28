// �ü�� ���� 1_2018380312 �弭��
#include <iostream>
#include <string>
using namespace std;

void multi(int n);

int main(int argc, char* argv[]) {		// cmd â���� .exe�� �Բ� �������ڸ� �Ѱ� �ֱ� ����, int argc, char* argv�� �Ű������� �д�.

	string str_num = argv[1];			// �������ڷ� ���� �����ʹ� char�� ������ �迭(argv�� 1��° �ε���)�� ����Ǿ� �ִ�.
	int num = stoi(str_num);			// stoi()�� �����, str_num�� ���ڿ��� ���ڷ� ��ȯ�� �� num�� �����Ѵ�.
	multi(num);							// num�� ���ڷ� �Ѱ� multi()�� ȣ���Ѵ�. �� ������ ���

	return 0;
}

void multi(int n) {	

	cout << endl;

	int cnt = n / 5;						// (5�ܾ� ��������) �� �� �� ������ �ϴ��� ���Ѵ�. 

	for (int row = 0; row <= cnt; row++) {  // 5�ܾ� ��� cnt�� �ٹٲ� �Ѵ�.
		int st = (5 * row) + 1;				// �� �ະ ���� ���� : 1, 6, 11 .. 
		int fn = 5 * (row + 1);				// �� �ະ ���� ���� : 5, 10, 15 ..

		for (int i = 1; i <= fn; i++) {		// 1*1 2*1 3*1 4*1 5*1 \n 2*2 3*2 4*2 5*2 .. ���·� �������� ����Ѵ�. (i�� 1�� ������ ��, j�� st���� fn���� ����)
			for (int j = st; j <= fn; j++) {
				if (j > n || i > n)			// j�� i �� �� n�� �Ѿ�� �ȵȴ�. (1*1 ~ n*n���� ���)
					break;

				if (j < i) {				// j(������ ���ϴ� ����)�� i(���ϴ� ����)���� ���� ��� ��ĭ���� �д�. ex) 6 * 7 (X)
					cout.width(10);			// width()�� std::left�� Ȱ����, ���� ���ķ� ��ĭ�� �����.
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
