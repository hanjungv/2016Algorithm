#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, pair<int, int> > > vi;
vector<pair<int, int> > grx;
vector<pair<int, int> > gry;
vector<pair<int, int> > grz;
int parent[100010];
long long ans = 0;
int find(int x){
	if (parent[x] == x) return x;
	return parent[x] = find(parent[x]);
}
int main(){
	freopen("input.txt", "r", stdin);
	int N, x, y, z; scanf("%d", &N);
	for (int i = 0; i < N; i++){
		scanf("%d %d %d", &x, &y, &z);
		grx.push_back({ x, i + 1 });
		gry.push_back({ y, i + 1 });
		grz.push_back({ z, i + 1 });
	}

	sort(grx.begin(), grx.end());
	sort(gry.begin(), gry.end());
	sort(grz.begin(), grz.end());

	for (int i = 0; i < N - 1; i++)
		vi.push_back({ abs(grx[i].first - grx[i + 1].first), { grx[i].second, grx[i + 1].second } });
	for (int i = 0; i < N - 1; i++)
		vi.push_back({ abs(gry[i].first - gry[i + 1].first), { gry[i].second, gry[i + 1].second } });
	for (int i = 0; i < N - 1; i++)
		vi.push_back({ abs(grz[i].first - grz[i + 1].first), { grz[i].second, grz[i + 1].second } });
	sort(vi.begin(), vi.end());
	for (int i = 1; i <= N; i++) parent[i] = i;
	for (int i = 0; i < vi.size(); i++){
		int fr = vi[i].second.first;
		int to = vi[i].second.second;
		fr = find(fr), to = find(to);
		if (fr == to) continue;
		parent[to] = fr;
		ans += (long long)vi[i].first;
	}
	printf("%lld\n", ans);
	return 0;
}