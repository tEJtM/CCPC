#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int N(1111);
int a[N];
int len;
struct P {
	int le, ri, v;
	P(int le, int ri, int v) : le(le), ri(ri), v(v) {
	}
};
inline operator < (const P & a, const P & b) {
	return a.le < b.le;
}
vector<P> ans;
void print() {
	for(int i(len - 1); i >= 0; i--) {
		printf("%d", a[i]);
	}
	printf("\n");
}
void calc(int ri, int le, int v, bool flag = false) {
	if(flag && ri == 0) {
		ans.insert(ans.begin(), P(ri, le, v));
	}else {
		ans.push_back(P(ri, le, v));
	}
	a[ri] -= v;
	if(le != ri) {
		a[le] -= v;
	}
	for(int i(ri); i < len; i++) {
		if(a[i] < 0) {
			a[i] += 10;
			a[i + 1] -= 1;
		}
	}
	while(len >= 1 && a[len - 1] == 0) {
		len--;
	}
	/*for(int i(len - 1); i >= 0; i--) {
		printf("%d", a[i]);
	}
	printf("\n");*/
}
void bruteForce(vector<string> & res, int x) {
	if(a[x] == 1) {
		string tmp;
		for(int i(0); i < x; i++) {
			tmp.push_back('9');
		}
		res.push_back(tmp);
		res.push_back("1");
	}else {
		string tmp;
		for(int i(0); i <= x; i++) {
			if(i == 0 || i == x) {
				tmp.push_back('0' + a[x] - 1);
			}else {
				tmp.push_back('9');
			}
		}
		res.push_back(tmp);
		tmp.clear();
		tmp.push_back(11 - a[x] + '0');
		res.push_back(tmp);
	}
}
int main() {
	int tests;
	scanf("%d", &tests);
	for(int qq(1); qq <= tests; qq++) {
		printf("Case #%d:\n", qq);
		static char st[N];
		scanf("%s", st);
		len = strlen(st);
//len = 1000;
		for(int i(0); i < len; i++) {
			a[i] = st[len - i - 1] - '0';
//a[i] = rand() % 9 + 1;
		}
		if(len <= 9) {
			printf("%d\n%d\n", len * 2 - 1, a[0]);
			long long pw(10);
			for(int i(1); i < len; i++) {
				if(a[i] == 0)
					continue;
				if(a[i] == 1) {
					printf("%d\n%d\n", pw - 1, 1);
				}else {
					printf("%d\n%d\n", pw * a[i] - (11 - a[i]), 11 - a[i]);
				}
				pw = pw * 10;
			}
		}else {
			ans.clear();
			if(a[len - 1] * 100 + a[len - 2] * 10 + a[len - 3] < 112) {
				calc(0, len - 2, 8);
			}else if(a[len - 1] >= 3) {
				calc(0, len - 1, a[len - 1] - 2);
			}
			calc(0, len - 3, 1);
			/*while(a[len - 1] <= 2) {
				calc(0, len - 2, 6);
			}
			while(a[len - 1] >= 4) {
				calc(0, len - 1, a[len - 1] - 3);
			}
			if(a[len - 1] == 3 && a[len - 2] > 0) {
				calc(0, len - 2, a[len - 2]);
			}
			if(a[len - 1] == 3 && a[len - 3] > 0) {
				calc(0, len - 3, a[len - 3]);
			}
			if(a[len - 1] == 3) {
				calc(0, len - 3, 1);
			}
			if(a[0] != 9) {
				calc(0, 0, a[0] + 1);
			}*/
			int ri(0);
			while(len - 3 >= ri) {
				int le(len - 1);
				for(;;) {
					if(a[le] == 0 && a[le - 1] == 2) {
						if(a[ri] == 0) {
							break;
						}else if(a[le - 2] >= a[ri]) {
							calc(ri, le - 1, 1);
						}else {
							calc(ri, le - 2, a[ri], true);
						}
					}else {
						calc(ri, le - 1, 1);
					}
					if(a[le] == 0 && a[le - 1] == 1) {
						break;
					}
				}
				if(a[ri]) {
					calc(ri, le - 2, a[ri], true);
					
				}
				//printf("%d %d\n", le, ri);
				ri++;
			}
			vector<string> res;
			if(len - 2 == ri) {
				bruteForce(res, len - 1);
				if(a[len - 2]) {
					//bruteForce(res, len - 2);
					calc(len - 2, len - 2, a[len - 2]);
				}
			}else {
				if(len) {
					bruteForce(res, len - 1);
				}
			}
			int cnt(7);
			for(int i(0); i < (int)ans.size(); i++) {
				//printf("%d %d %d\n", ans[i].le, ans[i].ri, ans[i].v);
				if(ans[i].le == 0 && cnt) {
					cnt--;
					string tmp;
					for(int j(0); j <= ans[i].ri; j++) {
						if(j == 0 || j == ans[i].ri) {
							tmp.push_back(ans[i].v + '0');
						}else {
							tmp.push_back('0');
						}
					}
					res.push_back(tmp);
				}else {
					for(int j(0); j < (int)res.size(); j++) {
						if((int)res[j].size() == ans[i].le + ans[i].ri + 1 && res[j][ans[i].le] + ans[i].v <= '9' && res[j][ans[i].ri] + ans[i].v <= '9') {
							res[j][ans[i].le] += ans[i].v;
							if(ans[i].le != ans[i].ri) 
								res[j][ans[i].ri] += ans[i].v;
							break;
						}
					}
				}
			}
			/*for(int i(0); i < (int)res.size(); i++) {
				for(int j(i + 1); j < (int)res.size(); j++) {
					if(res[i].size() == res[j].size()) {
						//printf("check %s %s\n", res[i].c_str(), res[j].c_str());
						bool flag(true);
						for(int k(0); k < (int)res[i].size(); k++) {
							if(res[i][k] - '0' + res[j][k] - '0' > 9) {
								flag = false;
								break;
							}
						}
						if(flag) {
							for(int k(0); k < (int)res[i].size(); k++) {
								res[i][k] += res[j][k] - '0';
							}
							res.erase(res.begin() + j);
							j--;
						}
					}
				}
			}*/
			printf("%d\n", (int)res.size());
			for(int i(0); i < (int)res.size(); i++) {
				printf("%s\n", res[i].c_str());
			}
		}
	}
}
