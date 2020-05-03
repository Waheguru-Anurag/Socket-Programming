#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    const char *hello = "Hello from client1"; 
    char buffer[1024] = "Hello PLayground"; 
    fd_set conct;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.20", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    for(int i=0; i<6; i++){
        if(FD_ISSET(sock,&conct)){
            send(sock , hello , strlen(hello) , 0 ); 
            printf("Hello message sent{connected}\n"); 
            valread = read( sock , buffer, 1024); 
            printf("%s\n",buffer); 
        }
        else{
            if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
            { 
                printf("\nConnection Failed \n"); 
                return -1; 
            } 
            FD_ZERO(&conct);
            FD_SET(sock,&conct);
            send(sock , hello , strlen(hello) , 0 ); 
            printf("Hello message sent{2}\n"); 
            valread = read( sock , buffer, 1024); 
            printf("%s\n",buffer ); 
        }
    }
    
} 