#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<sys/time.h>
#include<time.h>


#ifndef Node_H
#define Node_H

int m;

typedef struct t_Node
{
  long int *key;
  int n;
  int isLeaf;
  struct t_Node *parent;
  struct t_Node *children[];	
} Node;

Node* createNode();
int SearchInNode(Node* root, long int key);
Node* splitNode(Node* node1,long int *tempNode);
Node* InsertIntoNode(Node* root, long int value);

#endif
