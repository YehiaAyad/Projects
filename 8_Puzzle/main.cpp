#include <iostream>
#include <bits/stdc++.h>
#include<time.h>
using namespace std;

typedef struct node // Node for storing the states and the parent of each state
{
    string maze;
    struct node* parent;
} node;

node* create(string x) // creating a new state
{
node *c=(node*)malloc(sizeof(node));
   c->maze=x;
    c->parent=NULL;
    return c;
}
string swap (string x,int i, int j) // swap function used to swap 2 char in a string
{ char temp=x[j];
    x[j]=x[i];
    x[i]=temp;
return x;
}

bool ideal(string puzzle)  // check if the current state is equal to goal state
{  string ideal="012345678";
    if(puzzle==ideal)
        return true;
    else
        return false;
}
int heu(string puzzle,int x) // calculate the heuristic ,int x to choose either Manhattan or Euclidean
{ int man=0;
 int eud=0;
 int r,c;
vector<vector<int>> state (3,vector<int> (3));
int m=0;
 for(int i=0; i<3; i++)
    {int j=0;
        while(j!=3)
        { int num = puzzle[m]-48;
        m++;
        state[i][j]=num;
            j++;}}

    for(int i=0;i<state.size();i++)
     for(int j=0;j<state.size();j++)
        {

        if(state[i][j]!=0)
    { c=state[i][j]%3;
    if(state[i][j]<3)
        r=0;
    else if(state[i][j]>5)
        r=2;
    else
        r=1;

        man+= abs(r-i)+abs(c-j);
        eud+=sqrt(pow(r-i,2)+pow(c-j,2));

    }
    }
if(x==0)
    return man;
else return eud;
}

 vector<string> children ( string puzzle,int x) // Function that return the children of the current state with priority of [UP,DOWN,LEFT,RIGHT]
 { vector<string> child;
//Vertical Children [UP,DOWN]
if(x<3)
child.push_back(swap(puzzle,x,x+3));
else if(x>5)
        child.push_back(swap(puzzle,x,x-3));
         else
        { child.push_back(swap(puzzle,x,x-3));
     child.push_back(swap(puzzle,x,x+3));

        }
 //Horizontal Children [LEFT,RIGHT]
 switch (x%3)
 {
       case 0: {
           child.push_back(swap(puzzle,x,x+1));
               break;}

       case 1: {
           child.push_back(swap(puzzle,x,x-1));
               child.push_back(swap(puzzle,x,x+1));
               break;}

       case 2: {
           child.push_back(swap(puzzle,x,x-1));
               break;}
   }

return child;
 }


void prints(string p) //Prints the state of the puzzle in the form of 3x3 vector
{ int j=0;
for(int i=0;i<p.size();i++)
{if(p[i]=='0')
        cout<<"["<<" "<<"] ";
        else
        cout<<" "<<p[i]<<"  ";
    if(j==2||j==5)
        cout<<"\n";
j++;
}
cout<<"\n";
}

int found(string puzzle) //Gets the index of the blank space ( 0 ) in the puzzle
{ return puzzle.find("0");
}

pair<node*,int> bfs (string puzzle) //BFS to reach the goal , Queue and unordered map are used
{node* c=create(puzzle);
pair<node*,int>ce;
if(ideal(puzzle)){
    ce.second=0;
    ce.first=c;
    return ce;
}
int nodes_expanded=0;
 int k=0;
unordered_map<string,int>visit;
    queue <node*> q;
    q.push(c);
     visit.insert(make_pair(c->maze,k++));
     vector<string> child;
while(!q.empty())
{ child=children(q.front()->maze,found(q.front()->maze));

for(int i=0;i<child.size();i++)
{if(visit.find(child[i]) == visit.end())
    {visit.insert(make_pair(child[i],k++));
node*w=create(child[i]);
   w->parent=q.front();
 q.push(w);}}
q.pop();
 nodes_expanded++;
if(ideal(q.front()->maze))
   {ce.first=q.front();
    ce.second=nodes_expanded;
return ce;}}}


pair<node*,int> dfs (string puzzle) //DFS to reach goal ,Stack and unordered map are used
{node* c=create(puzzle);
pair<node*,int>ce;
if(ideal(puzzle)){
    ce.second=0;
    ce.first=c;
    return ce;
}
 int k=0;
unordered_map<string,int>visit;
    stack <node*> s;
    s.push(c);
     visit.insert(make_pair(c->maze,k++));
     vector<string> child;
int nodes_expanded=0;
while(!s.empty())
{ node*t=create(s.top()->maze);
t->parent=s.top()->parent;
child=children(s.top()->maze,found(s.top()->maze));
reverse(child.begin(),child.end());
if(ideal(s.top()->maze))
       {ce.first=s.top();
        ce.second=nodes_expanded;

        return ce;
       }
s.pop();
nodes_expanded++;
for(int i=0;i<child.size();i++)
{
    if(visit.find(child[i]) == visit.end())
    {
        visit.insert(make_pair(child[i],k++));
node*w=create(child[i]);
   w->parent=t;
 s.push(w);

 /*if(ideal(s.top()->maze))
       {ce.first=s.top();
        ce.second=nodes_expanded;

        return ce;

    }*/

}

}

}
}

