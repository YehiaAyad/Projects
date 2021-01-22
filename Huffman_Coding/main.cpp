#include <iostream>
#include <bits/stdc++.h>
#include<time.h>
#include <bitset>
using namespace std;

typedef struct node
{
    char data;
    int freq;
    struct node* Left;
    struct node* Right;
} node;

struct comparemarks  //Used to adjust the sequence of priority queue
{
    bool operator()(node* const &s1,node* const& s2)
    {
        return s2->freq <= s1->freq;
    }
};
node* create(char x, int f) // creating a new state
{
    node *c=(node*)malloc(sizeof(node));
    c->data=x;
    c->freq=f;
    c->Left=NULL;
    c->Right=NULL;

    return c;
}
node* createM(int f) // creating a new state
{
    node *c=(node*)malloc(sizeof(node));
    c->data=NULL;
    c->freq=f;
    c->Left=NULL;
    c->Right=NULL;

    return c;
}

string intvec(vector<int>re, int t)
{
    string x;
    for(int i=0; i<t; i++)
    {
        x+=to_string(re[i]);
    }
    return x;
//stringstream geek(x);
    // int s;
    //geek>>s;
    //return s;

}

void write_tree (node*a , string &e,unordered_map<char, string>byte) {
    if(a->Left==NULL && a->Right==NULL)
      {char w=a->data;
        e+=w;
        e+=byte[w];
        e+=" ";
        }
    else {
        write_tree (a->Left,e,byte);
       write_tree (a->Right,e,byte) ;}
       }

void analyze(node*a,vector<int>&re, int t,unordered_map<char, string>&byte)
{
    if(a->Left!=NULL)
    {
        re[t]=0;
        analyze(a->Left,re,t+1,byte);
    }
    if(a->Right!=NULL)
    {
        re[t]=1;
        analyze(a->Right,re,t+1,byte);
    }

    if(a->Left==NULL && a->Right==NULL)
        byte.insert(make_pair(a->data,intvec(re,t)));

}

pair<node*,int>read_bin(char*filename)
{
    ifstream file;
    file.open(filename,ios::binary);
    unordered_map<char, int> Freq;
    unordered_set <char> All ;
    char x;
    stringstream buffer;
    buffer << file.rdbuf();
    string contents(buffer.str());
    int i=0;
    while(i<contents.size())
    { x=contents[i];
        //x=tolower(x);
        if(x!='\r')
        {if(Freq.find(x) == Freq.end())
        {
            All.insert(x);
            Freq.insert(make_pair(x,1));
        }
        else
        {
            int t=Freq[x];
            Freq[x]=++t;
        }}
        i++;
    }
    file.close();
    priority_queue<node*,vector <node*>,comparemarks> pqueue;
    unordered_set<char> :: iterator itr;
    for (itr = All.begin(); itr != All.end(); itr++)
    {
        char e=*itr;
        node*c=create(e,Freq[e]);
        pqueue.push(c);
    }
    while(pqueue.size()!=1)
    {
        node*a=pqueue.top();
        pqueue.pop();
        node*b=pqueue.top();
        pqueue.pop();
        int q=a->freq+b->freq;
        node*s=createM(q);
        s->Left=a;
        s->Right=b;
        pqueue.push(s);
    }

    return make_pair(pqueue.top(),All.size());

}

void compressed(char*filename,unordered_map<char, string> byte,char*read,node*a)
{
    string all="";
    string all2="";
    ofstream MyFile(filename);
    ifstream file;
    file.open(read,ios::binary);
    unordered_map<char, string>:: iterator itr;

int pad=0;
    stringstream buffer;
    buffer << file.rdbuf();
    string contents(buffer.str());
    int i=0;
    char x;
    while(i<contents.size())
    { x=contents[i];
        //x=tolower(x);
        if(x!='\r')
        {all+=byte[x];
        all2+=x;}
        i++;
    }
    string h="";
    for(int i=0; i<all.size();)
    { string r="";

        if(i+7<all.size())
            {r = all.substr(i,8);
            }
        else
           {
               r=all.substr(i, all.size()-i);
           pad=8-(all.size()-i);
           }
            i+=8;
        bitset<8> mybits(r);
        unsigned long tr = mybits.to_ulong();
        unsigned char c = static_cast<unsigned char>( tr );
        h+=c;
    }
     string te="";

  write_tree(a,te,byte);

 MyFile << h.size()<< endl;
   MyFile << te.size()<< endl;
   MyFile << all2.size()<< endl;
     MyFile << pad<< endl;
     MyFile << te<< endl;
  MyFile << h;
    file.close();
    MyFile.close();
//cout<<all.size()<<endl;
}

