#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet.h>
#include <unistd.h>


#define PORT 8080


int main(int argc, char* argv)
{
    // initializations
    int socketFileDesc;
    int newSocketDesc;
    int valueReader;

    struct sockaddr_in clientAddr;

    int opt = 1;
    int addrLen = sizeof(clientAddr);
    char buffer[1024] = { 0 };
    char* message = "Hello form server";

    // Create socket file descriptor
    if((socketFileDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("File description error");
        exit(EXIT_FAILURE);
    }

    // Forcefully attach socket
    // set socket options
    if((setsocketopt(socketFileDesc, SOC_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) < 0) {
        perror("socket options failed");
        exit(EXIT_FAILURE);
    }
    // set address
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = INADDR_ANY;
    clientAddr.sin_port = htons(PORT);

    // bind
    if(bind(socketFileDesc, (const sockaddr*)&clientAddr, sizeof(clientAddr)) < 0) {
        perror("Error in bind");
        exit(EXIT_FAILURE);
    }

    // listen
    if(listen(socketFileDesc, 3) < 0) {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    // accept
    if((newSocketDesc = accept(socketFileDesc, (struct sockaddr*)&clientAddr, (socklen_t*)&addrLen)) < 0) {
        perror("socket acceptence error");
        exit(EXIT_FAILURE);
    }

    valueReader = read(newSocketDesc, buffer, 1024); // reading from the socket
    send(newSocketDesc, message, sizeof(message), 0); // writing to the socket


    // close the connected socket
    close(newSocketDesc);

    // close listening socket
    shutdown(socketFileDesc, SHUT_RDWR);

    return 0;
}


