// 20160620
// 앞으로는 정해진 시간(우선은 3시간)동안 스톱워치를 한 후 그동안 풀지 못하면 답을 보는 것으로 하자.
// 물론 화장실 등등 개인 업무도 이 시간에 포함
#include <stdio.h>
#include <string.h>

#define X 1
#define Y 0

typedef struct {
	int x;
	int y;
}point;

char board[20][20];
int block[4][3][2] = {
	{ {0, 0}, {0, 1}, {1, 0} },		//┌
	{ {0, 0}, {0, -1}, {1, 0} },	// ┐
	{ {0, 0}, {0, -1}, {-1, 0} },	// ┘
	{ {0, 0}, {0, 1}, {-1, 0} }		//└
};

int h = 0, w = 0;

int cover(int y, int x, int count);
point next(int y, int x);

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
				if (board[i][j] == '.')
					whiteCount++;
			}
		}

		if (whiteCount % 3 != 0) {
			printf("0\n");
		}
		else {
			point pos = next(0, 0);
			printf("%d\n", whiteCount / 3);
			printf("%d\n", cover(pos.y, pos.x, whiteCount/3));
		}
	}
}

// 계속 무한루프를 돌아 실패함
int cover(int y, int x, int count) {
	int result = 0;
	
	printf("current [%d][%d]\n", y, x);

	if (y == -1 && x == -1)
		return 0;

	if (count == 0)
		return 1;

	for (int i = 0; i < 4; i++) {
		bool abled = true;
		int j = 0;
		for (j = 0; j < 3; j++) {
			// 여기서 적당히 걸러져야 하는데 왜 안되는건지 잘..
			// 음.. 처음게 #라서 전부 abled = false가 된 후에 다음 좌표로 넘어가질 못하네
			if ((x + block[i][j][X] < 0 || x + block[i][j][X] >= w)
				|| (y + block[i][j][Y] < 0 || y + block[i][j][Y] >= h)
				|| (board[y + block[i][j][Y]][x + block[i][j][X]] != '.')) {
				printf("[%d][%d]<%d> -> [%d][%d]\n", y, x, i, y + block[i][j][y], x + block[i][j][X]);
				abled = false;
				break;
			}else{
				board[y + block[i][j][Y]][x + block[i][j][X]] = '#';
			}
		}

		if (!abled) {
			for (; j >= 0; j--) {
				board[y + block[i][j][Y]][x + block[i][j][X]] = '.';
			}
			continue;
		}
		
		point pos = next(y, x);

		printf("[%d][%d]<%d>\n", y, x, i);

		printf("next [%d][%d]\n", pos.y, pos.x);
		result += cover(pos.y, pos.x, count - 1);

		for (int j = 0; j < 3; j++) {
			board[x + block[i][j][0]][y + block[i][j][1]] = '.';
		}
	}
	point pos = next(y, x);

	printf("next [%d][%d]\n", pos.y, pos.x);
	result += cover(pos.y, pos.x, count);
	
	return result;
}

// 처음에는 int*를 반환했지만 배열처럼 작동하지 않아서 구조체를 사용.. 왜지..???
point next(int y, int x) {
	point result = { -1, -1 };
	int n = w * y + x;
	int i = -1;
	int j = -1;
	while (n < h * w) {
		i = (int)(n / w);
		j = n % w;

		if (board[i][j] == '.') {
			result.y = i;
			result.x = j;
			return result;
		}
		n++;
	}
	//for (int i = 0; i < h; i++) {
	//	for (int j = 0; j < w; j++) {
	//		if (board[i][j] == '.') {
	//			result.y = i;
	//			result.x = j;
	//			//result[Y] = i;
	//			//result[X] = j;
	//			//printf("[%d][%d]\n", result[Y], result[X]);
	//			return result;
	//		}
	//	}
	//}

	return result;
}
