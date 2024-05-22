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

        vertex* adjvertex(vertex* u){
        for(auto& i : u->wadj){
            if(!i.first->card.visit && i.second==1){
                i.first->card.visit = true;
                return i.first;
            }
        }
        return nullptr;
    }

    vertex* adjvertexdum(vertex* u){
        for(auto& i : u->wadj){
            if(!i.first->card.visit && i.second==0){
                i.first->card.visit = true;
                return i.first;
            }
        }
        return nullptr;
    }

    int checkrum(){
        set<vertex*> newmain;
        set<vertex*> newmain1;
        int count=0;
        int count1=0;
        for(auto i : graph){
            if(!i->card.visit){
                vector<vertex*> mainset;
                vertex* k = i;
                k->card.visit = true;
                mainset.push_back(k);
                k = adjvertex(k);
                while(k && (k->card.symbol == mainset[0]->card.symbol || k->card.value == mainset[0]->card.value)){
                    mainset.push_back(k);
                    k = adjvertex(k);
                }
                if(mainset.size() == 3 || mainset.size() == 4){
                    for(auto k : mainset){
                        cout << k->card.symbol << k->card.value << " ";

                    }
                    count+=1;
                    cout << endl;
                } else {
                    for(auto k : mainset){
                        newmain.insert(k);
                        k->card.visit = false;
                    }
                }
            }
        }
        cout<<"Main set count : "<<count<<endl;
        cout << "Remaining cards in newmain:" << endl;
        for(auto i : newmain){
            cout << i->card.symbol << i->card.value << " ";
        }

        cout << endl;
        for(auto i:newmain){
            if(!i->card.visit){
                vector<vertex*> mainset1;
                vertex* k = i;
                k->card.visit = true;
                mainset1.push_back(k);
                k = adjvertexdum(k);
                while(k && (k->card.symbol == mainset1[0]->card.symbol || k->card.value == mainset1[0]->card.value)){
                    mainset1.push_back(k);
                    k = adjvertexdum(k);
                }
                if(mainset1.size() == 3 || mainset1.size() == 4){
                    for(auto k : mainset1){
                        cout << k->card.symbol << k->card.value << " ";
                    }
                    count1+=1;
                    cout << endl;
                } else {
                    for(auto k : mainset1){
                        newmain1.insert(k);
                        k->card.visit = false;
                    }
                }
            }
        }
        cout<<"Dummy set count : "<<count1<<endl;
        cout << "Remaining cards in newmain:" << endl;
        for(auto i : newmain1){

            cout << i->card.symbol << i->card.value << " ";
        }

        
        return count1+count;
    }


     int checkrum1(){
        set<vertex*> newmain;
        set<vertex*> newmain1;
        int count=0;
        int count1=0;
        for(auto i : graph){
            if(!i->card.visit){
                vector<vertex*> mainset;
                vertex* k = i;
                k->card.visit = true;
                mainset.push_back(k);
                k = adjvertex(k);
                while(k && (k->card.symbol == mainset[0]->card.symbol || k->card.value == mainset[0]->card.value)){
                    mainset.push_back(k);
                    k = adjvertex(k);
                }
                if(mainset.size() == 3 || mainset.size() == 4){
                    // for(auto k : mainset){
                    //     cout << k->card.symbol << k->card.value << " ";

                    // }
                    count+=1;
                    // cout << endl;
                } else {
                    for(auto k : mainset){
                        newmain.insert(k);
                        k->card.visit = false;
                    }
                }
            }
        }
        // cout<<"Main set count : "<<count<<endl;
        // cout << "Remaining cards in newmain:" << endl;
        // for(auto i : newmain){
        //     cout << i->card.symbol << i->card.value << " ";
        // }

        cout << endl;
        for(auto i:newmain){
            if(!i->card.visit){
                vector<vertex*> mainset1;
                vertex* k = i;
                k->card.visit = true;
                mainset1.push_back(k);
                k = adjvertexdum(k);
                while(k && (k->card.symbol == mainset1[0]->card.symbol || k->card.value == mainset1[0]->card.value)){
                    mainset1.push_back(k);
                    k = adjvertexdum(k);
                }
                if(mainset1.size() == 3 || mainset1.size() == 4){
                    // for(auto k : mainset1){
                    //     cout << k->card.symbol << k->card.value << " ";
                    // }
                    count1+=1;
                    // cout << endl;
                } else {
                    for(auto k : mainset1){
                        newmain1.insert(k);
                        k->card.visit = false;
                    }
                }
            }
        }
        // cout<<"Dummy set count : "<<count1<<endl;
        // cout << "Remaining cards in newmain:" << endl;
        // for(auto i : newmain1){

        //     cout << i->card.symbol << i->card.value << " ";
        // }

        
        return count1+count;
    }
};

void checkreplacement(vector<string> set1,int k,Graph g){
        vector<string> set2;
        string deckcard;
        Graph g1[13];
        
        cout<<"Enter the deck card :";
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
            
            int y=g1[i].checkrum1();
            
            if(y>k){
                cout<<"Replace :"<<oldval<<oldnum<<endl;
                return ;
            }
            else if(y<k){
                cout<<"Don't replace :"<<oldval<<oldnum<<endl;
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
    cout<<endl<<"Enter the choice:";
    cin>>choice;
    ifstream card("cards.txt");
    string value;
    vector<string> set1;

  
    int c = 0;
    while(card >> value && c < 13 ){
        
            set1.push_back(value);
            c++;
    }
    
    Graph g1;
    int k;
    while(1){
        if(choice==1){
            cout<<"***Rules***"<<endl;
            ifstream rule("rules.txt");
            string line;
            while (getline(rule,line)) {
        
                cout<<line<<endl;
            }
            cout<<endl<<"Enter the choice:";
            cin>>choice;
        }
        else if(choice==2){
            sort(set1.begin(), set1.end()); 
   
            for(auto deck : set1){
                cout << deck << " ";
                char suit = deck[0];
                int value = stoi(deck.substr(1));
                g1.ivertex({value, suit});
            }
            cout << endl;
            g1.addedge();
            k=g1.checkrum();
            cout<<"No of sets formed  :"<<k<<endl;
                
            if(k!=4){
                    cout<<"rummy not formed formed"<<endl;
                }
                else{
                    cout<<"rummy formed"<<endl;
                }
                cout<<endl<<"Enter the choice:";
                cin>>choice;
            }
        else if(choice==3){
            if(k!=4){
                checkreplacement(set1,k,g1);
                cout<<endl<<"Enter the choice:";
                cin>>choice;
            }
            else{
                cout<<"rummy formed"<<endl;
                cout<<endl<<"Enter the choice:";
                cin>>choice;
            }
            
        }
        else if(choice ==4){
            cout<<"Exiting...";
            return 0;
        }
        else{
            cout<<"Entered the wrong choice"<<endl;
            cout<<endl<<"Enter the choice:"<<endl;
            cin>>choice;
        }
    }
    

    
    return 0;
}