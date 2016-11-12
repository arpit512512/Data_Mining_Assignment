#include <iostream>
#include <vector>
#include <list>
using namespace std;


void MinHeapify(vector<pair<int,int> > &heap, int idx) {

    int minimum = heap[idx].first;
    int in = idx;

    if(2*idx + 1 < heap.size() and heap[2*idx+1].first < minimum) {
        minimum = heap[2*idx+1].first;
        in = 2*idx + 1;
    }

    if(2*idx + 2 < heap.size() and heap[2*idx+2].first < minimum) {
        minimum = heap[2*idx+2].first;
        in = 2*idx + 2;
    }

    if(idx != in) {
        swap(heap[idx], heap[in]);
        MinHeapify(heap, in);
    }

}

vector<list<pair<int,int> > > graph(1<<21);
void  Insert(vector<pair<int,int> > &heap, pair<int,int> val) {
    heap.push_back(val);
    int i = heap.size()-1;
    int i_papa =  (i-1)/2;

    while(i != 0) {
        if(heap[i_papa].first > heap[i].first) {
            swap(heap[i_papa], heap[i]);
            i = i_papa;
            i_papa = (i-1)/2;
        }
        else{
            break;
        }
    }
}

pair<int,int> Pop(vector<pair<int,int> > &heap) {
    pair<int,int> top = heap[0];
    swap(heap[0], heap[heap.size()-1]);
    heap.pop_back();
    MinHeapify(heap, 0);
    return top;
}

bool Empty(vector<pair<int,int> > &heap) {
    if(heap.size() == 0)
        return true;
    return false;
}

int PrimsMST(vector<list<pair<int,int> > > &graph, int start = 0) {
    vector<pair<int,int> > heap;
    vector<bool> visited(graph.size(), false);
    Insert(heap, make_pair(0, start));
    int answer = 0;
    while(not Empty(heap)) {
        pair<int,int> temp = Pop(heap);
        if(not visited[temp.second]) {
            visited[temp.second] = true;
            answer += temp.first;
        }
        list<pair<int, int> >::iterator it = graph[temp.second].begin();
        for( ;it !=  graph[temp.second].end();it++) {
            if(not visited[(*it).second]) {
                Insert(heap, *it);
            }
        }
    }

    return answer;
}

/*
3
3 5 4
4
0 1 2 3
3
1 2 0
*/

void solve(){
     int n1, n2, n3;
    cin>>n1;int A1[n1];
    for(int i=0;i<n1;i++) {
        cin>>A1[i];
    }
    cin>>n2;int A2[n2];
    for(int i=0;i<n2;i++) {
        cin>>A2[i];
    }
    cin>>n3;int A3[n3];
    for(int i=0;i<n3;i++) {
        cin>>A3[i];
    }

    for(int i=1;i<n2;i++) {
        for(int j = A2[i-1];j < A2[i];j++) {
            graph[i-1].push_back(make_pair(A1[j], A3[j]));
        }
    }

    cout<<"Minimum Cost Spanning Tree: "<<PrimsMST(graph);
}

int main()
{

   solve();
    return 0;
}
