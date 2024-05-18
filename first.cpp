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

    void addedge(){
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    if(graph[i]->card.symbol==graph[j]->card.symbol){
                        graph[i]->wadj.push_back(make_pair(graph[j],abs(graph[i]->card.value-graph[j]->card.value)));
                    }
                    if(graph[i]->card.value==graph[j]->card.value){
                        graph[i]->wadj.push_back(make_pair(graph[j],abs(graph[i]->card.value-graph[j]->card.value)));
                    }
                }
            }
        }
    }


    void printadj(){
        for(auto i:graph){
            cout<<i->card.symbol<<i->card.value<<"->";
            for(auto j:i->wadj){
                cout<<j.first->card.symbol<<j.first->card.value<<" "<<j.second<<" ";
            }
            cout<<endl;
        }
    }


   


};


int main() {
    Graph g;

    g.ivertex({11,'h'});
    g.ivertex({12,'h'});
    g.ivertex({13,'h'});
    g.ivertex({4,'s'});
    g.ivertex({5,'s'});
    g.ivertex({6,'s'});
    g.ivertex({7,'s'});
    g.ivertex({1,'c'});
    g.ivertex({2,'c'});
    g.ivertex({3,'c'});
    g.ivertex({8,'s'});
    g.ivertex({9,'s'});
    g.ivertex({10,'s'});

    g.addedge();
    g.printadj();


    return 0;
}
