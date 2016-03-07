#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
int N, M, num, l, r, idx;
vector<int> tree;
void update(int pos, int val){
	int x = idx + pos;
	tree[x] = val;
	x >>= 1;
	while (x){
		tree[x] = min(tree[2 * x], tree[(2 * x + 1)]);
		x >>= 1;
	}
}
int find(int L, int R){
	int left = idx + L;
	int right = idx + R;
	int ret = INT_MAX;
	while (left <= right){
		if (left % 2 == 1) ret = min(ret, tree[left++]);
		if (right % 2 == 0) ret = min(ret, tree[right--]);
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

	for (int i = 0; i < N; i++){
		scanf("%d", &num);
		update(i, num);
	}
	for (int i = 0; i < M; i++){
		scanf("%d %d", &l, &r);
		printf("%d\n", find(--l, --r));
	}
	return 0;
}
