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
const int INF = 1000000000;
const int NMAX = 10005;
const int MMAX = 100005;
const int KMAX = 305;
struct heapnode {
	int u, key;
	bool operator <(const heapnode& n) const {
		return key < n.key;
	}
}heap[NMAX];

int vhmap[NMAX];
int dist[NMAX];
vector <int> adj[NMAX];
map<int, int> e;
void swapnode(int, int);
void heapify(int, int);
void bubble_up(int, int);
void bubble_down(int, int);
void update(int, int, int);
heapnode extract(int&);

inline void fastRead_int(int &x) {
	register int c = getchar_unlocked();
	x = 0;
	int neg = 0;
	for (; (c < 48 || c > 57) && c != '-';) c = getchar_unlocked();
	
	if (c == '-') {
		neg = 1;
		c = getchar_unlocked();
	}
	for (; (c > 47 && c < 58); c = getchar_unlocked()) {
		x = (x<<1) + (x<<3) + c - 48;
	}
	if (neg) x = -x;
}

int compute_hash(int a, int b) {
	return a*NMAX + b;
}
void swapnode (int idx, int idy) {
	int t = vhmap[heap[idx].u];
	vhmap[heap[idx].u] = vhmap[heap[idy].u];
	vhmap[heap[idy].u] = t;
	heapnode tmp = heap[idx];
	heap[idx] = heap[idy];
	heap[idy] = tmp;
}

void heapify(int root, int sz) {
	int l = (root<<1);
	int r = (l|1);
	int min_id = root;
	if (l <= sz) {
		heapify(l, sz);
		if (heap[l] < heap[min_id]) {
			min_id = l;
		}
	}
	if (r <= sz) {
		heapify(r, sz);
		if (heap[r] < heap[min_id]) {
			min_id = r;
		}
	}
	swapnode(root, min_id);
}

heapnode extract(int &sz) {
	heapnode ret = heap[1];
	swapnode(1, sz);
	sz--;
	bubble_down(1, sz);
	return ret;
}

void bubble_down(int root, int sz) {
	int l      = root<<1, 
	    r      = l|1, 
	    min_id = root;
	if (l <= sz && heap[l] < heap[min_id]) min_id = l;
	if (r <= sz && heap[r] < heap[min_id]) min_id = r;
	if (min_id != root) {
		swapnode(min_id, root);
		bubble_down(min_id, sz);
	}
}

void update(int n, int sz, int val) {
	heap[n].key = val;
	bubble_up(n, sz);
	bubble_down(n, sz);
}

void bubble_up(int pos, int sz) {
	if (1 < pos && pos <= sz && heap[pos] < heap[pos>>1]) {
		swapnode(pos, pos>>1);
		bubble_up(pos>>1, sz);
	}
}
const int TMAX = 21;
struct tests {
	int v[5];
	int e[NMAX][3];
	int k[KMAX][3];
}t[TMAX];

int main () {
#ifdef PROFILE_TIME
	double clt = clock();
#endif
	int tt;
	int n, m, k, s, d, a, b, v;
	scanf("%d", &tt);
	memset(t, 0, sizeof(t));
	for (int i = 0; i < tt; i++) {
		for (int j = 0; j < 5; j++) fastRead_int(t[i].v[j]);
		for (int j = 0; j < t[i].v[1]; j++) {
			for (int p = 0; p < 3; p++) {
				fastRead_int(t[i].e[j][p]);
			}
		}
		for (int j = 0; j < t[i].v[2]; j++) {
			for (int p = 0; p < 3; p++) {
				fastRead_int(t[i].k[j][p]);
			}
		}
	}
#ifdef PROFILE_TIME
	printf("time taken in input: %g seconds\n", (clock() - clt)/CLOCKS_PER_SEC);
#endif
	for (int q = 0; q < tt; q++) {
		memset(adj, 0, sizeof(adj));
		e.clear();
		n = t[q].v[0];
	       	m = t[q].v[1]; 
	       	k = t[q].v[2]; 
	       	s = t[q].v[3]; 
	       	d = t[q].v[4]; 
		for (int i = 0; i < m; i++) {
			a = t[q].e[i][0];
			b = t[q].e[i][1];
			v = t[q].e[i][2];
			e[compute_hash(a,b)] = v;
			adj[a].push_back(b);
		}
		int ans = INF;	
		int prevab, prevba;
		int ab, ba;
		for (int i = 0; i < k; i++) {
			int sz = n;
			a = t[q].k[i][0];
			b = t[q].k[i][1];
			v = t[q].k[i][2];	
			ab = compute_hash(a,b), ba = compute_hash(b,a);
			if (e.find(ab) == e.end()) {
				e[ab] = v;
				prevab = INF;
			}
			else {
				prevab = e[ab];
				if (e[ab] > v) e[ab] = v;
			}	
			if (e.find(ba) == e.end()) {
				e[ba] = v;
				prevba = INF;
			}
			else {
				prevba = e[ba];
				if (e[ba] > v) e[ba] = v;
			}
			adj[a].push_back(b);
			adj[b].push_back(a);
			memset(dist, 0, sizeof(dist));
			memset(heap, 0, sizeof(heap));
			memset(vhmap, 0, sizeof(vhmap));
			for (int j = 1; j <= n; j++) {
				heap[j].u = j;
				heap[j].key = INF;
				vhmap[j] = j;
			}
			heap[s].key = 0;
			heapify(1, sz);
			while (sz) {
				heapnode top = extract(sz);
				int u = top.u;
				dist[u] = top.key;
				for (int j = 0; j < adj[u].size(); j++) {
					int v =  adj[u][j];
					int dv = dist[u] + e[compute_hash(u,v)]; 
					if (heap[vhmap[v]].key > dv) {
						update(vhmap[v], sz, dv);
					}
				}
			}
			ans = min(dist[d], ans);
			adj[a].pop_back();
			adj[b].pop_back();
			e[ab] = prevab;
			e[ba] = prevba;
		}	
		printf ("%d\n", ((ans==INF)?-1:ans));
	}
#ifdef PROFILE_TIME
	printf("time taken : %g seconds\n", (clock() - clt)/CLOCKS_PER_SEC);
#endif
}
