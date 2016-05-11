#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
typedef long long ll;
using namespace std;
ll T, N, Cnt = 0;
ll dp[2][22][22];
ll arr[22];
//큰놈, 작은놈 숫자 알아야
ll func(ll flag, ll left, ll right){
	if (left == 0 && right == 0) return 1;
	ll &ret = dp[flag][left][right];
	if (ret != -1) return ret;
	ret = 0;
	if (flag == 0)
		for (ll r = 0; r < right; r++)
			ret += func(1, left + r, right - r - 1);
	else
		for (ll l = 0; l < left; l++)
			ret += func(0, left - l - 1, right + l);
	return ret;
}
int main(){
	memset(dp, -1, sizeof(dp));
	scanf("%lld", &T);
	arr[1] = 1;
	for (ll i = 2; i <= 20; i++){
		for (ll j = 0; j < i; j++){
			arr[i] += func(0, j, i - j - 1);
			arr[i] += func(1, j, i - j - 1);
		}
	}
	while (T--){
		scanf("%lld", &N);
		printf("%lld\n", arr[N]);
	}
	return 0;
}