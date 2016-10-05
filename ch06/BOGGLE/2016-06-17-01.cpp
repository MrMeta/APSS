// 20160615
#include <iostream>
#include <string>
#include <vector>
using namespace std;

char board[5][5];
vector<string> list;

int xdelta[8] = { -1,  0,  1, -1, 1, -1, 0, 1 };
int ydelta[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };

bool search(string word, int at, int currentPos[]);
bool isValid(int x, int y);

int main(void) {
	int C;

	cin >> C;
	while (C-- > 0) {
		for (int i = 0; i < 5; i++) {
			string input;
			cin >> input;
			for (int j = 0; j < 5; j++) {
				board[i][j] = input[j];
			}
		}

		int N = 0;
		cin >> N;

		list.clear();

		for (int i = 0; i < N; i++) {
			string input;
			cin >> input;
			list.push_back(input);
		}
		
		for (int i = 0; i < N; i++) {
			cout << list[i] << " ";
			string output = "NO";
			for(int y = 0; y < 5; y++){
				for (int x = 0; x < 5; x++) {
					if (board[y][x] == list[i][0]) {
						int pos[2] = { x, y };
						//cout << "[" << y << "][" << x << ") <0>" << endl;
						bool result = search(list[i], 1, pos);
						if (result) {
							output = "YES";
							goto outside;
						}
					}
				}
			}

			outside:
			cout << output << endl;
		}
	}
}

// num 
bool search(string word, int at, int currentPos[]) {
	bool result = false;
	for (int i = 0; i < 8; i++) {
		int x = currentPos[0] + xdelta[i];
		int y = currentPos[1] + ydelta[i];
		if (!isValid(x, y))
			continue;

		int nextPos[2] = { x, y };
		//cout << "[" << y << "][" << x << "] <" << at << ">" << endl;
		if (board[y][x] == word[at]) {
			// at에 해당하는 글자를 찾았고 그게 단어의 마지막이었다면 true 리턴
			// 즉 마지막 단어를 찾았는지의 여부가 중요하다!
			if (at == word.length() - 1) {
				result = true;
			}
			else {
				result = search(word, at + 1, nextPos);
			}

			if (result)
				break;
		}

	}

	return result;
}

bool isValid(int x, int y) {
	if (x < 0 || x > 5) {
		return false;
	}

	if (y < 0 || y > 5) {
		return false;
	}

	return true;
}