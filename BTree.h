#include "Node.h"

#ifndef BTree_Node_H
#define BTree_Node_H

typedef struct t_BTree_Node
{
  Node *Head;
}BTree;

BTree * CreateBTree(int m);
int SearchInBTree(BTree* root, long int value);
BTree* InsertIntoBTree(BTree* root, long int value);

#endif
