#include<iostream>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#define NODE_NUM 10010
using namespace std;
int n, from, to;

int dp[NODE_NUM][2];//ĥ�ϴ��� ��ĥ�ϴ���.
bool visited[NODE_NUM];

vector<int> wei;
vector<vector<int> > vi;
vector<pair<int, int> > trace[NODE_NUM][2]; //�������� ���� ��Ƴ��´�. �������¸� ��� ����

void dfs(int here){
	visited[here] = true;
	dp[here][1] = wei[here];//�ʱⰪ
	for (int i = 0; i < vi[here].size(); i++){
		int next = vi[here][i];
		if (!visited[next]){
			dfs(next);
			//there�� ĥ���� ��찡 ũ�ٸ� �����̰���
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
	printf("%d\n", max(dp[1][0], dp[1][1]));//ĥ�ϰ� ��ĥ�ϰ� �߿� �ִ밪.
	if (dp[1][0] < dp[1][1])
		tracing(1, 1);
	else tracing(1, 0);
	puts("");
	return 0;
}