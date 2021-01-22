#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#define nullptr NULL
using namespace std;
typedef struct node
{
    int x;
    int y;
    struct node* parent;
    int visited;
    int blocked;/*0 Open *1 Blocked */
} node;
node* create(int x)
{
    node *c=(node*)malloc(sizeof(node));
    c->visited=0;
    c->parent=NULL;
    c->blocked=x;
    return c;
}
typedef struct way
{
    int x;
    int y;
} way;

int CanI (node*t)
{
    if(t->blocked ==1 || t->visited ==1  )
        return 0;
    else
        return 1;

}
bool hasLeft (vector<vector<node*> > tree,node*t)
{  int m=t->x;
        int n=t->y;
    if(n-1<0 )
  return 0;
   else
    {if(CanI(tree[m][n-1]))
    return 1;
    else return 0;
}
}
bool hasRight (vector<vector<node*> > tree,node*t)
{ int we=tree.size()-1;
int m=t->x;
        int n=t->y;
    if(n+1>we)
       return 0;
       else {
       if(CanI(tree[m][n+1]))
    return 1;
    else
        return 0;}
}

bool hasNorth (vector<vector<node*> > tree,node*t)
{
int m=t->x;
        int n=t->y;
    if( m-1 <0 )
      return 0;
      else{
       if(CanI(tree[m-1][n]) )
    return 1;
    else return 0;
}}

bool hasSouth (vector<vector<node*> > tree,node*t)
{
    int we=tree.size()-1;
int m=t->x;
        int n=t->y;
    if( m+1 >we)
       return 0;
       else
            {if(CanI(tree[m+1][n]))
    return 1;
    else return 0;
}
}
    node* treeing(vector<vector<node*> > tree)
    {
        stack <node*> s;
        for(int i=0; i<tree.size(); i++)
        {
            int j=0;
            while(j!=tree.size())
            {
                tree[i][j]->x=i;
                tree[i][j]->y=j;
                j++;
            }
        }
            s.push(tree[0][0]);
            tree[0][0]->visited=1;
            while(!s.empty())
        {
            if(hasLeft(tree,s.top()) || hasRight(tree,s.top()) || hasNorth(tree,s.top())|| hasSouth(tree,s.top()))
            {
                int m=s.top()->x;
        int n=s.top()->y;
        s.pop();
            if(hasLeft(tree,tree[m][n]))
           {s.push(tree[m][n-1]);
             tree[m][n-1]->parent=tree[m][n];
             tree[m][n-1]->visited=1;

             }

        if(hasRight(tree,tree[m][n]))
           {s.push(tree[m][n+1]);
             tree[m][n+1]->parent=tree[m][n];
             tree[m][n+1]->visited=1;

             }
             if(hasNorth(tree,tree[m][n]))
          {s.push(tree[m-1][n]);
             tree[m-1][n]->parent=tree[m][n];
             tree[m-1][n]->visited=1;

             }
             if(hasSouth(tree,tree[m][n]))
       {s.push(tree[m+1][n]);
             tree[m+1][n]->parent=tree[m][n];
           tree[m+1][n]->visited=1;

             }}
        else
            s.pop();

    }
    return tree[tree.size()-1][tree.size()-1];
    }


 void printTrack(node*re)
 {
vector<way> Final;
way ay;
while(re->parent!=NULL)
    { ay.x=re->x;
    ay.y=re->y;
    re=re->parent;
    Final.push_back(ay);
        }
        ay.x=re->x;
    ay.y=re->y;
    re=re->parent;
    Final.push_back(ay);


        reverse(Final.begin(),Final.end());
        cout<<"||-";
        for(int e=0;e<Final.size();e++)
            cout<<"("<<Final[e].x<<","<<Final[e].y<<")-";
                    cout<<"||";


 }
void readfromfile(char *fileName)
{
    ifstream file;
    file.open(fileName);
    int n,x;
    file>>x;
    vector<vector<node*> > vect( x, vector<node*> (x));
    for(int i=0; i<x; i++)
    {
        int j=0;
        while(j!=x)
        {
            file>>n ;
            vect[i][j]=create(n);
            j++;
        }
    }
    file.close();

    cout<<"The Maze\n";
    for(int i=0; i<x; i++)
    {
        int j=0;
        while(j!=x)
        { cout<<"  "<<vect[i][j]->blocked<<"  ";
j++;
        }
        cout<<"\n";
    }
            cout<<"------------------------------\n";



     if(vect[0][0]->blocked==0 && vect[vect.size()-1][vect.size()-1]->blocked==0 )
{node* l =treeing(vect);
cout<<"The Solution\n";
       if(l->parent!=NULL)
            printTrack(l);
       else
        cout<<"The Maze doesn't have a solution.\n";

}
else
cout<<"The Maze can't be solved.Check Starting and Ending Position.\n";


}
    int main()
    {  readfromfile("test.txt");
return 0;
    }
