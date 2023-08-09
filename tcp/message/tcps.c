#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sock_desc,k,temp_sock_desc;
    struct sockaddr_in client,server;
    char buf[100];
    socklen_t len;
    
    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3001;
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3001;
    
    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
        printf("Error in binding");
    
    k=listen(sock_desc,5);
    if(k==-1)
        printf("Error in listening");
    
    len=sizeof(client);
    temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
    if(temp_sock_desc==-1)
        printf("Error in temporary socket creation");
    
    for(;;)
    {
        k=recv(temp_sock_desc,buf,100,0);
        if(k==-1)
            printf("Error in receiving");
        if(atoi(buf)==1111)
        {
            printf("\nExiting");
            exit(0);
        }
        printf("\nData received from client is %s",buf);
        printf("\nEnter data to be sent to client");
        fgets(buf,100,stdin);
        k=send(temp_sock_desc,buf,100,0);
        if(k==-1)
            printf("Error in sending");
    }
}
