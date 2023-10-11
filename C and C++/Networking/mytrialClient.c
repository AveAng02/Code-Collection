
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char* argv[]) {

    int status;
    int clientFileDesc;
    int valread;

    struct sockaddr_in serverAddr;

    char buffer[1024] = { 0 };
    char* message = "Hello from server";

    // defining client file description 
    if((clientFileDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    // Convert IPv4 and IPv6 from text to binary  and put it in 
    // serverAddr.sin_addr
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("invalid IP value");
        exit(EXIT_FAILURE);
    }

    // connect socket
    if((status = connect(clientFileDesc, (struct sockaddr_in*)&serverAddr,
    sizeof(serverAddr))) <= 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    send(clientFileDesc, message, sizeof(message), 0);
    printf("Message sent");
    valread = read(clientFileDesc, buffer, 1024);
    printf("Message received");


    // Closing socket
    close(clientFileDesc);

    return 0;
}
