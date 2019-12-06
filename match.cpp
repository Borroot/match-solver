#include <iostream>
#include <string>

#include <vector>
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
	for (int i = 0; i < A_SIZE; i++) {
		map.insert({U[i], i});
	}

	for (int i = 0; i < A_SIZE; i++) {
		map.insert({V[i], i + A_SIZE});
	}
}

bool contains (vector<int> &vec, int elem)
{
	for (int i = 0; i < (int)vec.size(); i++) {
		if (vec[i] == elem) {
			return true;
		}
	}
	return false;
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
		if (num < A_SIZE) {
			U.push_back(num); // in U
		} else { 
			V.push_back(num); // in V
		}
	}

	// update the adjacency list
	for (int i = 0; i < (int)U.size(); i++) {
		vector<int> &adj_Ui = adj.at(U[i]);

		for (int j = 0; j < (int)V.size(); j++) {
			if (!contains(adj_Ui, V[j])) {
				adj_Ui.push_back(V[j]);	
			}
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
		init_adj(adj, map, A_SIZE);
	}
}

int main ()
{
	int A_SIZE;
	cin >> A_SIZE;

	// U contains 0 to A_SIZE - 1
	// V contains A_SIZE - 1 to A_SIZE * 2 - 1

	vector<vector<int>> adj(A_SIZE);
	input(adj, A_SIZE);

	for (int i = 0; i < adj.size(); i++) {
		cerr << i << ": " << adj[i] << endl;
	}

	//const int RESULT = hopcroft_karp(U, V, adj);
	//cout << ((A_SIZE == RESULT) ? "Veronique" : "Mark") << endl;

	return 0;
}