void decompress(char*filename,char*nop)
{ ifstream file;
    file.open(filename,ios::binary);
    int num_encoded;
    file>>num_encoded;
    int header;
    file>>header;
    int original;
    file>>original;
    int pad;
    file>>pad;
    string ie;
    string code="";
    string encoded="";
    char t;
    char te;
    int z;
    int i=0;
    string oi="";
    unordered_map<string,char>decode;
stringstream buffer;
buffer << file.rdbuf();
string all(buffer.str());

all.erase(0,2);
string topology=all.substr(0,header+1);
string contents=all.erase(0,header+3);

for(int i=0; i<topology.size();)
{ char on=topology[i++];
if(on=='\r')
{ on='\n';
    i++;}
string we="";
while(topology[i]!=' ')
{
    we+=topology[i++];
}
decode.insert(make_pair(we,on));
we="";
i++;
}
    for(int i=0;i<contents.size();i++)
    { t=contents[i];
   if(t!='\r' || (t=='\r' &&contents[i+1]!='\n'))
    {
        if(i==contents.size()-1)
    { bitset<8> third (t);
    string ad=third.to_string();
     ad=ad.substr(pad,8-pad);
    encoded+=ad;
    }
    else{
    bitset<8> third (t);
    encoded+=third.to_string();
    }}}
   //cout<<encoded.size();
string fin="";
i=0;
string er="";
while(i<encoded.size())
{  er+=encoded[i];
   if(decode.find(er)!=decode.end())
     {fin+=decode[er];
     er="";
  }
i++;}

 ofstream file1;
    file1.open(nop,ios::binary);
    file1<<fin;

}

int main()
{
  cout<<"Welcome to Huffman compression and decompression program.\n";
cout<<"------------------------------------------------------\n";
int c=1;
while(c)
{cout<<"1.Compress File\n";
cout<<"2.Decompress File\n";
cout<<"3.Exit\n";
int w;
cin>>w;
switch (w)
{case 1:
    {cout<<"Enter name of file to compress:\n";
    string r;
    cin>>r;
    char * read = new char [r.length()+1];
strcpy (read, r.c_str());
    cout<<"Enter name of file to store the compression:\n";
    string er;
    cin>>er;
    char * write = new char [er.length()+1];
strcpy (write, er.c_str());
    clock_t t=clock();
    pair<node*,int>w=read_bin(read);
    vector<int> re(w.second,1);
    unordered_map<char, string> byte;
    analyze(w.first,re,0,byte);
  compressed(write,byte,read,w.first);
  cout<<"Compression Done........."<<read<<" is compressed into "<<write<<endl;
  t=clock()-t;
    cout<<((double)t)/CLOCKS_PER_SEC<<" Seconds to Compress.\n";
    ifstream first(read, ios::binary);
   first.seekg(0, ios::end);
   long long first_size = first.tellg();
   ifstream second(write, ios::binary);
   second.seekg(0, ios::end);
   long long second_size = second.tellg();
   double rati=((first_size*1.0-second_size*1.0)/first_size*1.0)*100;
   cout<<"The compression ratio is "<<rati<<"%\n";
   cout<<"------------------------------------------------------\n";
   cout<<"Do you want to see the codes used for each byte?\n";
   cout<<"1.Yes\n";
   cout<<"2.No\n";
   int rer;
   cin>>rer;
   switch (rer)
   { case 1:
       { for (auto const& pair: byte)
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    break;

       }
       default:break;
   }

    break;
}
    case 2:
    {cout<<"Enter name of file to decompress:\n";
    string r;
    cin>>r;
    char * read = new char [r.length()+1];
strcpy (read, r.c_str());
    cout<<"Enter name of file to store the decompression:\n";
    string er;
    cin>>er;
    char * write = new char [er.length()+1];
strcpy (write, er.c_str());
    clock_t t=clock();
   decompress(read,write);
  cout<<"Decompression Done........."<<read<<" is decompressed into "<<write<<endl;
  t=clock()-t;
    cout<<((double)t)/CLOCKS_PER_SEC<<" Seconds to decompress.\n";
    break;
}
    default:
        {
            c=0;
            break;
        }


}
cout<<"------------------------------------------------------\n";
}
cout<<"Thank you.";
    return 0;
}
