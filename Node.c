#include "Node.h"

Node* createNode(){
  Node *temp;
  long int *temp1;
  int i=0;
  temp = (Node *)malloc(sizeof(Node) + m*(sizeof(Node *)));
  temp1 = (long int*)malloc((m-1) * sizeof(long int));
  if(temp != NULL && temp1 != NULL){
    temp->key = temp1;
    temp->isLeaf = 1;
    temp->n = 0;
    temp->parent = NULL;
    for(i=0;i<m;i++)
      temp->children[i] = NULL;
    }
    else{
      printf("Out of memory\n");
      exit(0);
    }
  return temp;
}

long int* copyArray(long int *temp, long int *org,int n)
{
  int i;
  for(i=0;i<n;i++)
    temp[i] = org[i];
  return temp;
}

void printArray(long int *a, int n)
{
  int i;
}

long int* sortTheArray(long int *arr,int num)
{
  long int i,j,temp;
  for (i = 1; i < num; i++) {
      temp = arr[i];
      j = i - 1;
      while ((temp < arr[j]) && (j >= 0)) {
         arr[j + 1] = arr[j];
         j = j - 1;
      }
      arr[j + 1] = temp;
   }

return arr;
}


int binarySearch(long int *array, int n, long int search)
{
int first, last, middle;
   first = 0;
   last = n - 1;
   middle = (first+last)/2;
 
   while( first < last )
   {
      if ( array[middle] < search )
         first = middle + 1;    
      else if ( array[middle] == search ) 
      {
	return middle;
      }
      else
         last = middle - 1;
 
      middle = (first + last)/2;
   }
   return middle;
}



Node* splitNode(Node* node, long int *tempNode){
	int pos = m/2;
	int i;
	Node *rightNode = createNode();
	node->n = 0;
	rightNode->n = 0;		
	for(i=0;i < pos;i++)
	{
		node->key[i] = tempNode[i];
		node->n +=1; 
	}
	for(i=pos+1;i < m;i++)
	{
		rightNode->key[i] = tempNode[i]; 
		rightNode->n +=1;
	}
return rightNode;
}


