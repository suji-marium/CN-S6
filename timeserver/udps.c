#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

int main()
{
    struct sockaddr_in client,server;
    int sock_desc;
    int k,num;
    socklen_t len;
    sock_desc=socket(AF_INET,SOCK_DGRAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3001);
    
    k=bind(sock_desc,(struct sockaddr*) &server,sizeof(server));
    if(k==-1)
        printf("Error in binding");
    len=sizeof(client);
    
    time_t current_time;
    
    while(1)
    {
        k=recvfrom(sock_desc,&num,sizeof(num),0,(struct sockaddr*) &client,&len);
        if(k==-1)
            printf("Error in receiving");
        current_time=time(NULL);
        printf("Time at which client requested is %s",ctime(&current_time));
        k=sendto(sock_desc,&current_time,sizeof(current_time),0,(struct sockaddr*) &client,sizeof(client));
        if(k==-1)
            printf("Error in sending");
    }
}
