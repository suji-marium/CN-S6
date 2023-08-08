#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    char buf[100];
    struct sockaddr_in client,server;
    int sock_desc;
    int k;
    socklen_t len;
    
    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3003;
    
    k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
    if(k==-1)
        printf("Error in connecting");
    
    for(;;)
    {
        printf("\nEnter data to be sent: ");
        fgets(buf,100,stdin);
        if(atoi(buf)==1111)
        {
            k=send(sock_desc,buf,100,0);
            printf("\nExit Request sent\nExiting");
            exit(0);
        }
        
        k=send(sock_desc,buf,100,0);
        if(k==-1)
            printf("Error in sending");
            
        k=recv(sock_desc,buf,100,0);
        if(k==-1)
            printf("Error in receiving");
        
        if(atoi(buf)==1)
            printf("\nNumber is not prime");
        else
            printf("\nNumber is prime");
    }
    
}
