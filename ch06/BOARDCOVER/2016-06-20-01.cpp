// 20160620
// �����δ� ������ �ð�(�켱�� 3�ð�)���� �����ġ�� �� �� �׵��� Ǯ�� ���ϸ� ���� ���� ������ ����.
// ���� ȭ��� ��� ���� ������ �� �ð��� ����
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
	{ {0, 0}, {0, 1}, {1, 0} },		//��
	{ {0, 0}, {0, -1}, {1, 0} },	// ��
	{ {0, 0}, {0, -1}, {-1, 0} },	// ��
	{ {0, 0}, {0, 1}, {-1, 0} }		//��
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

// ��� ���ѷ����� ���� ������
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
			// ���⼭ ������ �ɷ����� �ϴµ� �� �ȵǴ°��� ��..
			// ��.. ó���� #�� ���� abled = false�� �� �Ŀ� ���� ��ǥ�� �Ѿ�� ���ϳ�
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

// ó������ int*�� ��ȯ������ �迭ó�� �۵����� �ʾƼ� ����ü�� ���.. ����..???
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
