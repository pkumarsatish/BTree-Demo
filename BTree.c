#include "BTree.h"

BTree* CreateBTree(int treeOrder)
{
	BTree *root;
	m = treeOrder;
	root = (BTree*)malloc(sizeof(BTree));
	root->Head = NULL;
return root;
}

int SearchInBTree(BTree *root,long int value){

	return SearchInNode(root->Head,value);

}

BTree* InsertIntoBTree(BTree* root, long int value){
	root->Head = InsertIntoNode(root->Head,value);

return root;
}

void DeleteBTree(BTree *root)
{
	
	deleteTree(root->Head);
	root=NULL;
}

void checkBParent(BTree *root){
checkParent(root->Head);
}
