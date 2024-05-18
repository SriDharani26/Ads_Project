#include<iostream>
#include<bits/stdc++.h>
using namespace std;

#define INF 999

struct Card {
    int value;
    char symbol;
};

class vertex {
public:
    Card card; 
    vector<pair<vertex*, int>> wadj; 
    bool visited;

    vertex(int s, char c) : card{ s, c }, visited(false) {}
};

class Graph {
public:
    int n;
    vector<vertex*> graph;

    Graph() : n(0) {}

    ~Graph() {
        for (auto v : graph) {
            delete v;
        }
    }

    void ivertex(Card c) {
        vertex* v = new vertex(c.value, c.symbol);
        graph.push_back(v);
        n++;
    }

    void printvertex(){
        for(auto i:graph){
            cout<<i->card.symbol<<" "<<i->card.value<<endl;
        }
    }
};

int main() {
    Graph g;

    g.ivertex({1,'a'});
    g.ivertex({1,'a'});
    g.ivertex({1,'a'});

    g.printvertex();


    return 0;
}