Node* InsertIntoNode(Node* rootNode, long int value)
{
	int pos,i,j,splitPos;
	long int temp=0;
	long int *tempNode, *tempParent;
	Node *newRoot,*p,*q,*r,*insNode,*node;
	Node *rightNode;
	
	if(rootNode == NULL){				
		rootNode = createNode();		
		rootNode->key[0] = value;
		rootNode->children[0] = rootNode->children[1] =  NULL; 
		rootNode->n = 1;
		rootNode->isLeaf = 1;
		return rootNode;		
	}	
	
	node = rootNode;
	//printf("%d-->",node->n);
	while(node->isLeaf != 1){
		splitPos = binarySearch(node->key,node->n,value);
		if(node->key[splitPos] > value)
			node = node->children[splitPos];	
		else
			node = node->children[splitPos+1];
	}
	if((node->n < m-1) && node->isLeaf == 1){
		node->key[node->n] = value;
		node->n +=1;	
		node->key = sortTheArray(node->key,node->n);
		return rootNode;	
	}
	else if(node->n == m-1 && node->isLeaf == 1){
		tempNode = (long int*)calloc(m,(sizeof(long int)));
		if(tempNode == NULL){
			printf("Memory allocation error\n");
					exit(0);
		}
		pos = m/2;
		tempNode = copyArray(tempNode,node->key,node->n);
		tempNode[m-1] = value;
		tempNode = sortTheArray(tempNode,m);		
		printArray(tempNode,m);
		
		if(node->parent == NULL){		
			newRoot = createNode();
			newRoot->isLeaf = 0;
			newRoot->n = 1;
			newRoot->key[0] = tempNode[pos];
			printArray(node->key,node->n);
			Node *rightNode = splitNode(node,tempNode);			
			rightNode->isLeaf = 1;
			node->parent = rightNode->parent = newRoot;			
			newRoot->children[0] = node;
			newRoot->children[1] = rightNode;
			free(tempNode);			
			return newRoot;		
		}
		else{
			p = node->parent;
			temp = tempNode[pos];
			if(p->n < m-1){		
				p->key[p->n] = temp;
				p->n +=1;
				p->key = sortTheArray(p->key,p->n);
				splitPos = binarySearch(p->key,p->n,temp);
				rightNode = splitNode(node,tempNode);
				rightNode->isLeaf = 1;
				rightNode->parent = p;
				
				p->children[splitPos] = node;
				q = p->children[splitPos+1]; 
				p->children[splitPos+1] = rightNode;
				for(i=splitPos+2;i<=p->n;i++)
				{
					r = p->children[i];						
					p->children[i] = q;							
					q=r;
				}
				free(tempNode);
			  return rootNode;			
			}
			else
			{
				Node *rightNode = splitNode(node, tempNode);
				rightNode->isLeaf = node->isLeaf;
				tempParent = (long int*)calloc(m,(sizeof(long int)));
				while(!(p->n < m-1)){
					if(tempParent == NULL){
						printf("Memory allocation error\n");
						exit(0);
					}
					tempParent = copyArray(tempParent,p->key,p->n);
					tempParent[m-1] = temp;
					tempParent = sortTheArray(tempParent,m);
					printArray(tempParent,m);
					splitPos = binarySearch(tempParent,m,temp);
					temp = tempParent[pos];	
					Node *rightParent = splitNode(p,tempParent);
					rightParent->isLeaf = 0;
					if(pos == splitPos){
						rightParent->children[0] = rightNode;
						rightNode->parent = rightParent;
						rightParent->parent = p->parent;
						p->children[p->n] = node;					
						for(i=1;i<=rightParent->n;i++){
							rightParent->children[i] = p->children[i+pos];
							(rightParent->children[i])->parent = rightParent;
							p->children[i+pos]=NULL;	
						}
					}
					else if(splitPos < pos){
						for(i=0;i<=rightParent->n;i++){
							rightParent->children[i] = p->children[i+pos];
							(rightParent->children[i])->parent = rightParent;
							p->children[i+pos]=NULL;
						}						
						rightNode->parent = p;
						rightParent->parent = p->parent;						
						p->children[splitPos] = node;
						q = p->children[splitPos+1]; 
						p->children[splitPos+1] = rightNode;
						for(i=splitPos+2; i <= p->n;i++)
						{
							r = p->children[i];						
							p->children[i] = q;							
							q=r;
						}
					}
					else if(splitPos > pos){
						for(i=pos;i<splitPos;i++){
							rightParent->children[i-pos] = p->children[i+1];
							(rightParent->children[i-pos])->parent = rightParent;
							p->children[i+1] = NULL;

						}
						rightNode->parent = rightParent;
						rightParent->parent = p->parent;

						rightParent->children[splitPos-pos] = rightNode;
						q = p->children[splitPos+1];
						p->children[splitPos+1] = NULL;
						//rightParent->children[splitPos+1-pos] = rightNode;
						rightNode->parent = rightParent;
	//printf("sp^^%d pos^^%d p->elem^^%d rightprn^^%d\n",splitPos,pos,p->n,rightParent->n);
						for(i=splitPos+1; i <= (rightParent->n + pos);i++)
						{
							//r = p->children[i];						
							rightParent->children[i-pos] = q;
							q->parent = rightParent;
							q=p->children[i+1];
							p->children[i+1] = NULL;
						}
					}
					printArray(node->key,node->n);							
					node = p;
					rightNode = rightParent;
					p = p->parent;
					if(p==NULL){
						newRoot = createNode();
						newRoot->isLeaf = 0;
						newRoot->n = 1;
						newRoot->key[0] = temp;
						newRoot->children[0] = node;
						newRoot->children[1] = rightNode;
						node->parent = rightNode->parent = newRoot;
						//rootNode = newRoot;
						free(tempNode);
						free(tempParent);	
						//printf("new root value %d\n",newRoot->key[0]);					
						return newRoot;
				 	}
					
				}//end of while
				p->key[p->n] = temp;
				p->n +=1;
				p->key = sortTheArray(p->key,p->n);
				splitPos = binarySearch(p->key,p->n,temp);
		
				p->children[splitPos] = node;
				q = p->children[splitPos+1]; 
				p->children[splitPos+1] = rightNode;
				rightNode->parent = p;
				for(i=splitPos+2;i<=p->n;i++)
				{
					r = p->children[i];						
					p->children[i] = q;							
					q=r;
				}
				free(tempNode);
				free(tempParent);
				return rootNode;
			}
				

		}
	}
	
}

void deleteTree(Node *root)
{

	Node *nd;
	int i,j,k;
	nd = root;
	if(root!=NULL && root->isLeaf == 1){
		if(root->key != NULL){
			free(root->key);
			root->key = NULL;
			free(root);	
			root = NULL;
		}
		return;
	}
	else{

		for(i=0;i<=root->n;i++)
		{
			if(root->children[i]!=NULL)
				deleteTree(root->children[i]);
		}

	}
	if(root->key != NULL){	
		free(root->key);
		root->key = NULL;
		free(root);	
		root = NULL;
	}
}

void checkParent(Node *ndroot)
{

	Node *nd;
	int i,j,k;
	
	if((ndroot->isLeaf) == 1){	
		return;
	}
	else{

		for(i=0;i<=ndroot->n;i++)
		{
			nd = ndroot->children[i];
			if(ndroot->isLeaf == 0 && nd == NULL){
				printf("child error %d--%d**%d\n",ndroot->n,ndroot->key[0],ndroot->key[1]);
				if(ndroot->parent != NULL)
					printf("parent value %d &&\n",(ndroot->parent)->key[0]);
				else
					printf("no parent\n");	
				break;		
			}
			if(nd != NULL){
				if(nd->parent != ndroot){
					printf("parent error %d**%d\n",ndroot->key[0],m);
					break;
				}
				else
					checkParent(ndroot->children[i]);
			}
		}

	}
}
int SearchInNode(Node *root,long int value){
	int pos;
	if(root == NULL)
		return 0;
	pos = binarySearch(root->key,root->n,value);

	if(root->key[pos]==value)
		return 1;
	else if(root->key[pos] > value)
		return SearchInNode(root->children[pos],value);
	else
		return SearchInNode(root->children[pos+1],value);
		
}

