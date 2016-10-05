// 20160618
#include <stdio.h>
#include <string.h>

char board[20][20];
int block[4][3][2] = {
	{ {0, 0}, {0, 1}, {1, 0} },		//┌
	{ {0, 0}, {0, -1}, {1, 0} },	// ┐
	{ {0, 0}, {0, -1}, {-1, 0} },	// ┘
	{ {0, 0}, {0, 1}, {-1, 0} }		//└
};

int h = 0, w = 0;

int cover(int x, int y, int count);

int* next(int x, int y);

int main(void) {
	int N = 0;
	scanf("%d", &N);

	while (N--) {
		scanf("%d %d", &h, &w);

		memset(board, ' ', sizeof(board));

		int whiteCount = 0;
		for (int i = 0; i < h; i++) {
			char str[20];
			scanf("%s", str);
			for (int j = 0; j < w; j++) {
				board[i][j] = str[j];
				if (board[i][j] == ',')
					whiteCount++;
			}
		}

		if (whiteCount % 3 != 0) {
			printf("0\n");
		}
		else {
			printf("%d\n", cover(0, 0, whiteCount/3));
		}
	}
}

int cover(int x, int y, int count) {
	int result = 0;
	for (int i = 0; i < 4; i++) {
		bool abled = true;
		for (int j = 0; j < 3; j++) {
			// 여기서 적당히 걸러져야 하는데 왜 안되는건지 잘..
			if ((x + block[i][j][1] < 0 || x + block[i][j][1] >= w)
				|| (y + block[i][j][0] < 0 || y + block[i][j][0] >= h)
				|| (board[y + block[i][j][0]][x + block[i][j][1]] != '.')) {
				abled = false;
			}else{
				board[x + block[i][j][0]][y + block[i][j][1]] = '#';
			}
		}
		if (!abled) {
			printf("(%d, %d)[%d]\n", x, y, i);
			continue;
		}
		
		//printf("(%d, %d)[%d]", x, y, i);

		if (count == 1)
			return 1;

		int* pos = next(x, y);

		result += cover(pos[0], pos[1], count - 1);

		for (int j = 0; j < 3; j++) {
			board[x + block[i][j][0]][y + block[i][j][1]] = '.';
		}
	}
	
	return result;
}

int* next(int x, int y) {
	int result[2] = { -1, -1 };
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (board[i][j] == '.') {
				result[0] = j;
				result[1] = i;
				return result;
			}
		}
	}

	return result;
}
