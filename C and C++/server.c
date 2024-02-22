#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

void response(int client_socket) {
    FILE *html_file = fopen("index.html", "r");

    if (html_file == NULL) {
        printf("Error opening HTML file");
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    size_t bytesRead;

    // Read the file and send it to the client
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), html_file)) > 0) {
        if (send(client_socket, buffer, bytesRead, 0) == -1) {
            perror("Error sending HTML file");
            fclose(html_file);
            return;
        }
    }

    fclose(html_file);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("172.20.122.235");
    server_address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept incoming connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) == -1) {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        // Send HTML response
        response(client_socket);

        printf("HTML file sent to client %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        // Close client socket
        close(client_socket);
    }

    // Close server socket
    close(server_socket);

    return 0;
}
