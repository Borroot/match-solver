#include <iostream>
#include <string>

#include <vector>
#include <unordered_map>

using namespace std;

typedef string T;

// Take a vector with elements of type T and print its contents.
ostream &operator << (ostream &out, vector<T> &A)
{
	cerr << "[";
	for (int i = 0; i < (int)A.size(); i++) {
		cerr << A[i];
		if (i != (int)A.size() - 1) {
			cerr << ",";
		}
	}
	cerr << "]";
	return out;
}

// Take in a vector A and an element e and check if e is in A.
bool in (vector<T> &A, T e)
{
	for (int i = 0; i < (int)A.size(); i++) {
		if (A[i] == e) {
			return true;
		}
	}
	return false;
}

// Take in a vector A and fill it with input from stdin.
void input_vertices (vector<T> &A, const int &SIZE)
{
	for (int i = 0; i < (int)SIZE; i++) {
		T vertex;
		cin >> vertex;
		A.push_back(vertex);
	}
}

// Take in a cast C and split it in elements from U and V which
// will be stored in _U and _V respectively.
void process_cast (vector<T> &C, vector<T> &_U, vector<T> &_V, vector<T> &U)
{
	for (int j = 0; j < (int)C.size(); j++) {
		if (in(U, C[j])) {
			_U.push_back(C[j]);
		} else { // C[j] in V
			_V.push_back(C[j]);
		}
	}
}

// Take in a list U and a list V and for every element u in U add
// everything from V to U's adjacency list (without making duplicates).
void process_adjs (vector<T> &U, vector<T> &V, unordered_map<T,vector<T>> &adj)
{
	for (int i = 0; i < (int)U.size(); i++) {
		vector<T> &adj_Ui = adj.at(U[i]);

		for (int j = 0; j < (int)V.size(); j++) {
			if (!in(adj_Ui, V[j])) {
				adj_Ui.push_back(V[j]);
			}
		}
	}
}

// Take in a list U and a list V. Save the actresses in U and the actors in V.
// Futhermore take in the adj list and save all the adjacents to every element from U here.
void input (vector<T> &U, vector<T> &V, unordered_map<T,vector<T>> &adj, const int &A_SIZE)
{
	int M_SIZE;
	cin >> M_SIZE;

	input_vertices(U, A_SIZE);
	input_vertices(V, A_SIZE);

	for (int i = 0; i < A_SIZE; i++) {
		vector<T> adj_Ui;
		adj.insert({U[i], adj_Ui});
	}

	for (int i = 0; i < M_SIZE; i++) {
		T tmp; cin >> tmp;
		int C_SIZE;
		cin >> C_SIZE;

		vector<T> C;
		input_vertices(C, C_SIZE);

		// split C in two lists _U and _V
		vector<T> _U;
		vector<T> _V;
		process_cast(C, _U, _V, U);

		// for all elems in _U add everything from _V to their adjs
		process_adjs(_U, _V, adj);
	}
}

int hopcroft_karp ()
{

	return 0;
}

int main ()
{
	int A_SIZE;
	cin >> A_SIZE;

	vector<T> U;
	vector<T> V;
	unordered_map<T,vector<T>> adj; // adjs of elems from U

	input(U, V, adj, A_SIZE);

	const int RESULT = hopcroft_karp();
	cout << ((A_SIZE == RESULT) ? "Veronique" : "Mark") << endl;

	// prints the elements 
	for (auto itr = adj.begin(); itr != adj.end(); itr++) { 
		cerr << itr->first << '\t' << itr->second << '\n'; 
	} 
	return 0;
}
