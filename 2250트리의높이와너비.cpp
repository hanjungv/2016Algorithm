#include<iostream>
#include<climits>
#include<algorithm>
#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;
int tree[10010][2];
bool IMCHILD[10010];
int indx[10010][2];
int from, to1, to2,Cnt=0;
void inorder(int here, int hei){
	if (here == -1)
		return;
	inorder(tree[here][0], hei + 1);
	Cnt++;
	indx[hei][0] = min(indx[hei][0], Cnt);
	indx[hei][1] = max(indx[hei][1], Cnt);
	inorder(tree[here][1], hei + 1);
}
int main(){
	freopen("input.txt", "r", stdin);
	int N,Root=0; scanf("%d", &N);
	for (int i = 0; i < N; i++){
		scanf("%d %d %d", &from, &to1, &to2);
		tree[from][0] = to1;
		tree[from][1] = to2;
		if (to1 != -1) IMCHILD[to1] = true;
		if (to2 != -1) IMCHILD[to2] = true;
	}
	for (int i = 1; i <= N; i++){
		if (!IMCHILD[i]) Root = i;
	}
	for (int i = 0; i <= N; i++){
		indx[i][0] = INT_MAX;
	}
	inorder(Root, 1);
	int wid = -1, hei = 0;
	for (int i = 1; i <= N; i++){
		if (wid < indx[i][1] - indx[i][0]){
			hei = i;
			wid = indx[i][1] - indx[i][0];
		}
	}
	printf("%d %d\n", hei, wid+1);
	return 0;
}