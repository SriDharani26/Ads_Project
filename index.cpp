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

        void nearest(vertex* v, int& count){  
            //  v->card.visit=true;
            
            for(auto i : v->wadj){    
                if(!i.first->card.visit && i.second == 1){
                    cout << i.first->card.symbol << i.first->card.value << " ";
                    i.first->card.visit = true;
                   
                    count++;
                    if(count == 3 || count == 4){
                        
                        cout << "one rummy is created" << endl;
                        m_sets+=1;
                        count = 0;
                    }
                    else {
                        cout << endl;
                    }
                    nearest(i.first, count);
                    
                }
            }
    }

    void dummy(vertex* v, int& count){
       
        for(auto i : v->wadj){
            if(!i.first->card.visit && abs (i.first->card.value - v->card.value)== 0){
                i.first->card.visit = true;
                cout << i.first->card.symbol << i.first->card.value << " ";
                count++;
                if(count == 3 || count == 4){
                    cout << "one dummy rummy is created" << endl;
                    d_sets+=1;
                    count = 0;
                }
                else {
                    cout << endl;
                }
                
                

                dummy(i.first, count);
            }
        }
    }



    void checkrum(){
        for(auto i : graph){
            if(!i->card.visit){
                int count = 0;
                nearest(i, count);
                cout << endl;
            }
        }

        for(auto i : graph){
            if(!i->card.visit){
                int count = 0;
                dummy(i, count);
                cout << endl;
            }
        }
        for(auto i : graph){
            if(!i->card.visit){
                cout << "Unvisited node ";
                cout << i->card.symbol << i->card.value << " ";
                cout << endl;
            }
        }
    }

    void rummycheck(){
        if(m_sets>1){
            if(m_sets+d_sets==4){
                cout<<"rummy formed"<<endl;
            }
            else{
                cout<<"rummy not formed"<<endl;
            }
        }
        else{
            cout<<"rummy not formed"<<endl;
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
    g.rummycheck();
    return 0;
}