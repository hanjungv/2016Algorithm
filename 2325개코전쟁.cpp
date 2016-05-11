#include<vector>
#include<queue>
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
#include<functional>
#include<cstring>
#define INF 210000000
using namespace std;
int M, N, from, to, wei;
vector<vector<pair<int, int> > > vi;

vector<int> parent, trace;

int dijkstra(int Start, int u, int v){
	vector<int> dist(N + 1, INF);
	priority_queue <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int>> > pq;
	pq.push({ 0, Start });
	dist[Start] = 0;
	while (!pq.empty()){
		int Cost = pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < Cost) continue;
		for (int i = 0; i < vi[here].size(); i++){
			int there = vi[here][i].first, nextDist = Cost + vi[here][i].second;
			if ((here == u && there == v) || (here == v && there == u)) continue;
			if (dist[there] > nextDist){ 
				dist[there] = nextDist;
				parent[there] = here;
				pq.push({ nextDist, there });
			}
		}
	}
	return dist[N];
}


int main(){
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	vi.resize(N + 1);
	for (int i = 0; i < M; i++){
		scanf("%d %d %d", &from, &to, &wei);
		vi[from].push_back({ to, wei });
		vi[to].push_back({ from, wei });
	}

	parent = vector<int>(N + 1, -1);

	int val = dijkstra(1, 0, 0);
	
	vector<int> parent2 = parent;
	int child = N;

	while (child != -1){
		trace.push_back(child);
		child = parent2[child];
	}

	reverse(trace.begin(), trace.end());

	int ans = -987654321;
	for (int i = 0; i < trace.size() - 1; i++){
		int u = trace[i], v = trace[i + 1];
		int curDist = dijkstra(1, u, v);
		ans = max(ans, curDist);
	}
	
	printf("%d\n", ans);
	return 0;
}