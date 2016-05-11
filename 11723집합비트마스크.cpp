#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
using namespace std;
int numSet;
char input[10];
int main(){
	freopen("input.txt", "r", stdin);
	int T, val; scanf("%d", &T);
	numSet = 0;
	getchar();
	while (T--){
		scanf("%s", input);
		if (input[1] == 'd'){
			scanf("%d", &val);
			val--;
			numSet |= (1 << val);
		}

		else if (input[1] == 'e'){
			scanf("%d", &val);
			val--;
			numSet &= ~(1 << val);
		}

		else if (input[1] == 'h'){
			scanf("%d", &val);
			val--;
			if (numSet & (1 << val)) puts("1");
			else puts("0");
		}
		else if (input[1] == 'o'){
			scanf("%d", &val);
			val--;
			numSet ^= (1 << val);
		}
		else if (input[1] == 'l'){
			numSet = (1 << 20) - 1;
		}
		else if (input[1] == 'm'){
			numSet = 0;
		}
	}
	return 0;
}