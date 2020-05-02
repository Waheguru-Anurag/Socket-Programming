// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <bits/stdc++.h>
using namespace std;
#define PORT 8888
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    int sock[5] = {0};
    const char *hello = "Hello from server"; 
    fd_set readfs;
    vector<int> v;
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8888
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    while(true){
        FD_ZERO(&readfs);
        FD_SET(server_fd,&readfs);
        int max = server_fd;
        for(int i=0; i<5; i++){
            if(sock[i]>0)
                FD_SET(sock[i],&readfs);
            if(sock[i]>max)
                max=sock[i];    
        }
        select(max+1,&readfs,NULL,NULL,NULL);
        if(FD_ISSET(server_fd,&readfs)){
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
            { 
                perror("accept"); 
                exit(EXIT_FAILURE); 
            }

            for(int i=0; i<6; i++)
                if(sock[i]==0){
                    sock[i]=new_socket;
                    break;
                }

        
            valread = read( new_socket , buffer, 1024); 
            printf("%s\n",buffer ); 
            send(new_socket , hello , strlen(hello) , 0 ); 
            printf("Hello message sent\n"); 
        }
    
        for(int i=0; i<5; i++){
                if(FD_ISSET(sock[i],&readfs)){
                    valread = read(sock[i] , buffer, 1024); 
                    if(valread!=0){
                        printf("%s\n",buffer ); 
                        send(sock[i] , hello , strlen(hello) , 0 ); 
                        printf("Hello message sentus\n"); 
                    }
                    else
                        sock[i]=0;
                }
        }
    }   
    return 0; 
} 