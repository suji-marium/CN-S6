#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 3001

int main()
{
    int sock_desc,k,temp_sock_desc,read_size;
    struct sockaddr_in server,client;
    char buf[100];
    socklen_t len;
    
    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Error in socket creation");
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);
    
    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
        printf("Error in binding");
    
    k=listen(sock_desc,5);
    if(k==-1)
        printf("Error in listening");
        
    printf("\nServer is listening at port %d",PORT);
    
    len=sizeof(client);
    temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
    if(temp_sock_desc==-1)
        printf("Error in temporary socket creation");
    
    FILE* file=fopen("server.txt","w");
    
    if(!file)
        printf("Error in opening the file");
    
    while((read_size=recv(temp_sock_desc,buf,sizeof(buf),0))>0)
    {
        fwrite(buf,sizeof(char),read_size,file);
        printf("\n%s",buf);
    }
    fclose(file);
    printf("File received successfuly and is written in server.txt");

    
}
