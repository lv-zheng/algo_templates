#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>

typedef long long int lli;
const int CS = 26 + 26 + 10;

int ch2c(char ch)
{
	if (std::isdigit(ch))
		return ch - '0';
	if (std::isupper(ch))
		return ch - 'A' + 10;
	return ch - 'a' + 10 + 26;
}

struct Trie {
	int cnt;
	int nxt[CS];
} trie[5000000];
int gp;

int addchar()
{
	std::memset(&trie[gp], 0, sizeof(trie[gp]));
	return gp++;
}

void addstring(const std::string& s)
{
	int p = 0;
	for (auto ch : s) {
		int c = ch2c(ch);
		if (trie[p].nxt[c])
			p = trie[p].nxt[c];
		else
			p = trie[p].nxt[c] = addchar();
	}
	++trie[p].cnt;
}

std::pair<lli, int> dfs(int p, int depth)
{
	lli ans = 0;
	int bns = 0;
	lli sum2 = 0, sum = 0;
	for (int i = 0; i < CS; ++i) {
		if (trie[p].nxt[i]) {
			auto cns = dfs(trie[p].nxt[i], depth + 1);
			bns += cns.second;
			ans += cns.first;
			sum += cns.second;
			sum2 += cns.second * cns.second;
		}
	}
	lli sab = (sum * sum - sum2) / 2;
	ans += (sab + sum * trie[p].cnt) * (depth * 2 + 1);
	ans += trie[p].cnt * (trie[p].cnt - 1) / 2 * (depth * 2 + 2);
	bns += trie[p].cnt;
	return {ans, bns};
}

int main()
{
	std::ios::sync_with_stdio(false);
	int n;
	int t = 0;
	while (std::cin >> n && n) {
		gp = 1;
		std::cout << "Case " << ++t << ": "; 
		std::memset(&trie[0], 0, sizeof(trie[0]));
		std::string s;
		std::getline(std::cin, s);
		for (int i = 0; i < n; ++i) {
			std::getline(std::cin, s);
			addstring(s);
		}
		auto ans = dfs(0, 0);
		std::cout << ans.first << std::endl;
	}
}
