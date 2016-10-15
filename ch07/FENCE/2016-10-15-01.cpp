#include <iostream>
#include <vector>
#define MAX(x, y) (x)>(y)?(x):(y)
#define MIN(x, y) (x)<(y)?(x):(y)
#define INF 987654321

using namespace std;

int getRectangle(vector<int>& fence, int start, int end);

int main(void){
	int C = 0;
	cin >> C;

	while(C-->0){
		int N = 0, input = 0;
		cin >> N;
		
		vector<int> fence;
		for(int i=0; i<N; i++){
			cin >> input;
			fence.push_back(input);
		}

		cout << getRectangle(fence, 0, N-1) << endl;
	}
	
	return 0;
}

int getRectangle(vector<int>& fence, int start, int end){
	if(start==end) return fence[start];

	int center = (start + end)/2;
	int leftWidth = getRectangle(fence, start, center);
	int rightWidth = getRectangle(fence, center+1, end);
	
	int result = MAX(leftWidth, rightWidth);
	
	int num = 1;
	int left = center, right = center;
	int minHeight = fence[center];
	int centerWidth = minHeight * num;

	while(left > start || right < end){
		if(left == start){
			right++;
			minHeight = MIN(minHeight, fence[right]);
		}else if(right == end){
			left--;
			minHeight = MIN(minHeight, fence[left]);
		}else{
			if(fence[left-1]>fence[right+1]){
				left--;
				minHeight = MIN(minHeight, fence[left]);
			}else{
				right++;
				minHeight = MIN(minHeight, fence[right]);
			}
		}
		centerWidth = MAX(centerWidth, (right - left + 1) * minHeight);
	}

	result = MAX(result, centerWidth);
	return result;
}
