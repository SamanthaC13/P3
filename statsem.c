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
int stackCount=0,blockFlag=0;
void  traverseTree(struct node_t* p)
//Function that traverses the tree using recursion in a pre-order traversal
{
	int i,varsFlag=0;
	if(strcmp(p->nodeName,"vars")==0)
	{
		varsFlag=1;	
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
			if(tokenP->tokenID==IDTK)
			{
				if((varsFlag==1)&&(blockFlag==0))
				{
					if(verify(tokenP->tokenInstance))
					{	
						errorMsg(tokenP,2);
					}
					push(tokenP);
				}
				if((varsFlag==0)&&(blockFlag==0))
				{	
					//printf("\n%s",tokenP->tokenInstance);
					if(verify(tokenP->tokenInstance))
					{
						printf("\n%s-true",tokenP->tokenInstance);
					}
					else
					{
						errorMsg(tokenP,1);
					}
				}
				if((blockFlag==1)&&(varsFlag==0))
				{
					if(find(tokenP->tokenInstance)==-1)
					{
						errorMsg(tokenP,1);
					}
				}
				if((blockFlag==1)&&(varsFlag==1))
				{
					if(find(tokenP->tokenInstance)!=-1)
					{
						errorMsg(tokenP,2);
					}
					push(tokenP);
					p->blockVarCount++;
					printf("\n%d",p->blockVarCount);
				}
			}
			tokenP=tokenP->nextToken;
			j++;
		}
	}
	for(i=0;i<5;i++)
	{
		if((strcmp(p->nodeName,"block")==0)&&(i==0))
		{
			blockFlag=1;
		}
		if(p->children[i]!=NULL)
		{
			//the function recursivly calls itself with the children of the node
			traverseTree(p->children[i]);
		}
		if((strcmp(p->nodeName,"block")==0)&&(i==1))
		{
			if(p->blockVarCount>0)
			{
				int k=0;
				for(;k<p->blockVarCount;k++)
				{	
					pop();
				}
			}
			blockFlag=0;
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
	stackCount++;
	printf("\npush-%s-%d",addToken->tokenInstance,stackCount);
}
void pop()
{
	if(*headP==NULL)
	{
		return;
	}
	struct stackNode* prev=*headP;
	struct stackNode* deleteNode=*headP;
	while(deleteNode->next!=NULL)
	{	
		prev=deleteNode;
		deleteNode=deleteNode->next;	
	}
	printf("\npop-%s",deleteNode->IDtoken->tokenInstance);
	free(deleteNode);
	currentNode=prev;
	prev->next=NULL;
	stackCount--;
}
int find(char* identifier)
{
	struct stackNode* top=*headP;
	int count=1;
	while(top!=NULL)
	{
		printf("\n%s->",top->IDtoken->tokenInstance);
		if(strcmp(top->IDtoken->tokenInstance,identifier)==0)
		{
			break;
		}
		count++;
		top=top->next;		
	}
	printf("\nfound %s at %d-stackCount-%d",identifier,count,stackCount);	
	return (stackCount-count);
}
bool verify(char* identifier)
{
	struct stackNode* stackP;
	if(headP!=NULL)
	{
		stackP=*headP;
	}
	else
	{
		return false;
	}
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
void errorMsg(struct tokenType* token, int errorCase)
{
	if(errorCase==1)
	{
		printf("\nSTATIC SEMENTIC ERROR:%s on line %d has not been defined",token->tokenInstance,token->lineCount); 
	}
	if(errorCase==2)
	{
		printf("\nSTATIC SEMANTIC ERROR:%s on line %d has been defined multiple times",token->tokenInstance,token->lineCount);
	}
	exit(1);
}
