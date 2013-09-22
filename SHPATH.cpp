#include <stdio.h>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>
#include <map>

#define REP(i,n) for(int (i) = 1; (i) <= (n); (i)++)
using namespace std;

int main () {
	// all source shortest path
	int s, n, p, r;
	cin >> s;// no. of tests
	map<string, int> dict;
	vector<vector<pair <int,int> > > *al;
	while (s--) {
		cin >> n;// no. of cities
		al = (vector<vetor pair<int,int> > > *) malloc (sizeof (vector<pair<int,int> >) * n);
		string temp, temp2;
		REP(i,n) {
			cin >> temp;
			dict[temp] = i;
			cin >> p;// no. of neighbours of p
			REP(j,r) {
				int nr, cost;
				cin >> nr >> cost;
				al[i].push_back(make_pair(nr, cost));
			}
		}
		
		cin >> r;// no. of paths to find
		
		REP(i,r) {
			cin >> temp >> temp2;
			int s, t;
			s = dict[temp];
			t = dict[temp2];
			
        }
		printf("%d\n", s);
    }
    return 0;
}
