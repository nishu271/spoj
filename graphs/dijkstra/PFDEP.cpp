#include <cstdio>
#include <cmath>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

const int NMAX = 103;
const int MMAX = 103;

vi adj[NMAX];
int deg[NMAX];
int visited[NMAX];
int main () {
	int n, m, x, y, k;
	scanf("%d%d", &n, &m);
	memset(deg, 0, sizeof(deg));
	int first = true;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &x, &k);
		deg[x] += k;
		for (int j = 0; j < k; j++) {
			scanf("%d", &y);
			adj[y].push_back(x);
		}
	}
	memset(visited, 0, sizeof(visited));
	int p = 0;
	vector<int> pn;
	while (p < n) {
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0 && deg[i] == 0) {
				visited[i] = 1;
				pn.push_back(i);	
			}
		}
		sort(pn.begin() + p, pn.end());
		if(first) {
			first = false;
			printf("%d", pn[p]);
		}
		else {
			printf(" %d", pn[p]);
		}
		for (int j = 0; j < adj[pn[p]].size(); j++) {
			deg[adj[pn[p]][j]]--;
		}
		p++;
	}
}
