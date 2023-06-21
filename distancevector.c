#include <stdio.h>

struct route 
{
    int distance[20];
    int adjNode[20];
}node[20];

int n,costmatrix[20][20];
int main()
{
    printf("Enter the no of nodes: ");
    scanf("%d",&n);
    readCostMatrix();
    calcRoutingTable();
    displayRoute();
}

void readCostMatrix()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&costmatrix[i][j]);
            costmatrix[i][i]=0;
            node[i].distance[j]=costmatrix[i][j];
            node[i].adjNode[j]=j;
        }
    }
}

void calcRoutingTable()
{
    
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
            {
                if(node[i].distance[j]>costmatrix[i][k]+node[k].distance[j])
                {
                    node[i].distance[j]=node[i].distance[k]+node[k].distance[j];
                    node[i].adjNode[j]=k;
                }
            }
        }
    }
}

void displayRoute()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("\n\nRouter %d",i+1);
        for(j=0;j<n;j++)
        {
            printf("\nNode %d via %d: Distance %d",j+1,node[i].adjNode[j]+1,node[i].distance[j]);
        }
    }
    
}
