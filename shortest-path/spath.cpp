#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define PATH "adjacency.txt"
#define MAX 9999
struct node{
	struct node *link;
	int data;
};
int **arrr,n,*dist,*stack,top=-1;
void SPT(int ,int);
void creat();//creats adjacency matrix
void display(int **,int );//display a 2d array
int shortpath(int **,int ,int ,int );//find shortest path take input as adjacency matrix,v1,v2,total no of vertices
int main()
{
	int i,j,k;
	creat();
	display(arrr,n);
	printf("\n enter two vertices to determine the shortes path ");
	scanf("%d%d",&i,&j);
    SPT(i,j);
    printf("\n shortest path between %d to %d ==%d\n path  ",i,j,dist[j]);
    for(k=top;k>=0;k--)
    printf("-->%4d",stack[k]);
    printf("\n shortest path between %d to %d = %d \n",i,j,shortpath(arrr,i,j,n));
    
	
}
void creat()//creats adjacency matrix
{
	char arr[100],c;int i=0,j,k,n1,i1,l;FILE *ptr; 
	ptr=fopen(PATH,"r");
	fgets(arr,80,ptr);
    i=0;n=0;
	while(arr[i]!='\n')// gets the total no of vertex
	{
		k=arr[i]-'0';
		n=(n*10)+k;
		i++;
	}
	arrr=(int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++)
	arrr[i]=(int *)malloc(sizeof(int)*n);
	n1=0;i=0;j=0;k=0;
	for(i=0;i<n;i++,j=0)
	{
	 fgets(arr,80,ptr);i1=0;
	 l=strlen(arr)-1;
	  for(i1=0;i1<=l;i1++)
	   {
	     if(isdigit(arr[i1]))
	     {
	      k=0;
	      k=arr[i1]-'0';
	       n1=n1*10+k;
	      if((i==n-1)&&(j==n-1))
	      arrr[i][j]=n1;	
	     }
	    else
        {
         arrr[i][j]=n1;
	     n1=0;j++;
	    }
	   }
	}
	fclose(ptr);
}
void display(int **arr,int n)//display a 2d array
{
	int i,j;
	for(i=0;i<n;i++)
	{
	  printf("\n");
	  for(j=0;j<n;j++)
       printf(" %d  ",arr[i][j]);
    }
	
}
int shortpath(int **arr,int u,int v,int n)//find shortest path take input as adjacency matrix,v1,v2,total no of vertices
{
	int i,j,k;
	//0 values are already updated to MAX
	for(k=0;k<n;k++)
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    if(arr[i][j]>arr[i][k]+arr[k][j])
    arr[i][j]=arr[i][k]+arr[k][j];
    return arr[u][v];
	
}	
void SPT(int u,int v)//find shortest path
{
	int *l,*la,lsize=-1,lasize=0,ch,f=0,i,j,k,k1,min2,min1;
	struct node **tree,*p,*q;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	if(arrr[i][j]==0)
	arrr[i][j]=MAX;
	dist=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	dist[i]=MAX;//distance array stores distance of every node from source
	dist[u]=0;
	l=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		if(i!=u)
		{
		 lsize++;
		 l[lsize]=i;
		}
	
	}
	la=(int *)malloc(sizeof(int)*n);
	la[lasize]=u;
	stack=(int *)malloc(sizeof(int)*n);
	tree=(struct node **)malloc(sizeof(struct node *)*n);
	for(i=0;i<n;i++)
	tree[i]=0;
	min2=MAX;
	while(lsize>=0)//finding of minimum distance node
	{
		min2=MAX;
		for(i=0;i<=lasize;i++)
		{
			ch=la[i];
		    for(j=0;j<n;j++)
		   {   
		       if(((arrr[ch][j]+dist[ch])<=min2)&&(dist[j]==MAX))
			    {
				 min2=dist[ch]+arrr[ch][j];
                 k=ch;k1=j;
		     	}
		   }
	    }
	    if(min2!=MAX)//creation of shortest path tree
	    {
	    	dist[k1]=min2;
	    	if(tree[k]==0)
	    	{
	    		p=(struct node *)malloc(sizeof(struct node));
	    		tree[k]=p;
	    		p->data=k1;
	    		p->link=0;
	    	}
	    	else
	    	{
	    		p=tree[k];
	    		while(p!=0)
	    		{
	    			if(p->link==0)
	    			{
	    				q=(struct node *)malloc(sizeof(struct node));
	    				p->link=q;
	    				q->link=0;
	    				q->data=k1;
	    				break;
	    			}
	    			p=p->link;
	    		}
	    	}
	    	
	    }
	    if(k1==v)
	    break;
	    lasize++;
	    la[lasize]=k1;
	    for(i=0;i<lsize;i++)//update the value of l[] &&la[]
	    {
	    	if(l[i]==k1)
	    	{
	    	   l[i]=l[lsize];break; 
			}
		}
		lsize--;
		
	}
	top=0;
	stack[top]=v;
	i=0;
	while(i<n)//finding of path from tree using stack
	{
		p=tree[i];
		while(p!=0)
		{
			if(p->data==stack[top])
			{
				top++;
				stack[top]=i;
				i=-1;
			}
			p=p->link;
		}
		if(stack[top]==u)
		break;
		i++;
	}
}
