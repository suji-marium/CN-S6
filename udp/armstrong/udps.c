#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
    struct sockaddr_in client,server;
    int sock_desc,k;
    socklen_t len;
    char buf[100];
    
    sock_desc=socket(AF_INET,SOCK_DGRAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3001);
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=htons(3001);
    
    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
        printf("Error in binding");
        
    len=sizeof(client);
    while(1)
    {
        k=recvfrom(sock_desc,buf,100,0,(struct sockaddr*)&client,&len);
        if(k==-1)
            printf("Error in receiving");
        
        int n=atoi(buf),temp=n,p,rem,res=0,count=0,flag=0;
        
        if(n==1111)
        {
            printf("\nExiting\n");
            exit(0);
        }
        printf("\nData received from client is %s",buf);
        
        while(temp!=0)
        {
            temp/=10;
            count++;
        }
            
        temp=n;
            
        while(temp!=0)
        {
            p=1;
            rem=temp%10;
            for(int i=1;i<=count;i++)
                p*=rem;
            res+=p;
            temp/=10;
        }
            
        if(n==res)
            flag=1;
        else
            flag=0;
        
        sprintf(buf,"%d",flag);
        k=sendto(sock_desc,buf,100,0,(struct sockaddr*)&client,sizeof(client));
        if(k==-1)
            printf("Error in sending");
        
    }
}
