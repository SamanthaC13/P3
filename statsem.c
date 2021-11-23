/*Name: Samantha Craig
 * Project 3
 * Class:CS4280*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"token.h"
#include"parser.h"

void  traverseTree(struct node_t* p)
//Function that prints the tree using recursion in a pre-order traversal
{
	int i;
	printf("\n%*c%d:%s-",level*2,' ',level,p->nodeName);
	if(p->startToken!=NULL)
	//In each node all the tokens in that node are printed also
	{
		int j=0;
		struct tokenType* tokenP=p->startToken;
		while(j<p->numOfTokens)
		{
			printf(" %s",tokenP->tokenInstance);
			tokenP=tokenP->nextToken;
			j++;
		}
	}
	for(i=0;i<5;i++)
	{
		if(p->children[i]!=NULL)
		{
			//the function recursivly calls itself with the children of the node
			printTree(p->children[i],level+1);
		}
	}
	return;
}
