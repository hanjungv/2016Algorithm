#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
int N, M, num, idx;
vector<int> tree;
void update(int pos, int val){
	int x = idx + pos + 1;
	tree[x] = val;
	x >>= 1;
	while (x){
		tree[x] = max(tree[2 * x], tree[(2 * x + 1)]);
		x >>= 1;
	}
}
int find(int L, int R){
	int left = idx + L + 1;
	int right = idx + R + 1;
	int ret = INT_MIN;
	while (left <= right){
		if (left % 2 == 1) ret = max(ret, tree[left++]);
		if (right % 2 == 0) ret = max(ret, tree[right--]);
		left >>= 1;
		right >>= 1;
	}
	return ret;
}
int main(){
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	tree.resize(4 * N);
	for (idx = 1; idx < N; idx <<= 1);//base address ÃÊ±âÈ­
	for (int i = 1; i <= N; i++){
		scanf("%d", &num);
		update(i, num);
	}
	for (int i = M; i <= N - M + 1 ; i++){
		printf("%d ", find(i - ( M - 1), i + M - 1));
	}
	return 0;
}
