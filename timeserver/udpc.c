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
    int k;
    socklen_t len;
    sock_desc=socket(AF_INET,SOCK_DGRAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3001);
    
    
    int num=1;
    time_t start_time,current_time,rtt;
    clock_t start_t,end_t;
    double rtt1;
    
    
    start_time=time(NULL);
    start_t=clock();
    k=sendto(sock_desc,&num,sizeof(num),0,(struct sockaddr*) &server,sizeof(server));
    
    len=sizeof(server);
    k=recvfrom(sock_desc,&current_time,sizeof(current_time),0,(struct sockaddr*) &server,&len);
    
    end_t=clock();
    rtt1=end_t-start_t;
    rtt1=rtt1/2;
    
    rtt=time(NULL)-start_time;
    current_time+=rtt/2;
    printf("Server Time : %s is delayed by %f",ctime(&current_time),rtt1);
}
