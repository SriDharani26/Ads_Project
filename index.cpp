#include<iostream>
#include<bits/stdc++.h>
#include <fstream>
using namespace std;

#define INF 999

struct Card {
    int value;
    char symbol;
    bool visit;
};

class vertex {
public:
    Card card; 
    vector<pair<vertex*, int>> wadj; 
    


    vertex(int s, char c) : card{ s, c, false} {}
};

class Graph {
public:
    int n;
    int m_sets=0,d_sets=0;
    vector<vertex*> graph;
    vector<vertex*> newset;
    
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
                    if(graph[i]->card.symbol==graph[j]->card.symbol && abs(graph[i]->card.value-graph[j]->card.value)==1){
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

    void remove(vertex * u){
        for(auto i:graph){
            if(i==u){
                delete u;
            }
        }
    }
    vertex * adjvertex(vertex *u){
        for(auto i:u->wadj){
            if(i.second==1 && i.first->card.visit!=true){
                i.first->card.visit=true;
                return i.first;
            }
            
        }
        return u;
    }
    void checkrum(){
        vector<vertex*> mainset;
        vector<vertex*> newmain;
        for(auto i:graph){
            if(i->card.visit!=true){
                vertex *k;
                i->card.visit=true;
                mainset.push_back(i);
                k=adjvertex(i);
                while((k->card.symbol!=i->card.symbol || k->card.value!=i->card.value)){
                    k->card.visit=true;
                    mainset.push_back(k);
                    i=k;
                    vertex *y=adjvertex(k);  
                    k=y;
                }
                cout<<"Size of "<<mainset.size()<<endl;
                if(mainset.size()==3|| mainset.size()==4){
                    for(auto k:mainset){
                        cout<<k->card.symbol<<k->card.value<<" ";
                    }
                    mainset.clear();
                }
                else{
                    for(auto k:mainset){
                        newmain.push_back(k);
                        k->card.visit=false;
                    }
                    mainset.clear();
                    
                }
            }

            for(auto i:newmain){
                cout<<i->card.symbol<<i->card.value<<" ";
            }
        }
            
    }

};


int main() {
    Graph g;
    ifstream card("cards.txt");
    string value;
    vector<string> set1;
    vector<string> set2;
    vector<string> set3;
    vector<string> set4;
    int c=1;
    while(card>>value && c<14){
        set1.push_back(value);
        c++; 
    }

    
    sort(set1.begin(), set1.end()); 
    for(auto deck:set1){
        cout<<deck<<" ";
        char suit = deck[0];

        int value = stoi(deck.substr(1));
        g.ivertex({value,suit});
    }
    cout<<endl;
    

    g.addedge();
    g.printadj();

    g.checkrum();
 
    return 0;
}