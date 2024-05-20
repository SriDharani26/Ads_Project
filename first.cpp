#include<iostream>
#include<bits/stdc++.h>
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

    bool ismain(vector<vertex*>& set) {
        if (set.size() < 3) return false;
        sort(set.begin(), set.end());
        
        for (int i = 1; i < set.size(); i++) {
            if (set[i]->card.value != set[i-1]->card.value + 1) {
                return false;
            }
        }
        return true;
    }

    void nearest(vertex * v,int count){
        
        // cout<<v->card.symbol<<v->card.value<<endl;

       
        for(auto i:v->wadj){
            
            if(!i.first->card.visit){
                if(i.second==1){
                    cout<<i.first->card.symbol<<i.first->card.value<<" ";
                    i.first->card.visit=true;
                    count+=1;
                     if(count==3 || count ==4){
                        cout<<"one rummy is created"<<endl;
                        count=0;
                    }
                    else{
                        
                        cout<<endl;
                    }
                    nearest(i.first,count);
                    
                }
                else{
                    // cout<<i.first->card.symbol<<i.first->card.value<<"is changed to false"<<endl;
                    i.first->card.visit=false;
                }
               
            }
        }
        
    }

    void dummy(vertex *v,int count){
        // cout<<v->card.symbol<<v->card.value<<endl;
        for(auto i:v->wadj){
            
            if(!i.first->card.visit){
                if(i.second==0){
                    cout<<i.first->card.symbol<<i.first->card.value<<" ";
                    
                    count+=1;
                     if(count==3 || count ==4){
                        cout<<"one dummy rummy is created"<<endl;
                        count=1;
                    }
                    else{
                        
                        cout<<endl;
                    }
                    nearest(i.first,count);
                    i.first->card.visit=true;
                }
                else{
                    i.first->card.visit=false;
                }
            }
        }
    }
    void checkrum(){
        for(auto i:graph){
            
            if(!i->card.visit){
                nearest(i,0);
            }
            
        }
        for(auto i:graph){
            
            if(!i->card.visit){
                // cout<<"Unvisited node";
                // cout<<i->card.symbol<<""<<i->card.value<<" ";
                dummy(i,0);
            }
        }
    }

};


int main() {
    Graph g;
    g.ivertex({10,'d'});
    g.ivertex({11,'h'});
    g.ivertex({12,'h'});
    g.ivertex({13,'h'});
    g.ivertex({4,'s'});
    g.ivertex({5,'s'});
    g.ivertex({6,'s'});
    g.ivertex({7,'s'});
    
    g.ivertex({2,'c'});
    g.ivertex({3,'c'});
    g.ivertex({4,'c'});
    g.ivertex({10,'s'});
    g.ivertex({10,'c'});

    g.addedge();
    g.printadj();

    g.checkrum();
    return 0;
}