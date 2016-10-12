#include <stdio.h>

// (y, x)
int block[4][3][2] = {
	{{0, 0}, {1, 0}, {1, 1}},
	{{0, 0}, {0, 1}, {1, 0}},
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {1, -1}, {1, 0}}
};

char buffer[25];
char board[20][20];
int H=0, W=0;

int cover(int x, int y, int white);
int main(void){
	int C=0;
	scanf("%d", &C);

	while(C-->0){
		scanf("%d %d", &H, &W);
		
		int white = 0;
		for(int i=0; i<H; i++){
			scanf("%s", buffer);
			for(int j=0; j<W; j++){
				board[i][j] = buffer[j];
				if(buffer[j]=='.') white++;
			}
		}
		
		printf("%d\n", cover(0, 0, white));
	}

	return 0;
}

int cover(int x, int y, int white){
	if(white % 3 != 0) return 0;

	int result = 0;
	int pos = y * W + x;
	while(pos < W * H){
		pos++;
		x = pos % W;
		y = pos / W;

		if(board[y][x] == '.') break;
	}

	// 아래 경우가 유효한 방법이었지만 return 0을 함
	if(x == W && y == H) return 0;

	for(int i=0; i<4; i++){
		if(y + block[i][1][0] >= H || x + block[i][1][1] >= W || y + block[i][2][0] >= H || x + block[i][2][1] >= W) continue;
		if(board[y+block[i][1][0]][x+block[i][1][1]] != '.' || board[y+block[i][2][0]][x+block[i][2][1]] != '.') continue;

		// block의 기준점 처리 안했음
		// board[y][x] = '#';
		board[y+block[i][1][0]][x+block[i][1][1]] = '#';
		board[y+block[i][2][0]][x+block[i][2][1]] = '#';
		if(white != 3) result += cover(x, y, white-3);
		else result += 1;
		// block의 기준점 처리 안했음
		// board[y][x] = '.';
		board[y+block[i][1][0]][x+block[i][1][1]] = '.';
		board[y+block[i][2][0]][x+block[i][2][1]] = '.';
	}

	return result;
}
