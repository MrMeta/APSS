// 20160617
#include <iostream>
#include <vector>
using namespace std;

vector<int> peer[10];
int count = 0;

void couple(vector<bool>& coupled, int start, int n);
int next(vector<bool>& coupled, int start);

int main(void) {
	int N = 0;

	cin >> N;

	while (N-- > 0) {
		int n = 0, m = 0;

		cin >> n >> m;

		for (int i = 0; i < n; i++) {
			peer[i].clear();
		}

		for (int i = 0; i < m; i++) {
			int a, b;

			cin >> a >> b;
			peer[a].push_back(b);
		}

		vector<bool> coupled(n);
		::count = 0;

		couple(coupled, 0, n);

		cout << ::count << endl;
	}
}

// [구현 방법]
// 0부터 순서대로 짝을 찾는 방법으로 함
// 친구정보를 양방향으로 성립하도록 저장하지 않고, 단방향으로만 저장한 후에
// 0부터 시작해서 매칭하도록 만듦
// 중복이 발생할 것을 대비하여 next()라는 함수를 만들어 작은 숫자로 돌아가는 경우를 막음
// 예를 들어, (0, 1), (4, 2), (3, 5)처럼 매칭되지는 못하도록 막음
// 왜냐하면, 저 조합은 0부터 순서대로 진행되므로 (0, 1), (3, 5), (4, 2)에서 나왔을 조합이기 때문

// [어려웠던 점]
// 1. 반복을 어떻게 처리해야 할 지에 대한 갑이 잘 안잡혀 구현이 복잡해짐
// 2. 적절한 자료루조를 선택하지 못해 구현이 복잡해짐
// 3. 매칭시키는 방법이 너무 복잡했던 것 같음

void couple(vector<bool>& coupled, int start, int n) {
	if (n == 0) {
		::count++;
		//cout << ::count << endl;
		return;
	}

	//cout << "start : " << start << endl;
	for (int i = start; i < coupled.size(); i++) {
		if (!coupled[i]) {
			for (int j = 0; j < peer[i].size(); j++) {
				int end = peer[i][j];
				if (!coupled[end]) {
					coupled[i] = true;
					coupled[end] = true;
					//cout << "(" << i << ", " << end << ")";
					//int next1 = next(coupled, i);
					//cout << "next :" << next1;
					//cout << "in couple(" << start << ", " << n << ")" << endl;
					couple(coupled, next(coupled, i), n - 2);
					coupled[i] = false;
					coupled[end] = false;
				}
			}
		}
	}


}

int next(vector<bool>& coupled, int start) {
	for (int i = start + 1; i < coupled.size(); i++) {
		//cout << i << endl;
		if (!coupled[i]) {
			return i;
		}
	}
}