struct comparemarks  //Used to adjust the sequence of priority queue
{
   bool operator()(pair<int,node*> const &s1, pair<int,node*> const& s2)
   {
      return s2.first < s1.first;
   }
};

pair<node*,int> Astar (string puzzle,int b) //A* Search to reach goal, Priority queue and 2 unordered maps are used
{node* c=create(puzzle);                   // , int b to choose either Manhattan or Euclidean
pair<node*,int>ce;
if(ideal(puzzle)){
    ce.second=0;
    ce.first=c;
    return ce;
}
int nodes_expanded=0;
 int k=0;
 int v=0;
 unordered_map<string,int>cost;
unordered_map<string,int>visit;
priority_queue<pair<int,node*>,vector <pair<int,node*>>,comparemarks> pqueue;
int f=k+heu(c->maze,b);
cost.insert(make_pair(c->maze,f));
    pqueue.push(make_pair(f,c));
     vector<string> child;
while(!pqueue.empty())
{ int z=1;
    while(z)
     {if(visit.find(pqueue.top().second->maze) == visit.end())
    {visit.insert(make_pair(pqueue.top().second->maze,k++));
z=0;
}
 else
    {  pqueue.pop();
        child.clear();
}}
node*t=create(pqueue.top().second->maze);
t->parent=pqueue.top().second->parent;
    child=children(pqueue.top().second->maze,found(pqueue.top().second->maze));
   pqueue.pop();
   nodes_expanded++;

for(int i=0;i<child.size();i++)
{if(visit.find(child[i]) == visit.end())
 {if(cost.find(child[i]) == cost.end())
   {int f=heu(child[i],b)+1+cost[t->maze]-heu(t->maze,b);
       cost.insert(make_pair(child[i],f));
node*w=create(child[i]);
   w->parent=t;
 pqueue.push(make_pair(cost[child[i]],w));
}
 else{if(cost[child[i]]>heu(child[i],b)+1+cost[t->maze]-heu(t->maze,b))
            {cost[child[i]]=heu(child[i],b)+1+cost[t->maze]-heu(t->maze,b);
               node*w=create(child[i]);
               w->parent=t;

                pqueue.push(make_pair(cost[child[i]],w));}

                }}
                }

if(ideal(pqueue.top().second->maze))
   { ce.first=pqueue.top().second;
    ce.second=visit.size();

    return ce;}}}

string dir(int q,int w) //Function that returns the direction of the change between 2 states
    { string k;
    switch (w-q)
{case 3:
    {
        k="DOWN";
        break;
    }
    case -3:
    {
       k="UP";
        break;
    }
    case 1:
    {
        k="RIGHT";
        break;
    }
    case -1:
    {
        k="LEFT";
        break;
    }}
      return k;}



 pair<int,int> showinfo (pair<node*,int>ce,int x, int y) //Function that prints the information about the 4 types of searches
 { vector<string> Final;                                 // int x chooses to see full route or just information about it
string ay;                                               // int y chooses which type of search to view
while(ce.first->parent!=NULL)
    {
    ay=ce.first->maze;
    ce.first=ce.first->parent;
    Final.push_back(ay);
        }
        ay=ce.first->maze;
    ce.first=ce.first->parent;
    Final.push_back(ay);
pair<int,int>acc;
acc.first=0;
acc.second=0;
        reverse(Final.begin(),Final.end());
        if(ideal(Final[0]))
           {
               cout<<"The starting node is already the goal state.\n";
        return make_pair(0,0);
           }
if(x==1)
        {
          int e=0;
          int q,w;
          string k="Beginning State";
            for(e;e<Final.size()-1;e++)
            {
if(e>=1)
{q=found(Final[e-1]);
w=found(Final[e]);
k=dir(q,w);
}
                cout<<"Step "<<e<<":["<<k<<"]\n";
            prints(Final[e]);
                    cout<<" ||  \n \\/  \n";}
    q=found(Final[e-1]);
w=found(Final[e]);
k=dir(q,w);
        cout<<"Step "<<e<<":["<<k<<"] [GOAL STATE]\n";
                    prints(Final[e]);

   cout << "------------------------------------\n";      }

else { string q;
        if(y==1)
        q="BFS";
else if(y==2)
    q="DFS";
else if(y==3)
    {q="A* using Manhattan Heuristic";
    acc.first=Final.size()-1;
acc.second=ce.second;}
else if(y==4)
    {q="A* using Euclidean Heuristic";
    acc.first=Final.size()-1;
acc.second=ce.second;
    }
cout<<"The cost by "<<q<<" is "<< Final.size()-1<<".\n" ;
cout<<"The number of expanded nodes by "<<q<<" is "<<ce.second<<".\n" ;
if(Final.size()<25)
{
     cout<<"The Path is [ " ;
     for(int e=0;e<Final.size()-1;e++)
{
    int q,w;
q=found(Final[e]);
w=found(Final[e+1]);
string t=dir(q,w);
cout<<t<<" ";
}
cout<<"].\n";
}}
return acc;
 }

