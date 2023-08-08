#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    char buf[100],bufs[100];
    struct sockaddr_in client,server;
    int sock_desc,temp_sock_desc;
    int k;
    socklen_t len;
    
    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3003;
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3003;
    
    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
        printf("Error in binding");
    
    k=listen(sock_desc,5);
    if(k==-1)
        printf("Error in listening");
    
    len=sizeof(client);    
    
    temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
    if(temp_sock_desc==-1)
        printf("Error in accepting");
        
    for(;;)
    {
        k=recv(temp_sock_desc,buf,100,0);
        if(k==-1)
            printf("Error in receiving");
        
        int n=atoi(buf);
        if(n==1111)
        {
            printf("Exiting");
            exit(0);
        }
        printf("\nData received from client is %s",buf);
        
        int flag=0;
        for(int j=2;j<=n/2;j++)
        {
            if(n%j==0)
                {
                    flag=1;
                    break;
                }
        }
        
        sprintf(bufs,"%d",flag);
        k=send(temp_sock_desc,bufs,100,0);
        if(k==-1)
            printf("Error in sending");
    }
}
