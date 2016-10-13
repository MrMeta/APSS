#include <stdio.h>
#define min(x, y)  (x)<(y)?(x):(y)
#define INF 987654321

bool isAllTwelve(int clockes[]);
void pressSwitch(int clockes[], int switchNum, int num);
int solve(int clockes[], int n);

int switches[10][5] = {
	{0, 1, 2, -1, -1},
	{3, 7, 9, 11, -1},
	{4, 10, 14, 15, -1},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15, -1},
	{3, 14, 15, -1, -1},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13}
};

int main(){
	int C = 0;
	scanf("%d", &C);

	while(C-->0){
		int clockes[16];
		for(int i=0; i<16; i++) scanf("%d", &clockes[i]);

		int solution = solve(clockes, 0);

		if(solution == INF) printf("-1\n");
		else printf("%d\n", solution);
	}

	return 0;
}

bool isAllTwelve(int clockes[]){
	bool result = true;
	for(int i=0; i<16; i++){
		if(clockes[i] != 12){
			result = false;
			break;
		}
	}

	return result;
}

void pressSwitch(int clockes[], int switchNum, int num){
	if(num < 0) num = 4 + num;

	for(int i=0; i<num; i++){
		for(int j=0; j<5; j++){
			int clockNum = switches[switchNum][j];
			if(clockNum == -1) break;
			
			clockes[clockNum] += 3;
			if(clockes[clockNum] == 15) clockes[clockNum] = 3;
		}
	}
}

int solve(int clockes[], int n){
	if(isAllTwelve(clockes)) return 0;
	if(n == 10) return INF;
	
	int result = INF;
	for(int i=0; i<4; i++){
		pressSwitch(clockes, n, i);
		result = min(result, i+solve(clockes, n+1));
		pressSwitch(clockes, n, -i);
	}

	return result;
}
