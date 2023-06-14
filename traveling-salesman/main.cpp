#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

typedef pair<int, int> pa;

#define MASK_14 0x00003FFF
#define MAX_VAL_INT INT_MAX

vector<int> neighbours[100000];

void ListOfNeighbours(int number_of_edges);

void Write(int number_of_vertices);

int MakePair(int vertex, int edge_weight){
    return ((vertex << 14) | (edge_weight));
}

int GetVertex(int pair){
    return (pair >> 14);
}

int GetWeight(int pair){
    return pair & MASK_14;
}

void Dijkstra(int* result, int number_of_vertices){
    result[0] = 0;
    for(int i = 1; i < number_of_vertices; i++){
        result[i] = MAX_VAL_INT;
    }
    priority_queue < pa, vector < pa > , greater < pa >> pr_q;
    pr_q.push(make_pair(0, 0));

    pa curr;
    int new_path;
    while(!empty(pr_q)){
        curr = pr_q.top();
        pr_q.pop();
        for(auto it = neighbours[curr.second].begin(); it != neighbours[curr.second].end(); it++) {
            new_path = curr.first + GetWeight(*it);
            if(result[GetVertex(*it)] > new_path) {
                result[GetVertex(*it)] = new_path;
                pr_q.push(make_pair(new_path, GetVertex(*it)));
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    // = NULL;

    //neighbours = new vector<int>[n];
    // = NULL;
    //dijkstra_result = new long long[n];
    ListOfNeighbours(m);
    //Write(n);

    int dijkstra_result[100000];
    Dijkstra(dijkstra_result, n);
    long long result = 0;
    int dest;
    bool correct = true;
    for (int i = 0; i < k; i++){
        cin >> dest;
        dest--;
        if(dijkstra_result[dest] == MAX_VAL_INT){
            correct = false;
            break;
        }
        result += (long long)dijkstra_result[dest];
    }
    if (correct == true){
        cout << result * 2 << "\n";
    }
    else{
        cout << "NIE\n";
    }

    //delete[] dijkstra_result;
    //delete[] neighbours;
    return 0;
}

void ListOfNeighbours(int number_of_edges){
    int a, b, d;
    for(int i  = 0; i < number_of_edges; i++){
        cin >> a >> b >> d;
        a--; b--;
        neighbours[a].push_back(MakePair(b, d));
        neighbours[b].push_back(MakePair(a, d));
    }
}

void Write(int number_of_vertices){
    for(int i = 0; i < number_of_vertices; i++){
        cout << i + 1<< ": [";
        for(auto it = neighbours[i].begin(); it != neighbours[i].end(); it++){
            cout << GetVertex(*it) + 1 << "(" << GetWeight(*it) << ")" << ", ";
        }
        cout << "...]\n";
    }
}
