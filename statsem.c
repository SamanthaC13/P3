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
struct stackNode* head;
struct stackNode* currentNode;
struct stackNode** headP;
void  traverseTree(struct node_t* p)
//Function that traverses the tree using recursion in a pre-order traversal
{
	int i,varsFlag=0;
	if(strcmp(p->nodeName,"vars")==0)
	{
		varsFlag=1;
		push(p->startToken);	
	}
//	printf("\n%*c%d:%s-",level*2,' ',level,p->nodeName);
	if(p->startToken!=NULL)
	//In each node all the tokens in that node are printed also
	{
		int j=0;
		struct tokenType* tokenP=p->startToken;
		while(j<p->numOfTokens)
		{
			//printf("\n %s",tokenP->tokenInstance);
			if((tokenP->tokenID==IDTK)&&(varsFlag==0))
			{
				//printf("\n%s",tokenP->tokenInstance);
				if(verify(tokenP->tokenInstance))
				{
					printf("\n%s-true",tokenP->tokenInstance);
				}
				else
				{
					printf("Static Semantic error- variable is not defined");
				}
			}
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
void push(struct tokenType* addToken)
{
	struct stackNode* temp=malloc(sizeof(struct stackNode));
	temp->IDtoken=addToken;
	temp->next=NULL;
	if(currentNode!=NULL)
	{
		currentNode->next=temp;
		currentNode=temp;	
	}
	else
	{
		currentNode=malloc(sizeof(struct stackNode));
		currentNode=temp;
		head=malloc(sizeof(struct stackNode));
		head=currentNode;
		headP=&head;
	}
}
bool verify(char* identifier)
{
	struct stackNode* stackP=*headP;
	while(stackP!=NULL)
	{
		//printf("\n%s",stackP->IDtoken->tokenInstance);
		if(strcmp(stackP->IDtoken->tokenInstance,identifier)==0)
		{
			return true;
		}
		stackP=stackP->next;
	}
	return false;
}
