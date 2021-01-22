#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <bits/stdc++.h>
#include <fstream>
#define COUNT 10
using namespace std;


typedef struct node
{
    char* data;
    struct node* left;
    struct node* right;
    struct node* parent;
    bool color; /*0 black*1 red */
} node;

node*create(char* x);
node*createroot(char* x);
char* in(node*root,char*x);
node* search (node*root,char *x);

node* create(char* x)
{
    node *c=(node*)malloc(sizeof(node));
    c->data=(char*)malloc(sizeof(char)*35);
    strcat(c->data,x);
    c->left=NULL;
    c->right=NULL;
    c->color=1;
    return c;
}
node*createroot(char* x)
{
    node *c=(node*)malloc(sizeof(node));
    c->data=(char*)malloc(sizeof(char)*35);
    strcat(c->data,x);
    c->left=NULL;
    c->right=NULL;
    c->color=0;
    c->parent=NULL;

}

node* insert (node* root, node*child)
{

    if (root==NULL)
    {
        return child;

    }
    else if (strcmp(child->data,root->data)<0)
    {
        root->left = insert(root->left,child);
        root->left->parent=root;
    }
    else if (strcmp(child->data,root->data)>0)
    {

        root->right= insert(root->right,child);
        root->right->parent=root;
    }

    return root;
}
void rotateLeft(node *&root, node *&grand,node*&temp)
{
    if(grand!=root)
    {
        if (temp->left != NULL)
        {
            temp->left->parent=grand;
            grand->right=temp->left;
        }
        else
            grand->right=NULL;
        temp->parent=grand->parent;
        if(grand==grand->parent->right)
            grand->parent->right=temp;
        else
            grand->parent->left=temp;
        grand->parent=temp;
        temp->left=grand;
    }
    else
    {
        if (temp->left != NULL)
        {
            temp->left->parent=grand;
            grand->right=temp->left;
        }
        else
            grand->right=NULL;
        temp->parent=NULL;
        grand->parent=temp;
        temp->left=grand;
        root=temp;

    }
}

void rotateRight(node *&root, node *&grand,node*&temp)
{
    if(grand!=root)
    {
        if (temp->right != NULL)
        {
            temp->right->parent=grand;
            grand->left=temp->right;
        }
        else
            grand->left=NULL;
        temp->parent=grand->parent;
        if(grand==grand->parent->right)
            grand->parent->right=temp;
        else
            grand->parent->left=temp;
        grand->parent=temp;
        temp->right=grand;
    }
    else
    {
        if (temp->right != NULL)
        {
            temp->right->parent=grand;
            grand->left=temp->right;
        }
        else
            grand->left=NULL;
        temp->parent=NULL;
        grand->parent=temp;
        temp->right=grand;
        root=temp;

    }
}


void adjust(node*&root, node*&child)
{
    node *parent= NULL;
    node *grand= NULL;
    node*uncle=NULL;
    node*temp=NULL;
    while ((child != root) && (child->color ==1) && (child->parent->color == 1))
    {

        parent = child->parent;
        grand = child->parent->parent;
        if (parent == grand->left)
        {
            uncle = grand->right;
            if (uncle != NULL && uncle->color == 1)
            {
                if(grand!=root)
                    grand->color = 1;
                parent->color = 0;
                uncle->color = 0;
                child = grand;
            }

            else
            {
                //LR
                if (child == parent->right)
                {
                    rotateLeft(root,parent,child);
                    rotateRight(root,grand,child);
                    parent->color=1;
                    grand->color=1;
                    child->color=0;
                }
                //LL
                else if (child == parent->left)
                {
                    rotateRight(root,grand,parent);
                    parent->color=0;
                    grand->color=1;
                    child->color=1;
                    child=parent;
                }

            }

        }

        else
        {
            node*uncle = grand->left;

            if ((uncle != NULL) && (uncle->color ==1))
            {
                if(grand!=root)
                    grand->color = 1;
                parent->color = 0;
                grand->left->color = 0;
                child = grand;
            }
            else
            {
                //RL
                if (child == parent->left)
                {
                    rotateRight(root,parent,child);
                    rotateLeft(root,grand,child);
                    parent->color=1;
                    grand->color=1;
                    child->color=0;
                }
                //RR
                else if (child == parent->right)
                {
                    rotateLeft(root,grand,parent);
                    parent->color=0;
                    grand->color=1;
                    child->color=1;
                    child=parent;
                }
            }
        }
    }



    root->color = 0;
}

node* search(node*root,char *x)
{
    if (root==NULL)
        return NULL;
    else if(strcmp(x,root->data)==0)
        return root;
    else if (strcmp(x,root->data)<0)
        search(root->left, x);
    else if (strcmp(x,root->data)>0)
        search(root->right, x);

}

int size (node* root)
{
    if(root == NULL)
        return 0;
    else
        return 1 + size(root->left) + size(root->right);
}


int height(node *root)
{
    return (root==NULL)? -1:1+ max(height(root->left),height(root->right));
}
/*void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}*/
int main()
{

    node*root=(node*)malloc(sizeof(node));
    node*child=(node*)malloc(sizeof(node));
    root->data=(char*)malloc(sizeof(char)*35);
    child->data=(char*)malloc(sizeof(char)*35);
    FILE *fp;
    fp = fopen("text.txt","r");
    char* word=(char*)malloc(sizeof(char)*35);
    if(!feof(fp))
    {
        fscanf(fp,"%s",word);
        root=createroot(word);
    }

    while(!feof(fp))
    {
        fscanf(fp,"\n%[^\n]s",word);
        child=create(word);
        root= insert(root,child);
        adjust(root,child);

    }
    fclose(fp);
//print2D(root);
    cout<<"Height of the TREE is "<<height(root);
    cout<<"\nSize of the TREE is "<<size(root)<<"\n";
    int end =1;
    while(end)
    {
        cout<<"Enter your Word:\n";
        cin>>word;
        child=create(word);
        if(search(root,word)!=NULL)
            cout<<"This Word is Already in the dictionary";
        else
        {
            root= insert(root,child);
            adjust(root,child);
            cout<<word<<" has been added to the dictionary";
            cout<<"\nThe new Height of the TREE is "<<height(root);
            cout<<"\nThe new Size of the TREE is "<<size(root);
        }
        char c;
        cout<<"\nDO YOU WANT TO ENTER ANOTHER WORD?\nFor YES ENTER 1 \n";
        cin>>c;
        while(!isdigit(c))
        {
            cout<<"INVALID INPUT!! ENTER AGAIN!\n";
            cin>>c;
        }



        switch(c)
        {
        case('1'):
        {
            end=1;
            break;
        }

        default:
        {
            end=0;
            break;
        }
        }

    }
    return 0;

}
