#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
string toString(int x) {
	string res;
	while(x) {
		res.push_back(x % 10 + '0');
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}
int main(int argc, char ** argv) {
	FILE * f = fopen(argv[1], "r");
	FILE * g = fopen(argv[2], "r");
	int tests;
	fscanf(f, "%d", &tests);
	bool flag(true);
	for(int qq(1); qq <= tests; qq++) {
		static char st[1111], st1[1111];
		fscanf(f, "%s", st);
		string ca((string)"Case #" + toString(qq) + ":");
		for(int i(0); i < (int)ca.size(); i++) {
			char c;
			fscanf(g, "%c", &c);
			if(c != ca[i]) {
				flag = false;
				break;
			}
		}
		int n;
		fscanf(g, "%d", &n);
		if(n <= 0 || n >= 50) {
			flag = false;
			break;
		}
		static int sum[1111];
		memset(sum, 0, sizeof(sum));
		for(int i(0); i < n; i++) {
			char c;
			fscanf(g, "%c", &c);
			while(c < '0' || c > '9') {
				fscanf(g, "%c", &c);
			}
			string p;
			while(c >= '0' && c <= '9') {
				p.push_back(c);
				if(p.size() > 1000) {
					flag = false;
					break;
				}
				fscanf(g, "%c", &c);
			}
			//printf("%s\n", p.c_str());
			string q(p);
			reverse(q.begin(), q.end());
			if(p[0] == '0' || q != p) {
				flag = false;
				break;
			}
			for(int i(0); i < (int)p.size(); i++) {
				sum[i] += p[i] - '0';
			}
		}
		int len(strlen(st));
		for(int i(0); i < len; i++) {
			sum[i + 1] += sum[i] / 10;
			sum[i] %= 10;
			if(sum[i] != st[len - i - 1] - '0') {
				flag = false;
				break;
			}
		}
		reverse(sum, sum + len);
		for(int i(0); i < len; i++) {
			st1[i] = sum[i] + '0';
		}
		st1[len] = 0;
		if(sum[len] != 0) {
			flag = false;
			break;
		}
	}
	printf("%s\n", flag ? "OK" : "WA");
	FILE * h = fopen(argv[4], "w");
	fprintf(h, "%s\n", flag ? "OK" : "WA");
}
