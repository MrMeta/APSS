#include <iostream>

using namespace std;

bool areFriends[10][10];
bool coupled[10] = {false, };

bool isAllMatched(int n);
int match(int n);

int main(void){
	int C = 0;
	cin >> C;

	while(C-->0){
		int n = 0, m = 0;
		cin >> n >> m;

		for(int i=0; i<n; i++){
			for(int j=i+1; j<n; j++){
				areFriends[i][j] = false;
			}
		}

		for(int i=0; i<m; i++){
			int from = 0, to = 0;
			cin >> from >> to;

			if(from > to) areFriends[to][from] = true;
			else areFriends[from][to] = true;
		}

		cout << match(n) << endl;
	}
}

bool isAllMatched(int n){
	bool result = true;
	for(int i=0; i<n; i++){
		result &= coupled[i];
	}
	
	return result;
}

int match(int n){
	if(isAllMatched(n)){
		return 1;
	}

	int result = 0;

	int from = -1;
	for(int i=0; i<n; i++){
		if(!coupled[i]){
			from = i;
			break;
		}
	}

	for(int to=from+1; to<n; to++){
		if(areFriends[from][to] && !coupled[to]){
			coupled[from] = true;
			coupled[to] = true;
			result += match(n);
			coupled[from] = false;
			coupled[to] = false;
		}
	}

	return result;
}
