#include <iostream>
#include <string>
#include <climits>

#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

#define NIL 0
#define INF INT_MAX

// Take a vector and print its contents.
template <typename T>
ostream &operator << (ostream &out, vector<T> &A)
{
	out << "[";
	for (int i = 0; i < (int)A.size(); i++) {
		out << A[i];
		if (i != (int)A.size() - 1) {
			out << ",";
		}
	}
	out << "]";
	return out;
}

void input_vertices (vector<string> &A)
{
	for (int i = 0; i < (int)A.size(); i++) {
		string vertex;
		cin >> vertex;
		A[i] = vertex;
	}
}

void init_map (unordered_map<string,int> &map, const int &A_SIZE)
{
	vector<string> U(A_SIZE);
	vector<string> V(A_SIZE);

	input_vertices(U);
	input_vertices(V);

	// put all the elements of U and V in the map
	for (int u = 0; u < A_SIZE; u++) {
		map.insert({U[u], u + 1});
	}

	for (int v = 0; v < A_SIZE; v++) {
		map.insert({V[v], v + A_SIZE + 1});
	}
}

void init_adj (vector<vector<int>> &adj, unordered_map<string,int> &map, const int &A_SIZE)
{
	string tmp; cin >> tmp;
	int C_SIZE;
	cin >> C_SIZE;

	vector<int> U;
	vector<int> V;

	// read the cast of the movie
	for (int i = 0; i < C_SIZE; i++) {
		string vertex;
		cin >> vertex;

		int num = map.at(vertex);
		if (num <= A_SIZE) {
			U.push_back(num); // in U
		} else { 
			V.push_back(num); // in V
		}
	}

	// update the adjacency list
	for (int u = 0; u < (int)U.size(); u++) {
		vector<int> &adj_u = adj[U[u]];

		for (int v = 0; v < (int)V.size(); v++) {
			adj_u.push_back(V[v] - A_SIZE);	
		}
	}
}

void input (vector<vector<int>> &adj, const int &A_SIZE)
{
	int M_SIZE;
	cin >> M_SIZE;

	// map all names (strings) to unique integers
	unordered_map<string,int> map;
	init_map(map, A_SIZE);

	for (int i = 0; i < M_SIZE; i++) {
		cerr << i << "-";
		init_adj(adj, map, A_SIZE);
	}
}

void init_nil (vector<int> vec)
{
	for (int i = 0; i < (int)vec.size(); i++) {
		vec[i] = NIL;
	}
}

// Returns true if there is an augmenting path else returns false.
bool bfs (vector<int> &pair_U, vector<int> &pair_V, vector<int> &dist, vector<vector<int>> &adj)
{
	queue<int> Q;

	for (int u = 1; u < (int)pair_U.size(); u++) {
		if (pair_U[u] == NIL) {
			dist[u] = 0;
			Q.push(u);
		} else {
			dist[u] = INF;
		}
	}
	dist[NIL] = INF;

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		if (dist[u] < dist[NIL]) {
			for (int i = 0; i < (int)adj[u].size(); i++) {
				int v = adj[u][i];
				if (dist[pair_V[v]] == INF) {
					dist[pair_V[v]] = dist[u] + 1;
					Q.push(pair_V[v]);
				}
			}
		}
	}
	return dist[NIL] != INF;
}

bool dfs (const int u, vector<int> &pair_U, vector<int> &pair_V, vector<int> &dist, vector<vector<int>> &adj)
{
	if (u != NIL) {
		for (int i = 0; i < (int)adj[u].size(); i++) {
			int v = adj[u][i];
			if (dist[pair_V[v]] == dist[u] + 1) {
				if (dfs(pair_V[v], pair_U, pair_V, dist, adj)) {
					pair_V[v] = u;
					pair_U[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int hopcroft_karp (vector<vector<int>> &adj, const int &A_SIZE)
{
	vector<int> pair_U(A_SIZE + 1);
	vector<int> pair_V(A_SIZE + 1);
	vector<int> dist(A_SIZE + 1);

	init_nil(pair_U);
	init_nil(pair_V);

	int matching = 0;

	while (bfs(pair_U, pair_V, dist, adj)) {
		for (int u = 1; u < (int)pair_U.size(); u++) {
			if (pair_U[u] == NIL && dfs(u, pair_U, pair_V, dist, adj)) {
				matching++;
			}
		}
	}
	return matching;
}

int main ()
{
	int A_SIZE;
	cin >> A_SIZE;

	// U contains NIL + 1 to A_SIZE
	// V contains NIL + 1 to A_SIZE

	vector<vector<int>> adj(A_SIZE + 1);
	input(adj, A_SIZE);

	const int RESULT = hopcroft_karp(adj, A_SIZE);
	cout << ((A_SIZE == RESULT) ? "Mark" : "Veronique") << endl;

	return 0;
}
