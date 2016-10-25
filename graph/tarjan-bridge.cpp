#include <bitset>
#include <cstring>

#include "graph_llist.hpp"

int tmr;
int idx[N];
int low[N];
std::bitset<N> isartv;

void tarjan_rec(int node, int par)
{
	idx[node] = low[node] = ++tmr;
	for (int e = gbegin[node]; e; e = gedges[e].next) {
		int son = gedges[e].to;
		if (!idx[son]) {
			tarjan_rec(son, node);
			low[node] = std::min(low[node], low[son]);
		} else if (son != par) {
			low[node] = std::min(low[node], idx[son]);
		}
		if (low[son] > idx[node])
			isartv[node] = true;
	}
}

void tarjan()
{
	std::memset(idx, 0, sizeof(idx));
	std::memset(low, 0, sizeof(low));
	isartv.reset();
	tmr = 0;
	for (int i = 1; i <= n; ++i) {
		if (!idx[i])
			tarjan_rec(i, -1);
	}
}
