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


    int checkrum(){
        for(auto i:graph){
            i->card.visit=false;
        }
        Card narr[13];
        int n=0;
        queue<vertex*> q;
        for(auto i:graph){
            
            if(!i->card.visit){
                i->card.visit=true;
                     narr[n++]=i->card; 

            for(auto  j:i->wadj){
                if(!j.first->card.visit){
                    if(i->card.symbol==j.first->card.symbol && abs(i->card.value-j.first->card.value)==1){
                    narr[n++]=j.first->card; 
                    j.first->card.visit=true;

                }
            }
            }
           
            }
        }
        int count=0;
        int main=0;
        for(int i=0;i<12;i++){
            cout<<narr[i].symbol<<narr[i].value<<" ";
            if(narr[i].symbol==narr[i+1].symbol){

                if(abs(narr[i].value-narr[i+1].value)==1){
                    count+=1;
                    if((count%3)==0||(count%4)==0){
                        count=0;
                        main+=1;
                    }   
                }
            }
            
        }
        return main;
      
    
    }
    int checkdum(){
        // for(auto i:graph){
        //     i->card.visit=false;
        // }
        Card narr[13];
        int n=0,s=0;
        queue<vertex*> q;
        for(auto i:graph){
            
            if(!i->card.visit){
                    i->card.visit=true;
                    narr[n++]=i->card; 
                 //   cout<<i->card.symbol<<i->card.value<<endl;
                for(auto  j:i->wadj){
                    if(!j.first->card.visit){
                         
                        if(i->card.value==j.first->card.value && i->card.symbol!=j.first->card.symbol){
                            narr[n++]=j.first->card; 
        
                            j.first->card.visit=true;

                        }

                    }
                }
           
            }
        }
        int count=0;
        int dum=0;
        for(int i=0;i<13;i++){
            cout<<narr[i].symbol<<narr[i].value<<" ";
            if(narr[i].value==narr[i+1].value){
                count+=1;
                if((count%3)==0||(count%4)==0){
                    count=0;
                    dum+=1;
                }   
            }
        }
        cout<<endl;
      return dum;
 
    }

    void rummy(){
        int k=checkdum();
        int l=checkrum();
        if(l>1){
             if(l+k==4){
                cout<<"Total sets :"<<l+k<<endl;

                cout<<"You deck is rummy"<<endl;
            }
            else{
                cout<<"Total sets :"<<l+k<<endl;
                cout<<"You deck is not rummy"<<endl;
            }
        }
        else{
                cout<<"Total sets :"<<l+k<<endl;
                cout<<"You deck is not rummy becase there is no main set"<<endl;
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
     g.rummy();
    return 0;
}
