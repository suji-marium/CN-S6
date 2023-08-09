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
    
    while(1)
    {
        printf("\nEnter data to be send to server: ");
        fgets(buf,100,stdin);
        
        if(atoi(buf)==1111)
        {
            k=sendto(sock_desc,buf,100,0,(struct sockaddr*)&server,sizeof(server));
            printf("\nExit request sent\nExiting\n");
            exit(0);
        }
        
        k=sendto(sock_desc,buf,100,0,(struct sockaddr*)&server,sizeof(server));
        if(k==-1)
            printf("Error in sending");
        
        len=sizeof(server);
        k=recvfrom(sock_desc,buf,100,0,(struct sockaddr*)&server,&len);   
        if(atoi(buf)==1)
            printf("Number is Armstrong");
        else
            printf("Number is not Armstrong");
        
    }
}
