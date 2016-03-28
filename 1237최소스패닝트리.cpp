#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
int V, E, from, to, wei,ans=0;
struct Edge{
	int from, to, cost;
};
Edge edge[100010];
int parent[100010];
bool cmp(const Edge &A,const Edge &B){
	return A.cost < B.cost;
}
int find(int x){
	if (parent[x] == x) return x;
	return parent[x] = find(parent[x]);
}
int main(){
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &V, &E);
	for (int i = 0; i < E; i++){
		scanf("%d %d %d", &from, &to, &wei);
		edge[i].from = from;
		edge[i].to = to;
		edge[i].cost = wei;
	}
	sort(edge, edge + E, cmp);
	for (int i = 1; i <= V; i++)
		parent[i] = i;
	for (int i = 0; i < E; i++){
		int x = edge[i].from;
		int y = edge[i].to;
		x = find(x); y = find(y);
		if (x == y) continue;
		parent[y] = x;
		ans += edge[i].cost;
	}
	printf("%d\n", ans);
	return 0;
}