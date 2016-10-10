#include <iostream>
#include <string>
#include <vector>

using namespace std;

int coordX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int coordY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

char board[5][5];
bool hasWord(int x, int y, string word);

int main(void){
	int C = 0;
	cin >> C;

	while(C-->0){
		for(int i=0; i<5; i++){
			cin >> board[i];
		}

		int N = 0;
		cin >> N;
		
		vector<string> words;
		for(int i=0; i<N; i++){
			string word;
			cin >> word;
			words.push_back(word);
		}

		for(int i=0; i<N; i++){
			bool result = false;
			for(int y=0; y<5; y++){
				for(int x=0; x<5; x++){
					result |= hasWord(y, x, words[i]);
				}
			}

			cout << words[i] << " ";
			if(result) cout << "YES";
			else cout << "NO";
			cout << endl;
		}
	}
}

bool hasWord(int x, int y, string word){
	if(x<0||x>4||y<0||y>4) return false;
	if(word[0]!=board[y][x]) return false;

	if(word.length()==1) return true;
	
	bool result = false;
	for(int i=0; i<8; i++){
		result |= hasWord(x+coordX[i], y+coordY[i], word.substr(1));
	}
	
	return result;
}
