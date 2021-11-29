/*Name: Samantha Craig
 * Project 3
 * Class:CS4280*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"token.h"
#include"parser.h"
#include"statsem.h"
struct stackNode* symbolTableRoot;
struct stackNode* currentNode;
void  traverseTree(struct node_t* p)
//Function that traverses the tree using recursion in a pre-order traversal
{
	int i;
	if(strcmp(p->nodeName,"vars")==0)
	{
		insert(p->startToken);	
	}
//	printf("\n%*c%d:%s-",level*2,' ',level,p->nodeName);
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
			traverseTree(p->children[i]);
		}
	}
	return;
}
void insert(struct tokenType* addToken)
{
	if(symbolTableRoot=NULL)
	{
		symbolTableRoot->IDtoken=malloc(sizeof(struct tokenType));
		symbolTableRoot->IDtoken=addToken;
		symbolTableRoot->next=NULL;
		currentNode=symbolTableRoot;
	}
	else
	{
		struct stackNode* temp= malloc(sizeof(struct stackNode));
		currentNode->next=temp;
		temp->IDtoken=addToken;
		currentNode->next=NULL;
		currentNode=temp;
	}
}
bool verify(char* identifier)
{
	struct stackNode* stackP=symbolTableRoot;
	while(stackP->next!=NULL)
	{
		if(strcmp(stackP->IDtoken->tokenInstance,identifier)==0)
		{
			return true;
		}
		stackP=stackP->next;
	}
	return false;
}
