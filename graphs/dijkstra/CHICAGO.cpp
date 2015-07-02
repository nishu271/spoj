#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

const int NMAX = 105;

struct heapnode {
	int v;
	double prob;
	bool operator <(const heapnode& n) const {
		return prob < n.prob;
	}
}heap[NMAX];

double mat[NMAX][NMAX];
int ar[NMAX];
vector<int> adj[NMAX];
double prob[NMAX];
void swapnode(int idx, int idy) {
	int x = ar[heap[idx].v];
	ar[heap[idx].v] = ar[heap[idy].v];
	ar[heap[idy].v] = x;
	heapnode tmp = heap[idx];
	heap[idx] = heap[idy];
	heap[idy] = tmp;
}

void heapify(int root, int &sz) {
	int l = root*2;
	int r = l + 1;
	int max_id = root;
	if (l <= sz) {
	       	heapify(l, sz);
		if (heap[max_id] < heap[l]) {
			max_id = l;
		}
	}
	if (r <= sz) {
	       	heapify(r, sz);
		if (heap[max_id] < heap[r]) {
			max_id = r;
		}
	}
	swapnode(max_id, root);
}

void bubble_down(int root, int &sz) {
	int l = root * 2;
	int r = l + 1;
	int max_id = root;
	if (l <= sz && heap[max_id] < heap[l]) {
		max_id = l;
	}
	if (r <= sz && heap[max_id] < heap[r]) {
		max_id = r;
	}
	if (root != max_id) {
		swapnode(max_id, root);
		bubble_down(max_id, sz);
	}
}

heapnode extract(int root, int &sz) {
	heapnode ans = heap[root];
	swapnode(root, sz);
	sz--;
	bubble_down(root, sz);
	return ans;
}

void bubble_up(int pos, int &sz) {
	if (1 < pos && pos <= sz && heap[pos>>1] < heap[pos]) {
			swapnode(pos, pos>>1);
			bubble_up(pos>>1, sz);
	}
}

void update_key(int pos, int &sz, double val) {
	if (1 <= pos && pos <= sz) {
		heap[pos].prob = val;
		bubble_up(pos, sz);
		bubble_down(pos, sz);
	}
}
int main () {
	int n, m;
	int a, b, p;
	while (1) {
		memset(adj, 0, sizeof(adj));
		memset(ar, 0, sizeof(ar));
		memset(heap, 0, sizeof(heap));
		memset(prob, 0, sizeof(prob));
		memset(mat, 0, sizeof(mat));
		scanf("%d", &n);
		if (!n) break;
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &p);
			mat[a][b] = p/100.0;
			mat[b][a] = p/100.0;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		for (int i = 1; i <= n; i++) {
			ar[i] = i;
			heap[i].v = i;
			heap[i].prob = 0;
		}	
		heap[ar[1]].prob = 1;
		int num_nodes = n;
		heapify(1, n);
		while (n) {
			heapnode top = extract(1, n);
			int v = top.v;
			prob[v] = top.prob;
			for (int i = 0; i < adj[v].size(); i++) {
				if (heap[ar[adj[v][i]]].prob < prob[v]*mat[v][adj[v][i]]) {
					update_key(ar[adj[v][i]], n, prob[v] * mat[v][adj[v][i]]);
				}	
			}
		}
		printf("%.6f percent\n", prob[num_nodes] * 100);

	}
}
