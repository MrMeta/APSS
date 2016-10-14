#include <iostream>
#include <string>

using namespace std;

string turnover(string picture);

int main(){
	int C = 0;
	cin >> C;

	while(C-->0){
		string picture;	

		cin >> picture;
		
		cout << turnover(picture) << endl;
	}

	return 0;
}

string turnover(string picture){
	string result;
	result += picture[0];
	if(result == "w" || result == "b") return result;
	
	string partition[4];
	int start = 1;
	for(int i=0; i<4; i++){
		partition[i] = turnover(picture.substr(start));
		start += partition[i].length();
	}
	
	result += partition[2];
	result += partition[3];
	result += partition[0];
	result += partition[1];

	return result;
}
