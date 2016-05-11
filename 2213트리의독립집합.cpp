#include<iostream>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#define NODE_NUM 10010
using namespace std;
int n, from, to;

int dp[NODE_NUM][2];//칠하는지 안칠하는지.
bool visited[NODE_NUM];

vector<int> wei;
vector<vector<int> > vi;
vector<pair<int, int> > trace[NODE_NUM][2]; //역추적할 것을 담아놓는다. 다음상태를 묶어서 저장

void dfs(int here){
	visited[here] = true;
	dp[here][1] = wei[here];//초기값
	for (int i = 0; i < vi[here].size(); i++){
		int next = vi[here][i];
		if (!visited[next]){
			dfs(next);
			//there가 칠해진 경우가 크다면 선택이가능
			if (dp[next][0] < dp[next][1])
				trace[here][0].push_back({ next, 1 });
			else
				trace[here][0].push_back({ next, 0 });
			trace[here][1].push_back({ next, 0 });

			dp[here][0] += max(dp[next][0], dp[next][1]);
			dp[here][1] += dp[next][0];
		}
	}
}

void tracing(int here, int color){
	if (color) printf("%d ",here);
	for (int i = 0; i < trace[here][color].size(); i++){
		int there = trace[here][color][i].first;
		int curColor = trace[here][color][i].second;
		tracing(there, curColor);
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	vi.resize(n + 1);
	wei.resize(n + 1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &wei[i]);
	for (int i = 0; i < (n - 1); i++){
		scanf("%d %d", &from, &to);
		vi[from].push_back(to);
		vi[to].push_back(from);
	}
	dfs(1);
	printf("%d\n", max(dp[1][0], dp[1][1]));//칠하고 안칠하고 중에 최대값.
	if (dp[1][0] < dp[1][1])
		tracing(1, 1);
	else tracing(1, 0);
	puts("");
	return 0;
}