bool solvable(string puzzle)  //Check if puzzle has a solution
{ int inv=0;
   int f=found(puzzle);
   puzzle.erase(puzzle.begin()+f);
  for(int i=0;i<puzzle.size();i++)
   { for(int j=i+1;j<puzzle.size();j++)
       if(puzzle[j]<puzzle[i])
        inv++;
   }


if(inv%2==0)
                return 1;
            else
            return 0;

}

bool valid(string puzzle)  //Check if the puzzle is a valid puzzle
{ sort(puzzle.begin(),puzzle.end());
    string ideal="012345678";
if(puzzle==ideal)
        return true;
   else return false;

}

int main()
{
 string puzzle;
pair<int,int>o,p;
    cout << "Welcome to the 8 Puzzle Solver!\n------------------------------------\nEnter Your Puzzle in form of 3x3 vector separated by spaces.(Represent the space by 0 or X):\n";
   while(1){
        for(int j=0;j<9;j++)
    { char n;
        cin>>n;
        if(n=='x'||n=='X')
            n='0';
    puzzle.push_back(n);

    }
    cout << "------------------------------------\n";

    if(!valid(puzzle))
 {cout<<"This puzzle isn't valid.\n";
 cout << "------------------------------------\n";
 }
 else if(!solvable(puzzle))
 {cout<<"This puzzle doesn't have a solution.\n";
 cout << "------------------------------------\n";
 }
else
{
    clock_t t=clock(); // Function to get the running time

showinfo(bfs(puzzle),0,1);
    t=clock()-t;
    cout<<((double)t)/CLOCKS_PER_SEC<<" Seconds to find solution using BFS.\n";
    cout << "------------------------------------\n";

 t=clock();

showinfo(dfs(puzzle),0,2);
    t=clock()-t;
    cout<<((double)t)/CLOCKS_PER_SEC<<" Seconds to find solution using DFS.\n";
    cout << "------------------------------------\n";

    t=clock();
o=showinfo(Astar(puzzle,0),0,3);
    t=clock()-t;
    cout<<((double)t)/CLOCKS_PER_SEC<<" Seconds to find solution using A* using the Manhattan Heuristic.\n";
    cout << "------------------------------------\n";

    t=clock();
p=showinfo(Astar(puzzle,1),0,4);
    t=clock()-t;
    cout<<((double)t)/CLOCKS_PER_SEC<<" Seconds to find solution using A* using the Euclidean Heuristic.\n";
    cout << "------------------------------------\n";
if(o.first<p.first)
    cout<<"The Manhattan Heuristic is more admissible as it has a lower cost.\n";
else if(o.second<p.second)
        cout<<"The Manhattan Heuristic is more admissible as it has a lower number of expanded nodes.\n";
else
    cout<<"In this case, both Heuristics have similar performance.\n";
cout << "------------------------------------\n";
while(1){
cout<<"Which path do you want to see?\n1-BFS\n2-DFS\n3-A* using the Manhattan Heuristic\n4-A* using the Euclidean Heuristic\n5-None\n";
int c;
cin>>c;
if(c==5)
    break;
switch (c){
case 1: { cout << "------------------------------------\n";
cout<<"BFS:\n";
          showinfo(bfs(puzzle),1,1);
               break;}
case 2:{ cout << "------------------------------------\n";
cout<<"DFS:\n";
    showinfo(dfs(puzzle),1,2);
               break;}
case 3:{ cout << "------------------------------------\n";
cout<<"A* using the Manhattan Heuristic:\n";
    showinfo(Astar(puzzle,0),1,3);
               break;}
case 4:{ cout << "------------------------------------\n";
cout<<"A* using the Euclidean Heuristic:\n";
    showinfo(Astar(puzzle,1),1,4);
               break;}



      default: break;
   }
}
}

cout<<"Do you want to solve another puzzle?\n1-Yes\n2-NO\n";
int we;
cin>>we;
if(we==2)
    break;
    else
        cout<<"Enter your puzzle:\n";
    puzzle.erase();

}
cout<<"<3 <3 Thank You For Playing <3 <3";
    return 0;
}


