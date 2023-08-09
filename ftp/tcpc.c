#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 3001

int main()
{
    int sock_desc,k;
    struct sockaddr_in server,client;
    char buf[100];
    socklen_t len;
    
    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);
    
    k=connect(sock_desc,(struct sockaddr*) &server,sizeof(server));
    if(k==-1)
        printf("Error in connecting");
    
    printf("\nThe server is connected to the port %d",PORT);
    
    
    FILE* file=fopen("client.txt","r");
    
    if(!file)
        printf("Error in opening the file");
    
    while(!feof(file))
    {
        size_t read_size=fread(buf,sizeof(char),sizeof(buf),file);
        k=send(sock_desc,buf,read_size,0);
        if(k==-1)
            printf("Error in sending");
    }
    fclose(file);
    printf("\nFile sended to the server successfuly");
    
}
