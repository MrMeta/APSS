#include <stdio.h>
#include <string.h>

int map[100][100];
int cache[100][100];
int size;

// int searchPath(int startX, int startY, int endX, int endY);

int main(){
	int C = 0;
	scanf("%d", &C);

	while(C-->0){
		memset(map, -1, sizeof(map));
		memset(cache, 0, sizeof(cache));

		size = -1;
		scanf("%d", &size);

		for(int i=0; i<size; i++)
			for(int j=0; j<size; j++)
				scanf("%d", &map[i][j]);

		cache[0][0] = 1;
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				if(cache[i][j] > 0){
					if(j + map[i][j] < size) cache[i][j+map[i][j]] += 1;
					if(i + map[i][j] < size) cache[i+map[i][j]][j] += 1;
				}
			}
		}

		if(cache[size-1][size-1] > 0) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}

// int searchPath(int startX, int startY, int endX, int endY){
//	if(startX < 0 || startY < 0 || endX >= size || endY >= size) return 0;
//	if(startX > endX || startY > endY) return 0;
//	
//	int& ret = cache[endX
// }
