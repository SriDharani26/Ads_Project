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
                    // cout << i.first->card.symbol << i.first->card.value << " ";
                    i.first->card.visit = true;
                   
                    count++;
                    if(count == 3 || count == 4){
                        
                        // cout << "one rummy is created" << endl;
                        m_sets+=1;
                        count = 0;
                    }
                    // else {
                    //     cout << endl;
                    // }
                    nearest(i.first, count);
                    
                }
            }
    }

    void dummy(vertex* v, int& count){
       
        for(auto i : v->wadj){
            if(!i.first->card.visit && abs (i.first->card.value - v->card.value)== 0){
                i.first->card.visit = true;
                // cout << i.first->card.symbol << i.first->card.value << " ";
                count++;
                if(count == 3 || count == 4){
                    // cout << "one dummy rummy is created" << endl;
                    d_sets+=1;
                    count = 0;
                }
                // else {
                //     cout << endl;
                // }
                
                

                dummy(i.first, count);
            }
        }
    }



    void checkrum(){
        for(auto i : graph){
            if(!i->card.visit){
                int count = 0;
                nearest(i, count);
                // cout << endl;
            }
        }

        for(auto i : graph){
            if(!i->card.visit){
                int count = 0;
                dummy(i, count);
                // cout << endl;
            }
        }
        for(auto i : graph){
            if(!i->card.visit){
                // cout << "Unvisited node ";
                // cout << i->card.symbol << i->card.value << " ";
                // cout << endl;
            }
        }
    }

    int rummycheck(){
        if(m_sets>1){
            if(m_sets+d_sets==4){
                // cout<<"rummy formed"<<endl;
                return m_sets+d_sets;
            }
            else{
                // cout<<"rummy not formed"<<endl;
                return m_sets+d_sets;
            }
        }
        else{
            // cout<<"rummy not formed"<<endl;
            return m_sets+d_sets;
        }
    }

};

void checkreplacement(vector<string> set1,int k,Graph g){
        vector<string> set2;
        string deckcard;
        Graph g1[13];
        
        cout<<"Enter the deck card  :";
        cin>>deckcard;
        int count=0;
        for(int i=0;i<13;i++){
            int oldnum=g.graph[i]->card.value;
            char oldval=g.graph[i]->card.symbol;
          
            set2=set1;
            set2[i]=deckcard;
            
            sort(set2.begin(), set2.end()); 
            for(auto deck:set2){
                // cout<<deck<<" ";
                char suit = deck[0];

                int value = stoi(deck.substr(1));
                g1[i].ivertex({value,suit});
            }
            
        
            g1[i].addedge();
            g1[i].checkrum();
            int y=g1[i].rummycheck();
            
            if(y>k){
                cout<<"Replace :"<<oldnum<<oldval<<endl;
                return ;
            }
            else if(y<k){
                cout<<"Don't replace :"<<oldnum<<oldval<<endl;
                count+=1;
                
            }
            else{
                cout<<"In case no other cards are able to replace change this card :";
                cout<<oldnum<<oldval<<endl;
                count+=1;
            }
        }
        if(count==13){
            cout<<"Don't replace the cards"<<endl;
        }
}


void checkrummyformation(Graph g);


int main() {

    cout<<"-----------------------------------WELCOME TO RUMMY WORLD------------------------------------"<<endl;
    cout<<"--------------This program will give you the basic idea of how to play rummy-----------------"<<endl;
    cout<<"FEATURES:"<<endl;
    cout<<"1.Rules \n2.Check whether the set of card forms rummy or not \n3.given card set and deck card give the information--whether to replace it or not \n4.Exit"<<endl;
    int choice;
    cout<<"Enter the choice:"<<endl;
    cin>>choice;
    Graph g;
    ifstream card("cards.txt");
    string value;
    vector<string> set1;
    int k;
    int c=1;
    while(card>>value && c<13){
        set1.push_back(value);
        c++; 
    }
    while(1){
        if(choice==1){
            cout<<"1st menu"<<endl;
            cout<<"Enter the choice:"<<endl;
            cin>>choice;
        }
        else if(choice==2){
            sort(set1.begin(), set1.end()); 
            for(auto deck:set1){
                cout<<deck<<" ";
                char suit = deck[0];

                int value = stoi(deck.substr(1));
                g.ivertex({value,suit});
            }
            cout<<endl;
            

            g.addedge();

            g.checkrum();
            k=g.rummycheck();
            cout<<"No of sets formed  :"<<k<<endl;
            
            if(k!=4){
                cout<<"rummy not formed formed"<<endl;
            }
            else{
                cout<<"rummy formed"<<endl;
            }
            cout<<"Enter the choice:"<<endl;
            cin>>choice;
        }
        else if(choice==3){
            if(k!=4){
                checkreplacement(set1,k,g);
                cout<<"Enter the choice:"<<endl;
                cin>>choice;
            }
            else{
                cout<<"rummy formed"<<endl;
                cout<<"Enter the choice:"<<endl;
                cin>>choice;
            }
            
        }
        else if(choice ==4){
            cout<<"Exiting...";
            return 0;
        }
        else{
            cout<<"Entered the wrong choice"<<endl;
            cout<<"Enter the choice:"<<endl;
            cin>>choice;
        }
    }
    

    
    return 0;
}