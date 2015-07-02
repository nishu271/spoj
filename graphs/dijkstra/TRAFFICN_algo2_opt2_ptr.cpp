#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define PROFILE_TIME
const uint INF = 1000000000;
const uint NMAX = 10005;
const uint MMAX = 100005;
const uint KMAX = 305;
struct heapnode {
	uint u, key;
	bool operator <(const heapnode& n) const {
		return key < n.key;
	}
}heap[NMAX],*arr[NMAX];

typedef unsigned int uint;
uint vhmap[NMAX];
uint dist[NMAX];
uint dist_rev[NMAX];
vector <uint> adj[NMAX], adj_rev[NMAX];
map<uint, uint> e, e_rev;
void swapnode(uint, uint);
void heapify(uint, uint);
void bubble_up(uint, uint);
void bubble_down(uint, uint);
void update(uint, uint, uint);
heapnode* extract(uint&);

inline void fastRead_uint(uint &x) {
	register uint c = getchar_unlocked();
	x = 0;
	for (; (c < 48 || c > 57);) c = getchar_unlocked();
	
	for (; (c > 47 && c < 58); c = getchar_unlocked()) {
		x = (x<<1) + (x<<3) + c - 48;
	}
}

uint compute_hash(uint a, uint b) {
	return a*NMAX + b;
}
inline void swapnode (uint idx, uint idy) {
	int t = vhmap[idx];
	vhmap[idx] = vhmap[idy];
	vhmap[idy] = t;
	heapnode *tmp = arr[idx];
	arr[idx] = arr[idy];
	arr[idy] = tmp;
}

void heapify(uint root, uint sz) {
	uint l = (root<<1);
	uint r = (l|1);
	uint min_id = root;
	if (l <= sz) {
		heapify(l, sz);
		if (arr[l]->key < arr[min_id]->key) {
			min_id = l;
		}
	}
	if (r <= sz) {
		heapify(r, sz);
		if (arr[r]->key < arr[min_id]->key) {
			min_id = r;
		}
	}
	swapnode(root, min_id);
}

inline heapnode* extract(uint &sz) {
	heapnode *ret = arr[1];
	swapnode(1, sz);
	sz--;
	bubble_down(1, sz);
	return ret;
}

inline void bubble_down(uint root, uint sz) {
	while(root <= sz) {
		uint l = root<<1, 
		     r = l|1, 
	   	min_id = root;
		if (l <= sz && arr[l]->key < arr[min_id]->key) min_id = l;
		if (r <= sz && arr[r]->key < arr[min_id]->key) min_id = r;
		if (min_id != root) {
			swapnode(min_id, root);
			root = min_id;
		}
		else break;
	}
}

inline void update(uint n, uint sz, uint val) {
	arr[n]->key = val;
	bubble_up(n, sz);
}

inline void bubble_up(uint pos, uint sz) {
	while (1 < pos && pos <= sz && arr[pos]->key < arr[pos>>1]->key) {
		swapnode(pos, pos>>1);
		pos >>= 1;
	}
}
const uint TMAX = 21;

int main () {
#ifdef PROFILE_TIME
	double clt = clock();
#endif
	uint tt;
	uint n, m, k, s, d, a, b, v;
	fastRead_uint(tt);
#ifdef PROFILE_TIME
	printf("time taken in input: %g seconds\n", (clock() - clt)/CLOCKS_PER_SEC);
#endif
	for (uint q = 0; q < tt; q++) {
		memset(adj, 0, sizeof(adj));
		memset(adj_rev, 0, sizeof(adj_rev));
		e.clear();
		e_rev.clear();
		fastRead_uint(n);
		fastRead_uint(m);
		fastRead_uint(k);
		fastRead_uint(s);
		fastRead_uint(d);
		for (uint i = 0; i < m; i++) {
			fastRead_uint(a);
			fastRead_uint(b);
			fastRead_uint(v);
			e[compute_hash(a,b)] = v;
			e_rev[compute_hash(b,a)] = v;
			adj[a].push_back(b);
			adj_rev[b].push_back(a);
		}
		memset(dist, 0, sizeof(dist));
		memset(dist_rev, 0, sizeof(dist_rev));
		memset(heap, 0, sizeof(heap));
		uint sz = n;
		for (uint j = 1; j <= n; j++) {
			heap[j].u = j;
			heap[j].key = INF;
			arr[j] = &heap[j];
			vhmap[j] = j;
		}
		heap[s].key = 0;
		heapify(1, sz);
		while (sz) {
			heapnode *top = extract(sz);
			uint u = top->u;
			dist[u] = top->key;
			for (uint j = 0; j < adj[u].size(); j++) {
				uint v =  adj[u][j];
				uint dv = dist[u] + e[compute_hash(u,v)];
				if (heap[v].key > dv) {
					update(vhmap[v], sz, dv);
				}
			}
		}
		sz = n;
		memset(heap, 0, sizeof(heap));
		for (uint j = 1; j <= n; j++) {
			heap[j].u = j;
			heap[j].key = INF;
			arr[j] = &heap[j];
			vhmap[j] = j;
		}
		heap[d].key = 0;
		heapify(1, sz);
		while (sz) {
			heapnode *top = extract(sz);
			uint u = top -> u;
			dist_rev[u] = top -> key;
			for (uint j = 0; j < adj_rev[u].size(); j++) {
				uint v =  adj_rev[u][j];
				uint dv = dist_rev[u] + e_rev[compute_hash(u,v)]; 
				if (heap[v].key > dv) {
					update(vhmap[v], sz, dv);
				}
			}
		}
		uint ans = dist[d];
		for (uint i = 0; i < k; i++) {
			fastRead_uint(a);
			fastRead_uint(b);
			fastRead_uint(v);
			ans = min(min(ans, dist[a] + v + dist_rev[b]), dist[b] + v + dist_rev[a]);
		}
		printf ("%d\n", ((ans==INF)?-1:ans));
	}
#ifdef PROFILE_TIME
	printf("time taken : %g seconds\n", (clock() - clt)/CLOCKS_PER_SEC);
#endif
}
