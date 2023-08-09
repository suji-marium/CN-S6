#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sock_desc,k;
    struct sockaddr_in client,server;
    char buf[100];
    socklen_t len;
    
    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3001;
    
    k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
    if(k==-1)
        printf("Error in connecting");
    
    for(;;)
    {
        printf("Enter data to be sent to server: ");
        fgets(buf,100,stdin);
        
        if(atoi(buf)==1111)
        {
            k=send(sock_desc,buf,100,0);
            printf("\nExit Request Sent\nExiting");
            exit(0);    
        }
        k=send(sock_desc,buf,100,0);
        if(k==-1)
            printf("Error in sending");
            
        k=recv(sock_desc,buf,100,0);
        if(k==-1)
            printf("Error in receiving");
            
        printf("Data received from server is %s",buf);
    }
}
