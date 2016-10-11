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

// [���� ���]
// 0���� ������� ¦�� ã�� ������� ��
// ģ�������� ��������� �����ϵ��� �������� �ʰ�, �ܹ������θ� ������ �Ŀ�
// 0���� �����ؼ� ��Ī�ϵ��� ����
// �ߺ��� �߻��� ���� ����Ͽ� next()��� �Լ��� ����� ���� ���ڷ� ���ư��� ��츦 ����
// ���� ���, (0, 1), (4, 2), (3, 5)ó�� ��Ī������ ���ϵ��� ����
// �ֳ��ϸ�, �� ������ 0���� ������� ����ǹǷ� (0, 1), (3, 5), (4, 2)���� ������ �����̱� ����

// [������� ��]
// 1. �ݺ��� ��� ó���ؾ� �� ���� ���� ���� �� ������ ������ ��������
// 2. ������ �ڷ������ �������� ���� ������ ��������
// 3. ��Ī��Ű�� ����� �ʹ� �����ߴ� �� ����

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